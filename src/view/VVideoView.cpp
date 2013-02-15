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

#include "VVideoView.h"

#include <iostream>
#include <QFile>

#include "VApplView.h"

namespace inscore
{

//----------------------------------------------------------------------
VVideoView::VVideoView(QGraphicsScene * scene, const IVideo* h)
 : VGraphicsItemView( scene , new IQGraphicsVideoItem(h) )
{
	fVideoItem = (IQGraphicsVideoItem*)(fItem);
}

//----------------------------------------------------------------------
void VVideoView::initFile( IVideo * video, const QString&  videoFile )
{
	fVideoItem->setMediaFile( videoFile );
//	fVideoItem->media()->play();
//	fVideoItem->media()->pause();	
	updateObjectSize (video);
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
	// 1. Update video file.
	QString file = VApplView::toQString( video->getFile().c_str() );
	if ( QFile::exists(  file  ) )
	{
//		QString videoFile = VApplView::toQString( video->getFile().c_str() );

//		if ( ( fVideoItem->media() && ( fVideoItem->media()->currentSource().fileName() != videoFile ) ) ||	!fVideoItem->media())

//		if ( fVideoItem->media()->currentSource().fileName() != videoFile )
//			initFile (video, videoFile);

//		{
//			fVideoItem->setMediaFile( videoFile );
//			fVideoItem->media()->play();
//			fVideoItem->media()->pause();
//			
//			// Sets the IVideo model size to the original video size.
//			video->setWidth( scene2RelativeWidth( fVideoItem->size().width() ) );
//			video->setHeight( scene2RelativeHeight( fVideoItem->size().height() ) );
//		}
		// 2. Update video size.
		fVideoItem->setOpacity (video->getA() / 255.f);
		fVideoItem->resize( QSizeF( relative2SceneWidth(video->getWidth()),relative2SceneHeight(video->getHeight()) ) );
//		fVideoItem->media()->seek( video->currentTime() * 1000 );		

		// TODO Checker le support video de Phonon.
	}
	else
	{
		// File not found. Do nothing. (Error msg is handled by the model.)
	}

	itemChanged();
	VGraphicsItemView::updateView( video );
}


} // end namespoace
