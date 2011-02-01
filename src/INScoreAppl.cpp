/*

  Interlude Prototype
  Copyright (C) 2009,2010  Grame

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

#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QMenu>
#include <QDir>
#include <QString>
#include <QEvent>
#include <QFileDialog>
#include <QFileOpenEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QUrl>
#include <QDebug>

#include <stdlib.h>
#include <iostream>
#include <string>

#include "INScore.h"
#include "INScoreAppl.h"

using namespace inscore;
using namespace std;

#define kUPDPort		7000
#define kTimeInterval	10			// time task interval in milliseconds

//_______________________________________________________________________
static int intopt (const string& opt, int defaultValue, int n, char **argv)
{
	for (int i = 0; i < n; i++) {
		if (opt == argv[i]) {
			int port = ( i+1 == n) ? 0 : atoi(argv[i+1]);
			return port ? port : defaultValue;
		}
	}
	return defaultValue;
}

//_______________________________________________________________________
INScoreScene::INScoreScene () : QGraphicsScene () 
{ 
//	setAcceptDrops(true); 
}

//_______________________________________________________________________
void INScoreScene::dropEvent ( QGraphicsSceneDragDropEvent * event )
{
	if (event->mimeData()->hasUrls()) {
		QString fileName = event->mimeData()->urls().first().toLocalFile();
		string strfile = fileName.toLocal8Bit().data();
		INScoreAppl::open ( strfile );
		event->accept();
	}
}

//_______________________________________________________________________
void INScoreScene::dragEnterEvent ( QGraphicsSceneDragDropEvent * event )
{
	if (event->mimeData()->hasUrls())
         event->acceptProposedAction();
}
//_______________________________________________________________________
void INScoreScene::dragMoveEvent ( QGraphicsSceneDragDropEvent * event )
{
	if (event->mimeData()->hasUrls())
         event->acceptProposedAction();
}

//_______________________________________________________________________
void INScoreAppl::setupMenu ()
{
	QMenuBar * menu = new QMenuBar();
	QMenu* fileMenu = menu->addMenu(tr("&File"));
	QMenu* helpMenu = menu->addMenu(tr("&Help"));


	QAction * opentAct = new QAction(tr("&Open"), this);
	opentAct->setShortcut (QKeySequence::Open);
    fileMenu->addAction(opentAct);
    connect(opentAct, SIGNAL(triggered()), this, SLOT(open()));

	QAction * aboutAct = new QAction(tr("&About"), this);
    helpMenu->addAction(aboutAct);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	QAction * aboutQtAct = new QAction(tr("&AboutQt"), this);
    helpMenu->addAction(aboutQtAct);
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
}


//_______________________________________________________________________
void INScoreAppl::about()
{
	QString title = "INScore Viewer";
	QString about = "An Interactive Augmented Score Viewer\nINScore library version ";
	about += INScore::versionStr();
	QMessageBox::about (0, title, about);
}

//_______________________________________________________________________
void INScoreAppl::aboutQt()
{
	QMessageBox::aboutQt (0, "INScore Viewer");
}

#if WIN32
#define sep '/'
#else
#define sep '/'
#endif
//_______________________________________________________________________
void INScoreAppl::open(const string& file)
{
	size_t pos = file.find_last_of (sep);
	if (pos != string::npos) {
		string path = file.substr(0, pos);
		INScore::MessagePtr msg = INScore::newMessage ("rootPath");
		INScore::add (msg, path.c_str());
		INScore::postMessage ("/ITL", msg);
	}
	INScore::MessagePtr msg = INScore::newMessage ("load");
	INScore::add (msg, file.c_str());
	INScore::postMessage ("/ITL", msg);
}

//_______________________________________________________________________
void INScoreAppl::open()
{
	QString fileName = QFileDialog::getOpenFileName(0, tr("Open INScore file"), "");
	if (fileName.size())
		open (fileName.toStdString());
}

//_______________________________________________________________________
bool INScoreAppl::event(QEvent *ev)
{
    if (ev->type() == QEvent::FileOpen) {
		QString fileName = static_cast<QFileOpenEvent *>(ev)->file();
		open (fileName.toStdString());
		return true;
    }
	return QApplication::event(ev);
}


#if defined(WIN32) && !defined(_DEBUG)
# define USEWINMAIN
#endif
//_______________________________________________________________________
#ifdef USEWINMAIN
#include <windows.h>
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdParam, int iCmdShow)
#else
int main( int argc, char **argv )
#endif
{
#ifdef USEWINMAIN
	int argc = __argc;
	char **argv = __argv;
#endif

	int ret = 1;
	int udpPort = intopt ("--port", kUPDPort, argc, argv);
	INScoreAppl appl(argc, argv);
	appl.setApplicationName("INScoreViewer");
	QDir dir(QApplication::applicationDirPath());
#ifndef WIN32
	dir.cdUp();
#endif
	dir.cd("PlugIns");
	appl.addLibraryPath		( dir.absolutePath());

	INScoreScene* scene = new INScoreScene;
	IGlue * glue = INScore::start (scene, kTimeInterval, udpPort, kUPDPort+1, kUPDPort+2);
	appl.setupMenu();
	ret = appl.exec();
	INScore::stop (glue);
	return ret;
}
