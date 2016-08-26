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
#ifndef USEPHONON
#include <QGraphicsVideoItem>
#endif

#include "INScore.h"
#include "ITLError.h"
#include "VVideoView.h"
#include "VApplView.h"

namespace inscore
{

//----------------------------------------------------------------------
VVideoView::VVideoView(QGraphicsScene * scene, const IVideo* video)
 :	VGraphicsItemView( scene , new IQGraphicsVideoItem(video) )
#ifndef USEPHONON
	, fMediaPlayer(0, QMediaPlayer::VideoSurface)
	, fVideo(0)
#endif
{
	fVideoItem = (IQGraphicsVideoItem*)(fItem);
#ifndef USEPHONON
    connect(&fMediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(error(QMediaPlayer::Error)));
    connect(&fMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(&fMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(&fMediaPlayer, SIGNAL(seekableChanged(bool)), this, SLOT(seekableChanged(bool)));
    connect(&fMediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&fMediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
#endif

}

//----------------------------------------------------------------------
#ifndef USEPHONON
void VVideoView::error(QMediaPlayer::Error )
{
	ITLErr << (fVideo ? fVideo->getOSCAddress().c_str() : "no video OSC address") << fMediaPlayer.errorString().toStdString() << ITLEndl;
}

//----------------------------------------------------------------------
void VVideoView::nativeSizeChanged(const QSizeF & size)
{
	fVideoItem->setSize (size);
	fVideo->setWidth ( scene2RelativeWidth(size.width()) );
	fVideo->setHeight( scene2RelativeHeight(size.height()) );
	INScore::postMessage (fVideo->getOSCAddress().c_str(), kx_GetSetMethod, fVideo->getXPos());
	fVideo->videoReady();
}

//----------------------------------------------------------------------
void VVideoView::seekableChanged(bool /*seekable*/)		{ /* qDebug() << "VVideoView::seekableChanged :" <<  seekable;*/ }
void VVideoView::positionChanged(qint64 pos)			{ fVideo->setIDate(pos); }
void VVideoView::durationChanged(qint64 duration)		{ fVideo->setVideoDuration (duration); }
void VVideoView::stateChanged (QMediaPlayer::State /*state*/)	{ /*qDebug() << "VVideoView::stateChanged :" <<  state;*/ }

//----------------------------------------------------------------------
void VVideoView::mediaStatusChanged (QMediaPlayer::MediaStatus status)
{
//qDebug() << "VVideoView::mediaStatusChanged" << status;
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
			ITLErr << (fVideo ? fVideo->getOSCAddress().c_str() : "no video OSC address") << "invalid media" << ITLEndl;
			break;

		case QMediaPlayer::EndOfMedia:
			fMediaPlayer.setPosition( fMediaPlayer.duration()-1 );
			fVideo->videoEnd();
			break;
		default:
			break;
	}
}
#endif

//----------------------------------------------------------------------
void VVideoView::initFile( IVideo * video, const QString&  videoFile )
{
#ifdef USEPHONON
	fVideoItem->setMediaFile( videoFile );
	fVideoItem->media()->play();
	fVideoItem->media()->pause();	
	updateObjectSize (video);
#else
	fVideo = video;
	fMediaPlayer.setMedia(QUrl::fromLocalFile(videoFile));
	fMediaPlayer.setVideoOutput (fVideoItem);
	fMediaPlayer.setNotifyInterval(10);

	fVideoItem->setAspectRatioMode(Qt::IgnoreAspectRatio);

	video->setWidth(0.f);		// unknown width
	video->setHeight(0.f);		// unknown height
    connect(fVideoItem, SIGNAL(nativeSizeChanged(const QSizeF &)), this, SLOT(nativeSizeChanged(const QSizeF &)));
#endif
}

//----------------------------------------------------------------------
void VVideoView::initialize( IVideo * video  )
{
	QString file = VApplView::toQString( video->getPath().c_str() );
	if ( QFile::exists(  file  ) ) 
		initFile (video, file);
}

//----------------------------------------------------------------------
void VVideoView::updateView( IVideo * video  )
{
    video->cleanupSync();
	fVideoItem->setOpacity (video->getA() / 255.f);
	QSizeF size ( relative2SceneWidth(video->getWidth()),relative2SceneHeight(video->getHeight()));
//		qint64 pos = video->currentTime() * 1000;
	qint64 pos = video->vDate();
		
#ifdef USEPHONON
	fVideoItem->resize( size );
	fVideoItem->media()->seek( pos );
#else
	if (pos < 0 ) pos = 0;
	if (pos > fMediaPlayer.duration()) pos = fMediaPlayer.duration()-1;
	if (size != fVideoItem->size()) fVideoItem->setSize( size );

	fMediaPlayer.setVolume( video->volume() * 100);
	if (video->rateModified()) fMediaPlayer.setPlaybackRate( video->rate() );
	if (video->playing()) {
		if (fMediaPlayer.state() !=  QMediaPlayer::PlayingState) {
			fMediaPlayer.play ();
		}
	}
	else if (fMediaPlayer.state() ==  QMediaPlayer::PlayingState)
		fMediaPlayer.pause ();

	if (video->vdateModified())
		fMediaPlayer.setPosition( pos );
#endif
	itemChanged();
	VGraphicsItemView::updateView( video );
}


} // end namespoace
