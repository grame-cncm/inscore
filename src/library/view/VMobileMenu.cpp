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

#include "IAppl.h"
#include "IMessage.h"
#include "Methods.h"
#include "VQtInit.h"
#include "INScore.h"

#include <QDebug>

namespace inscore
{

static const char * sampleFileName = "sample.inscore";

//--------------------------------------------------------------------------
VMobileMenu::VMobileMenu(const char * name, QWidget* parent) : QWidget(parent)
{
	setWindowTitle( tr(name) );

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

	// Add controls
	loadSample = new QCheckBox(tr("Load sample file next time"));
	verticalLayout->addWidget(loadSample);

	showNextTime = new QCheckBox(tr("Show this dialog next time"));
	verticalLayout->addWidget(showNextTime);

	// Layout for buttons
	QHBoxLayout * horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);

	QPushButton * openFile = new QPushButton("Open file");
	connect(openFile, SIGNAL(clicked()), this, SLOT(showFileDialog()));
	horizontalLayout->addWidget(openFile);

	QSpacerItem * buttonHSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalLayout->addItem(buttonHSpacer);

	QPushButton * close = new QPushButton("Close Menu");
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
	if (dialog.exec())
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

} // end namespoace
