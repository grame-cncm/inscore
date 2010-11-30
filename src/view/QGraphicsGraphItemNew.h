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


#ifndef __QGraphicsGraphItemNew__
#define __QGraphicsGraphItemNew__

#include <QGraphicsRectItem>
#include "GraphicSignal.h"

namespace INScore
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
class QGraphicsGraphItemNew : public QGraphicsRectItem
{
	private:
		const ParallelSignal*	fSignals;

	public :
				 QGraphicsGraphItemNew(QGraphicsItem * parent = 0);
		virtual ~QGraphicsGraphItemNew();

		void					setSignal (const ParallelSignal* sig)		{ fSignals = sig; }
		const ParallelSignal*	signal() const								{ return fSignals; }

		void	drawSignal( ParallelSignal * sig, QPainter * painter, unsigned short size, float stepWidth, float yHeight);
		void	paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * );		

	protected :
};

} // end namespoace

#endif
