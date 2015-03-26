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


#ifndef __QGraphicsVideoItem__
#define __QGraphicsVideoItem__

#include <QGraphicsProxyWidget>
#ifdef USEPHONON
#include <phonon/phonon>
#else
#include <QMediaPlayer>
#include <QMovie>
#include <QWidget>
#endif

namespace inscore {

#ifdef USEPHONON
class QGraphicsVideoItem : public QGraphicsProxyWidget
{
	Phonon::MediaObject *	fMedia;
	Phonon::VideoWidget *	fVideoWidget;
	Phonon::Path			fPath;
		
	public:
				 QGraphicsVideoItem( QGraphicsItem * parent = 0 ) 
									: QGraphicsProxyWidget(parent), fMedia(0), fVideoWidget(0) {}
		virtual ~QGraphicsVideoItem()		{ close(); }
		
		Phonon::MediaObject * media()		{ return fMedia; }

		void setMediaFile(const QString& fileName)
		{
			close();

			fMedia = new Phonon::MediaObject;
			fMedia->setCurrentSource(Phonon::MediaSource( fileName ));
			
			fVideoWidget = new Phonon::VideoWidget;
			fVideoWidget->setScaleMode(Phonon::VideoWidget::FitInView);
			fVideoWidget->setAspectRatio( Phonon::VideoWidget::AspectRatioWidget );
			
			setWidget(fVideoWidget);
			fPath = Phonon::createPath(fMedia, fVideoWidget);
		}

	protected:

		void close()
		{
			if ( fMedia ) fMedia->stop();
			fPath.disconnect();
			setWidget(0);
			delete fVideoWidget;
			delete fMedia;
			fVideoWidget = 0;
			fMedia = 0;
		}
		
};

#else

class QGraphicsVideoItem : public QGraphicsProxyWidget
{
	private:
		QMediaPlayer		 fMediaPlayer;
		QGraphicsVideoItem * fVideoItem;

	public:
				 QGraphicsVideoItem( QGraphicsItem * parent = 0 ) 
									: QGraphicsProxyWidget(parent), fMediaPlayer(0, QMediaPlayer::VideoSurface) {}
		virtual ~QGraphicsVideoItem()		{ close(); }
		
		QMediaPlayer * media()						{ return &fMediaPlayer; }
		void setMediaFile(const QString& fileName)	{
			if (!fileName.isEmpty())
				fMediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
				fVideoItem = new QGraphicsVideoItem;
				fMediaPlayer.setVideoOutput (fVideoItem);
//				fVideoItem->setSize(QSizeF(640, 480));
			}
		
	protected:
		void close() {}
};

#endif

}	// namespace

#endif	// __QGraphicsVideoItem__

