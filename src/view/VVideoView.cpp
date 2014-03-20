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
#endif
}

//----------------------------------------------------------------------
#ifndef USEPHONON
void VVideoView::error(QMediaPlayer::Error error)
{
	ITLErr << (fVideo ? fVideo->getOSCAddress().c_str() : "no video address") << fMediaPlayer.errorString().toStdString() << ITLEndl;
}

//----------------------------------------------------------------------
void VVideoView::nativeSizeChanged(const QSizeF & size)
{
	fVideoItem->setSize (size);
	fVideo->setWidth ( scene2RelativeWidth(size.width()) );
	fVideo->setHeight( scene2RelativeHeight(size.height()) );
	INScore::MessagePtr msg = INScore::newMessage ("show");
	INScore::add (msg, 1);
	INScore::postMessage (fVideo->getOSCAddress().c_str(), msg);
}

//----------------------------------------------------------------------
void VVideoView::mediaStatusChanged (QMediaPlayer::MediaStatus status)
{
//qDebug() << "VVideoView::mediaStatusChanged" << status << "metadata" << fMediaPlayer.availableMetaData().size();
	switch (status) {
		case QMediaPlayer::BufferedMedia:
			break;

		case QMediaPlayer::LoadingMedia:
//			fMediaPlayer.play();
//			fMediaPlayer.pause();
//			fMediaPlayer.setPosition(0);
//			fMediaPlayer.stop();
			break;
			
		case QMediaPlayer::UnknownMediaStatus:
		case QMediaPlayer::InvalidMedia:
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

	fVideoItem->setAspectRatioMode(Qt::IgnoreAspectRatio);

	video->setWidth(0.01f);			// default width
	video->setHeight(0.01f);		// and height
//	video->setVisible (false);
    connect(fVideoItem, SIGNAL(nativeSizeChanged(const QSizeF &)), this, SLOT(nativeSizeChanged(const QSizeF &)));
#endif
}

//----------------------------------------------------------------------
void VVideoView::initialize( IVideo * video  )
{
	QString file = VApplView::toQString( video->getFile().c_str() );
	if ( QFile::exists(  file  ) ) 
		initFile (video, file);
}

//----------------------------------------------------------------------
void VVideoView::updateView( IVideo * video  )
{
    video->cleanupSync();
    if(!video->getParent()->getDeleted())
    {
        if(video->getParent()->getTypeString() != IScene::kSceneType)
            setParentItem(video->getParent()->getView()?video->getParent()->getView():0);
    }
	QString file = VApplView::toQString( video->getFile().c_str() );
	if ( QFile::exists(  file  ) )
	{
		fVideoItem->setOpacity (video->getA() / 255.f);
		QSizeF size ( relative2SceneWidth(video->getWidth()),relative2SceneHeight(video->getHeight()));
		qint64 pos = video->currentTime() * 1000;
#ifdef USEPHONON
		fVideoItem->resize( size );
		fVideoItem->media()->seek( pos );
#else
		if (pos < 0 ) pos = 0;
		if (pos > fMediaPlayer.duration()) pos = fMediaPlayer.duration();
		if (size != fVideoItem->size()) fVideoItem->setSize( size );
		fMediaPlayer.play ();
		fMediaPlayer.setPosition( pos );
		fMediaPlayer.pause ();
#endif
	}
	else
	{
		// File not found. Do nothing. (Error msg is handled by the model.)
	}
	itemChanged();
	VGraphicsItemView::updateView( video );
}


} // end namespoace
