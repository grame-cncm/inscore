/*

  INScore Project

  Copyright (C) 2015  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include "VMobileMenu.h"

#include <QSettings>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>

#include "IAppl.h"
#include "IMessage.h"
#include "Methods.h"
#include "INScore.h"

#include <QDebug>

namespace inscore
{

static const char * sampleFileName = "sample.inscore";

//--------------------------------------------------------------------------
VMobileMenu::VMobileMenu(const char * name, QWidget* parent) : QWidget(parent)
{
	setWindowTitle( tr(name) );
    // For ios, avoid transparent background
    setAutoFillBackground(true);

	// Create the main layout
	QVBoxLayout *verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(0, 0, 0, 0);

	// Create main title
	QFont font ("FreeSans", 20);
	font.setBold(true);
	QLabel * text = new QLabel("INScore for mobile");
	text->setFont(font);
	verticalLayout->addWidget(text);

	// Layout for tree text label with left indentation
	QGridLayout * gridLayout = new QGridLayout();
	gridLayout->setSpacing(6);
	QSpacerItem * labelHSpacer = new QSpacerItem(20, 5, QSizePolicy::Maximum, QSizePolicy::Minimum);
	gridLayout->addItem(labelHSpacer, 0, 0, 3, 1);

	// Create inscore version text
	font.setPointSize(16);
	font.setBold(false);
	QString version("INScore v.");
	version += INScore::versionStr();
	text = new QLabel(version);
	text->setFont(font);
	gridLayout->addWidget(text, 0, 1, 1, 1);

	QString qt("Using Qt v.");
	qt += qVersion();
	text = new QLabel(qt);
	text->setFont(font);
	gridLayout->addWidget(text, 1, 1, 1, 1);

	QString guido("Using Guido Engine v.");
	guido += INScore::guidoversion();
	text = new QLabel(guido);
	text->setFont(font);
	gridLayout->addWidget(text, 2, 1, 1, 1);

	verticalLayout->addLayout(gridLayout);

	// Add change port button
	QPushButton * changePort = new QPushButton(tr("Change application port number"));
	connect(changePort, SIGNAL(clicked()), this, SLOT(showChangePortNumber()));
	verticalLayout->addWidget(changePort);

	// Add checkboxes
	loadSample = new QCheckBox(tr("Load sample file next time"));
	loadSample->setStyleSheet("margin-top : 40px; margin-bottom : 0px;");
	verticalLayout->addWidget(loadSample);

	showNextTime = new QCheckBox(tr("Show this dialog next time"));
	showNextTime->setStyleSheet("margin-top : 0px; margin-bottom : 40px;");
	verticalLayout->addWidget(showNextTime);

	// Add Url file loader
	verticalLayout->addWidget(new QLabel(tr("Url for external resources : ")));
	QHBoxLayout * horizontalLayout = new QHBoxLayout();
	fUrlFile = new QLineEdit();
	horizontalLayout->addWidget(fUrlFile);
	QPushButton * loadUrl = new QPushButton;
	loadUrl->setIcon(QIcon(":/images/load.png"));
	loadUrl->iconSize();
	loadUrl->setIconSize(QSize(60, 60));
	connect(loadUrl, SIGNAL(clicked()), this, SLOT(loadUrlFile()));
	horizontalLayout->addWidget(loadUrl);
	verticalLayout->addLayout(horizontalLayout);

	// Layout for buttons
	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);

	QPushButton * openFile = new QPushButton("Open local file");
	connect(openFile, SIGNAL(clicked()), this, SLOT(showFileDialog()));
	horizontalLayout->addWidget(openFile);

	QSpacerItem * buttonHSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalLayout->addItem(buttonHSpacer);

	QPushButton * close = new QPushButton("Close");
	connect(close, SIGNAL(clicked()), this, SLOT(closeMenu()));
	horizontalLayout->addWidget(close);
	verticalLayout->addLayout(horizontalLayout);

	QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	verticalLayout->addItem(verticalSpacer);

	// Read the settings
	readSettings();
	connect(showNextTime, SIGNAL(stateChanged(int)), this, SLOT(writeSettings()));
	connect(loadSample, SIGNAL(stateChanged(int)), this, SLOT(writeSettings()));

	if (loadSample->isChecked()) {
		loadSampleFile();
	}
}

//--------------------------------------------------------------------------
void VMobileMenu::showFileDialog()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter(tr("Script Files (*.inscore)"));
	dialog.setViewMode(QFileDialog::List);
	dialog.setDirectory(IAppl::getRootPath().c_str());
	dialog.showMaximized();
	QStringList fileNames;
	if (dialog.exec()) // modal mode
		fileNames = dialog.selectedFiles();

	if(!fileNames.isEmpty()) {
		std::string filename = fileNames[0].toStdString();
		sendLoadMsg(filename.c_str());
	}
}

//--------------------------------------------------------------------------
void VMobileMenu::writeSettings()
{
	QSettings settings("Grame", "INScore");

	settings.beginGroup("Mobile");
	settings.setValue("showMenu", showNextTime->isChecked());
	settings.setValue("loadSample", loadSample->isChecked());
	settings.endGroup();
}

//--------------------------------------------------------------------------
void VMobileMenu::readSettings()
{
	QSettings settings("Grame", "INScore");

	settings.beginGroup("Mobile");
	showNextTime->setChecked(settings.value("showMenu", true).toBool());
	loadSample->setChecked(settings.value("loadSample", true).toBool());
	settings.endGroup();
}

//--------------------------------------------------------------------------
void VMobileMenu::loadSampleFile() {
	// Get root path
	QString path = IAppl::getRootPath().c_str();
	if(!QFile(path + sampleFileName).exists()) {
		// The sample file is in qt ressources, so we need to create it in root path.
		QFile::copy(QString(":/") + sampleFileName, path + sampleFileName);
	}
	// send a message to load file.
	sendLoadMsg(sampleFileName);
}

//--------------------------------------------------------------------------
void VMobileMenu::sendLoadMsg(const char * file)
{
	// Create a message to load file.
	SIMessage msg = IMessage::create("/ITL", kload_SetMethod);
	msg->add(file);
	msg->send();
}

//--------------------------------------------------------------------------
void VMobileMenu::closeMenu()
{
	SIMessage msg = IMessage::create("/ITL/menu", kshow_GetSetMethod);
	msg->add(0);
	msg->send();
}

//--------------------------------------------------------------------------
void VMobileMenu::loadUrlFile()
{
	// Get the url and send a message to load the file.
	QString url = fUrlFile->text().trimmed();
	if(!url.isEmpty()) {
		sendLoadMsg(url.toStdString().c_str());
	}
}

//--------------------------------------------------------------------------
void VMobileMenu::showChangePortNumber()
{
	// Create a modal window to change the port number
	QDialog popup(this, Qt::Window);
	QLineEdit *inport = new QLineEdit(&popup);
	QLineEdit *outport = new QLineEdit(&popup);
	QLineEdit *errport = new QLineEdit(&popup);

	// Push button OK and cancel
	QPushButton * ok = new QPushButton("OK", &popup);
	connect(ok, SIGNAL(clicked()), &popup, SLOT(accept()));
	QPushButton * cancel = new QPushButton("Cancel", &popup);
	connect(cancel, SIGNAL(clicked()), &popup, SLOT(reject()));

	// Main layout with spacer at left right and bottom.
	QGridLayout * gridLayout = new QGridLayout(&popup);
	QSpacerItem * horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	gridLayout->addItem(horizontalSpacer, 0, 0, 2, 1);
	horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	gridLayout->addItem(horizontalSpacer, 0, 3, 2, 1);
	gridLayout->addWidget(new QLabel(tr("Listening port :")), 0, 1);
	gridLayout->addWidget(inport, 0, 2);
	gridLayout->addWidget(new QLabel(tr("Out port :")), 1, 1);
	gridLayout->addWidget(outport, 1, 2);
	gridLayout->addWidget(new QLabel(tr("Error port :")), 2, 1);
	gridLayout->addWidget(errport, 2, 2);

	// Layout for buttons
	QHBoxLayout * horizontalLayout = new QHBoxLayout();
	horizontalLayout->addWidget(ok);
	horizontalLayout->addWidget(cancel);
	gridLayout->addLayout(horizontalLayout, 3, 1, 1, 2);

	// Spacer at end of window
	QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	gridLayout->addItem(verticalSpacer, 4, 0, 1, 4);

	// Initialize port numbers with actual port numbers
	int originalIn = IAppl::getUDPInPort();
	inport->setText(QString::number(originalIn));
	inport->setFocus();
	int originalOut = IAppl::getUDPOutPort();
	outport->setText(QString::number(originalOut));
	int originalErr = IAppl::getUDPErrPort();
	errport->setText(QString::number(originalErr));

	if(QDialog::Accepted == popup.exec()) { // Modal mode
		// User cick "OK", send messages

		// Listening port
		QString text = inport->text();
		bool ok;
		int newPort = text.toInt(&ok);
		if(ok && originalIn != newPort) {
			// Send message to change listening port number.
			SIMessage msg = IMessage::create("/ITL", kport_GetSetMethod);
			msg->add(newPort);
			msg->send();
		}
		// Out port
		text = outport->text();
		newPort = text.toInt(&ok);
		if(ok && originalOut != newPort) {
			// Send message to change listening port number.
			SIMessage msg = IMessage::create("/ITL", koutport_GetSetMethod);
			msg->add(newPort);
			msg->send();
		}
		// Error port
		text = errport->text();
		newPort = text.toInt(&ok);
		if(ok && originalErr != newPort) {
			// Send message to change listening port number.
			SIMessage msg = IMessage::create("/ITL", kerrport_GetSetMethod);
			msg->add(newPort);
			msg->send();
		}
	}
}

} // end namespoace
