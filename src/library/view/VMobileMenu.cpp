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

	// Create main title
	QFont font ("FreeSans", 20);
	font.setBold(true);
	QLabel * text = new QLabel("INScore for mobile", this);
	text->setFont(font);
	text->move(20, 20);

	// Create inscore version text
	font.setPointSize(16);
	font.setBold(false);
	QString version("INScore v.");
	version += INScore::versionStr();
	text = new QLabel(version, this);
	text->setFont(font);
	text->move(50, 70);

	QString qt("Using Qt v.");
	qt += qVersion();
	text = new QLabel(qt, this);
	text->setFont(font);
	text->move(50, 105);

	QString guido("Using Guido Engine v.");
	guido += INScore::guidoversion();
	text = new QLabel(guido, this);
	text->setFont(font);
	text->move(50, 140);

	// Add controls
	loadSample = new QCheckBox(tr("Load sample file next time"), this);
	loadSample->move(20, 165);

	showNextTime = new QCheckBox(tr("Show this dialog next time"), this);
	showNextTime->move(20, 230);

	QPushButton * openFile = new QPushButton("Open file", this);
	openFile->move(20, 320);
	connect(openFile, SIGNAL(clicked()), this, SLOT(showFileDialog()));

	QPushButton * close = new QPushButton("Close Menu", this);
	close->move(this->width() - 350, 320);
	connect(close, SIGNAL(clicked()), this, SLOT(closeMenu()));

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
