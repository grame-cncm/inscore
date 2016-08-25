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


#ifndef __VVideoView__
#define __VVideoView__

#include <string>

#ifdef USEPHONON
#include "QGraphicsVideoItem.h"
class QGraphicsVideoItem;
#else
#include <QMediaPlayer>
#include <QGraphicsVideoItem>
#endif

#include "VGraphicsItemView.h"
#include "VMappedShapeView.h"
#include "MouseEventAble.h"


namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

class IVideo;
//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IVide.
*/
class VVideoView: public QObject, public VGraphicsItemView
{
#ifndef USEPHONON
    Q_OBJECT
#endif

	public :
		using VGraphicsItemView::updateView;
		using VGraphicsItemView::updateLocalMapping;

				 VVideoView(QGraphicsScene * scene, const IVideo* h);
#ifndef USEPHONON
		virtual ~VVideoView() { fMediaPlayer.stop(); }
#else
		virtual ~VVideoView() {}
#endif
				void initialize( IVideo * video );
		virtual void initialize (IObject* obj)					{ initialize(static_cast<IVideo*>(obj)); }
		virtual void updateView ( IVideo * video );
		virtual void updateLocalMapping (IShapeMap* shapeMap)	{ VMappedShapeView::updateGraphic2GraphicMapping(shapeMap); }


	private:
	typedef MouseEventAble<QGraphicsVideoItem> IQGraphicsVideoItem;
	QGraphicsVideoItem*			fVideoItem;
#ifndef USEPHONON
	QMediaPlayer				fMediaPlayer;
	QMediaPlayer::MediaStatus	fStatus;
	IVideo*						fVideo;
#endif

	void initFile( IVideo * video, const QString&  videoFile );
	bool error() const;

#ifndef USEPHONON
protected slots:
	void	error (QMediaPlayer::Error error);
	void	mediaStatusChanged (QMediaPlayer::MediaStatus status);
	void	stateChanged (QMediaPlayer::State state);
	void	seekableChanged(bool seekable);
	void	nativeSizeChanged(const QSizeF & size);
	void	durationChanged(qint64 duration);
	void	positionChanged(qint64 position);
#endif
};


/*!@} */

} // end namespoace

#endif
