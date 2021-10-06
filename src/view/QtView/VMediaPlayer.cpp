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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <QAudioOutput>
#include <QFile>
#include <QSize>
#include <QDebug>
#include <QGraphicsVideoItem>

#include "Modules.h"
#include "INScore.h"
#include "IMedia.h"
#include "ITLError.h"
#include "VMediaPlayer.h"

namespace inscore
{

//----------------------------------------------------------------------
VMediaPlayer::VMediaPlayer () :
#if Qt6
	fMediaPlayer(0)
#else
	fMediaPlayer(0, QMediaPlayer::VideoSurface)
#endif
{
    connect(&fMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(&fMediaPlayer, SIGNAL(seekableChanged(bool)), this, SLOT(seekableChanged(bool)));
    connect(&fMediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&fMediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
#if !Qt6
    connect(&fMediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(error(QMediaPlayer::Error)));
    connect(&fMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
#else
    connect(&fMediaPlayer, SIGNAL(hasAudioChanged(bool)), this, SLOT(hasAudioChanged(bool)));
    connect(&fMediaPlayer, SIGNAL(hasVideoChanged(bool)), this, SLOT(hasVideoChanged(bool)));
	fMediaPlayer.setAudioOutput(new QAudioOutput);
#endif
}

//----------------------------------------------------------------------
void VMediaPlayer::connectVideo(QGraphicsVideoItem* v)
{
//qDebug() << "INScore VMediaPlayer::connectVideo";
    connect(v, SIGNAL(nativeSizeChanged(const QSizeF &)), this, SLOT(nativeSizeChanged(const QSizeF &)));
}

//----------------------------------------------------------------------
void VMediaPlayer::error(QMediaPlayer::Error err )
{
	error (fMediaPlayer.errorString());
//	qDebug() << "VMediaPlayer::error" << err << endl;
}

#if Qt6
//----------------------------------------------------------------------
bool VMediaPlayer::ready()
{
	if (fMediaPlayer.hasAudio() && fMediaPlayer.hasVideo()) return fAudioAvailable && fVideoAvailable;
	if (fMediaPlayer.hasAudio()) return fAudioAvailable;
	if (fMediaPlayer.hasVideo()) return fVideoAvailable;
	return false;
}

//----------------------------------------------------------------------
void VMediaPlayer::hasAudioChanged(bool available)
{
	fAudioAvailable = available;
	if (ready()) mediaReady();
}

//----------------------------------------------------------------------
void VMediaPlayer::hasVideoChanged(bool available)
{
	fVideoAvailable = available;
	if (ready()) mediaReady();
}
#else

//----------------------------------------------------------------------
void VMediaPlayer::hasAudioChanged(bool available) {}
void VMediaPlayer::hasVideoChanged(bool available) {}
#endif

//----------------------------------------------------------------------
void VMediaPlayer::nativeSizeChanged(const QSizeF & size)
{
//qDebug() << "INScore : VMediaPlayer::nativeSizeChanged" << size << endl;
	if (size.isEmpty()) return;
	sizeChanged (size);
#if !Qt6
	int target = fMediaPlayer.isAudioAvailable() ?  1 : 0;
	target += fMediaPlayer.isVideoAvailable() ?  1 : 0;
	if (++fReady == target) {
		mediaReady();
	}
#endif
}

//----------------------------------------------------------------------
void VMediaPlayer::seekableChanged(bool seekable)		{ /*qDebug() << "INScore : VMediaPlayer::seekableChanged :" <<  seekable;*/ }
void VMediaPlayer::positionChanged(qint64 pos)			{ posChanged(pos); }
void VMediaPlayer::durationChanged(qint64 duration)		{
//qDebug() << "INScore : VMediaPlayer::durationChanged" << duration;
#if ! Qt6
	int target = fMediaPlayer.isAudioAvailable() ?  1 : 0;
	target += fMediaPlayer.isVideoAvailable() ?  1 : 0;
	if (++fReady == target) {
		mediaReady();
	}
#else
//	if (ready())
	mediaReady();
#endif
}
//void VMediaPlayer::stateChanged (QMediaPlayer::State state)	{ /*qDebug() << "INScore : VMediaPlayer::stateChanged :" <<  state;*/ }

//----------------------------------------------------------------------
void VMediaPlayer::mediaStatusChanged (QMediaPlayer::MediaStatus status)
{
//qDebug() << "INScore : VMediaPlayer::mediaStatusChanged" << status;
	switch (status) {
		case QMediaPlayer::LoadedMedia:			// this is necessary to trigger the nativeSizeChanged slot
			fMediaPlayer.play();
			fMediaPlayer.setPosition(0);
			fMediaPlayer.pause();
			break;
			
		case QMediaPlayer::BufferedMedia:
//		case QMediaPlayer::UnknownMediaStatus:
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
//qDebug() << "INScore : VMediaPlayer::updatePlayer size" << ;
	qint64 pos = media->vDate();
	if (pos < 0 ) pos = 0;
	if (pos > player()->duration()) pos = player()->duration()-1;

#if Qt6
	QMediaPlayer::PlaybackState state = player()->playbackState();
	fMediaPlayer.audioOutput()->setVolume(media->volume());
#else
	QMediaPlayer::State state = player()->state();
	player()->setVolume( media->volume() * 100);
#endif
	if (media->rateModified()) player()->setPlaybackRate( media->rate() );
	if (media->playing()) {
		if (state !=  QMediaPlayer::PlayingState) {
			player()->play ();
		}
	}
	else if (state ==  QMediaPlayer::PlayingState)
		player()->pause ();

	if (media->vdateModified())
		player()->setPosition( pos );
}

//----------------------------------------------------------------------
void VMediaPlayer::setFile( const QString&  mediaFile )
{
	fMediaPlayer.stop ();
#if Qt6
	fAudioAvailable = fVideoAvailable = false;
	fMediaPlayer.setSource(QUrl::fromLocalFile(mediaFile));
#else
	fReady = 0;
	fMediaPlayer.setMedia(QUrl::fromLocalFile(mediaFile));
	fMediaPlayer.setNotifyInterval(10);
#endif
}


} // end namespoace
