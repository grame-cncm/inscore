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
 :	VGraphicsItemView( scene , new IQGraphicsVideoItem(video) ), fVideo(0)
{
	fVideoItem = (IQGraphicsVideoItem*)(fItem);
    connect(fVideoItem, SIGNAL(nativeSizeChanged(const QSizeF &)), this, SLOT(nativeSizeChanged(const QSizeF &)));
	player()->setVideoOutput (fVideoItem);
}


//----------------------------------------------------------------------
void VVideoView::mediaReady()
{
	fVideo->setMediaDuration(player()->duration());
	fVideo->videoReady();
}

//----------------------------------------------------------------------
void VVideoView::mediaEnd()					{ fVideo->videoEnd(); }
void VVideoView::posChanged(qint64 pos)		{ fVideo->setIDate(pos); }

//----------------------------------------------------------------------
void VVideoView::error(QString msg)
{
	ITLErr << (fVideo ? fVideo->getOSCAddress().c_str() : "no video OSC address") << "error" << msg.toStdString() << ITLEndl;
}

//----------------------------------------------------------------------
void VVideoView::sizeChanged(const QSizeF & size)
{
	fVideoItem->setSize (size);
	fVideo->setWidth ( scene2RelativeWidth(size.width()) );
	fVideo->setHeight( scene2RelativeHeight(size.height()) );
	INScore::postMessage (fVideo->getOSCAddress().c_str(), kx_GetSetMethod, fVideo->getXPos());
}

//----------------------------------------------------------------------
void VVideoView::initFile( IVideo * video, const QString&  videoFile )
{
	setFile(videoFile);
	fVideoItem->setAspectRatioMode(Qt::IgnoreAspectRatio);
	video->setWidth(0.f);		// unknown width
	video->setHeight(0.f);		// unknown height
}

//----------------------------------------------------------------------
void VVideoView::initialize( IVideo * video  )
{
	fVideo = video;
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
	if (size != fVideoItem->size()) fVideoItem->setSize( size );
	
	updatePlayer (video);

	itemChanged();
	VGraphicsItemView::updateView( video );
}


} // end namespace
