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

#include <QFile>
#include <QSize>
#include <QDebug>
#include <QGraphicsVideoItem>

#include "INScore.h"
#include "IMedia.h"
#include "ITLError.h"
#include "VMediaPlayer.h"

namespace inscore
{

//----------------------------------------------------------------------
VMediaPlayer::VMediaPlayer () :
	fMediaPlayer(0, QMediaPlayer::VideoSurface), fReady(0)
{
    connect(&fMediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(error(QMediaPlayer::Error)));
    connect(&fMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(&fMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(&fMediaPlayer, SIGNAL(seekableChanged(bool)), this, SLOT(seekableChanged(bool)));
    connect(&fMediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&fMediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
}

//----------------------------------------------------------------------
void VMediaPlayer::connectVideo(QGraphicsVideoItem* v)
{
qDebug() << "VMediaPlayer::connectVideo";
    connect(v, SIGNAL(nativeSizeChanged(const QSizeF &)), this, SLOT(nativeSizeChanged(const QSizeF &)));
}

//----------------------------------------------------------------------
void VMediaPlayer::error(QMediaPlayer::Error err )
{
	error (fMediaPlayer.errorString());
	qDebug() << "VMediaPlayer::error" << err << endl;
}

//----------------------------------------------------------------------
void VMediaPlayer::nativeSizeChanged(const QSizeF & size)
{
	if (size.isEmpty()) return;
	sizeChanged (size);
	int target = fMediaPlayer.isAudioAvailable() ?  1 : 0;
	target += fMediaPlayer.isVideoAvailable() ?  1 : 0;
	if (++fReady == target) {
		mediaReady();
	}
}

//----------------------------------------------------------------------
void VMediaPlayer::seekableChanged(bool /*seekable*/)		{ /* qDebug() << "VMediaPlayer::seekableChanged :" <<  seekable;*/ }
void VMediaPlayer::positionChanged(qint64 pos)			{ posChanged(pos); }
void VMediaPlayer::durationChanged(qint64 duration)		{
	int target = fMediaPlayer.isAudioAvailable() ?  1 : 0;
	target += fMediaPlayer.isVideoAvailable() ?  1 : 0;
	if (++fReady == target) {
		mediaReady();
	}
}
void VMediaPlayer::stateChanged (QMediaPlayer::State /*state*/)	{ /*qDebug() << "VMediaPlayer::stateChanged :" <<  state;*/ }

//----------------------------------------------------------------------
void VMediaPlayer::mediaStatusChanged (QMediaPlayer::MediaStatus status)
{
//qDebug() << "VMediaPlayer::mediaStatusChanged" << status;
	switch (status) {
		case QMediaPlayer::LoadedMedia:			// this is necessary to trigger the nativeSizeChanged slot
			fMediaPlayer.play();
			fMediaPlayer.setPosition(0);
			fMediaPlayer.pause();
			break;
			
		case QMediaPlayer::BufferedMedia:
		case QMediaPlayer::UnknownMediaStatus:
			break;
		case QMediaPlayer::InvalidMedia:
			error("invalid media");
			break;

		case QMediaPlayer::EndOfMedia:
			fMediaPlayer.setPosition( fMediaPlayer.duration()-1 );
			mediaEnd();
			break;
		default:
			break;
	}
}

//----------------------------------------------------------------------
void VMediaPlayer::updatePlayer( const IMedia * media  )
{
	qint64 pos = media->vDate();
	if (pos < 0 ) pos = 0;
	if (pos > player()->duration()) pos = player()->duration()-1;

	player()->setVolume( media->volume() * 100);
	if (media->rateModified()) player()->setPlaybackRate( media->rate() );
	if (media->playing()) {
		if (player()->state() !=  QMediaPlayer::PlayingState) {
			player()->play ();
		}
	}
	else if (player()->state() ==  QMediaPlayer::PlayingState)
		player()->pause ();

	if (media->vdateModified())
		player()->setPosition( pos );
}

//----------------------------------------------------------------------
void VMediaPlayer::setFile( const QString&  mediaFile )
{
	fReady = 0;
	fMediaPlayer.stop ();
	fMediaPlayer.setMedia(QUrl::fromLocalFile(mediaFile));
	fMediaPlayer.setNotifyInterval(10);
}


} // end namespoace
