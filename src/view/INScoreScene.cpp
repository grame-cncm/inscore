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

#include <QString>
#include <QEvent>
#include <QMimeData>
#include <QUrl>
#include <QGraphicsSceneDragDropEvent>

#include <iostream>
#include <string>

#include "IAppl.h"
#include "INScore.h"
#include "INScoreScene.h"

using namespace std;
using namespace inscore;

//_______________________________________________________________________
INScoreScene::INScoreScene (const std::string& address) : QGraphicsScene (), fOscAddress(address) {}
INScoreScene::~INScoreScene ()						{}

//_______________________________________________________________________
void INScoreScene::open (const char* fullpath)
{
	string file (fullpath);
	size_t pos = file.find_last_of ("/");
	string appl("/");
	appl += IAppl::kName;
	if (pos != string::npos) {
		string path = file.substr(0, pos);
		INScore::MessagePtr msg = INScore::newMessage ("rootPath");
		INScore::add (msg, path.c_str());
		INScore::postMessage (appl.c_str(), msg);
	}
	INScore::MessagePtr msg = INScore::newMessage ("load");
	INScore::add (msg, file.c_str());
	INScore::postMessage (fOscAddress.c_str(), msg);
}

//_______________________________________________________________________
void INScoreScene::dropEvent ( QGraphicsSceneDragDropEvent * event )
{
	if (event->mimeData()->hasUrls()) {
		QString fileName = event->mimeData()->urls().first().toLocalFile();
		open ( fileName.toLocal8Bit().data() );
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
