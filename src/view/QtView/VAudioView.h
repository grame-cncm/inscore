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


#ifndef __VAudioView__
#define __VAudioView__

#include <QAudioProbe>

#include "VMediaPlayer.h"
#include "VRectView.h"
#include "VMappedShapeView.h"
#include "MouseEventAble.h"


namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

//----------------------------------------------------------------------
class TAudioReader : public QAudioProbe
{
	Q_OBJECT

	QAudioProbe * fAudioProbe;
	public:
				 TAudioReader();
		virtual ~TAudioReader() { delete fAudioProbe; }
	
		void	setSource (QMediaPlayer* player);

	protected slots:
		void processBuffer (const QAudioBuffer &buffer);
};

class IAudio;
//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IVide.
*/
class VAudioView: public VMediaPlayer, public VMappedShapeView
{
	Q_OBJECT

	MouseEventAble<QGraphicsPathItem>* item() const	{ return (MouseEventAble<QGraphicsPathItem>*)fItem; }

	public :
		using VGraphicsItemView::updateView;
		using VGraphicsItemView::updateLocalMapping;

				 VAudioView(QGraphicsScene * scene, const IAudio* h);
		virtual ~VAudioView() {}

				void initialize( IAudio * video );
		virtual void initialize (IObject* obj)					{ initialize(static_cast<IAudio*>(obj)); }
		virtual void updateView ( IAudio * video );
		virtual void updateLocalMapping (IShapeMap* shapeMap)	{ VMappedShapeView::updateGraphic2GraphicMapping(shapeMap); }
//		virtual QRectF getBoundingRect (IObject * o) const;

		virtual void mediaReady();
		virtual void mediaEnd();
		virtual void posChanged(qint64 pos);
		virtual void error(QString msg);
		virtual void updateObjectSize( IObject * )		{}

	private:
		IAudio *		fAudio;
		TAudioReader	fReader;
		float			fCacheW, fCacheH;
};


/*!@} */

} // end namespoace

#endif
