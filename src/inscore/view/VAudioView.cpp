/*

  INScore Project

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

#include <iostream>
#include <QFile>
#include <QDebug>
#include <QGraphicsRectItem>

#include "INScore.h"
#include "ITLError.h"
#include "VAudioView.h"
#include "VApplView.h"

namespace inscore
{

//----------------------------------------------------------------------
VAudioView::VAudioView(QGraphicsScene * scene, const IAudio* audio)
 :	VMappedShapeView( scene , new MouseEventAble<QGraphicsRectItem>(audio)), fAudio(0)
{
}

//----------------------------------------------------------------------
void VAudioView::mediaReady() {
	fAudio->setMediaDuration(player()->duration());
	fAudio->mediaReady();
}
void VAudioView::posChanged(qint64 pos)		{ fAudio->setIDate(pos); }
void VAudioView::mediaEnd()					{ fAudio->mediaEnd(); }

//----------------------------------------------------------------------
void VAudioView::error(QString msg)
{
	ITLErr << fAudio->getOSCAddress().c_str() << "error" << msg.toStdString() << ITLEndl;
}

//----------------------------------------------------------------------
void VAudioView::initialize( IAudio * audio  )
{
	fAudio = audio;
	QString file = VApplView::toQString( audio->getPath().c_str() );
	if ( QFile::exists(  file  ) ) 
		setFile (file);
}

//----------------------------------------------------------------------
void VAudioView::updateView( IAudio * audio  )
{
	audio->cleanupSync();

	updatePlayer (audio);
	
//	qint64 pos = audio->vDate();
//	if (pos < 0 ) pos = 0;
//	if (pos > player()->duration()) pos = player()->duration()-1;
//
//	player()->setVolume( audio->volume() * 100);
//	if (audio->rateModified()) player()->setPlaybackRate( audio->rate() );
//	if (audio->playing()) {
//		if (player()->state() !=  QMediaPlayer::PlayingState) {
//			player()->play ();
//		}
//	}
//	else if (player()->state() ==  QMediaPlayer::PlayingState)
//		player()->pause ();
//
//	if (audio->vdateModified())
//		player()->setPosition( pos );

	itemChanged();
	VShapeView::updateView( audio );
}


} // end namespace
