/*

  INScore Project

  Copyright (C) 2015  Grame

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


#ifndef __QGraphicsGraphItemRadial__
#define __QGraphicsGraphItemRadial__

#include <QGraphicsRectItem>

namespace inscore
{

class ParallelSignal;

/*!
\addtogroup ITLView
@{
*/

/**
*	\brief A QGraphicsItem displaying data in a graph.

	The basic rendering principle :
	the graphic area is sliced in 'stripes'
*
*/
class QGraphicsGraphItemRadial : public QGraphicsRectItem
{
	private:
		const ParallelSignal*	fSignals;

	public :
				 QGraphicsGraphItemRadial(QGraphicsItem * parent = 0);
		virtual ~QGraphicsGraphItemRadial();

		void					setSignal (const ParallelSignal* sig)		{ fSignals = sig; }
		const ParallelSignal*	signal() const								{ return fSignals; }

		/*!
			\brief draws the signals as radial graphs
			\param sig a set of parrallel signals
			\param painter a qt painter
			\param size the signals size
			\param step angular step of each graphic frame
			\param xr the drawing area x center
			\param yr the drawing area y center
		*/
		void	drawSignal( ParallelSignal * sig, QPainter * painter, unsigned short size, double step, double xr, double yr);
		void	paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * );

	protected :
};

} // end namespoace

#endif
