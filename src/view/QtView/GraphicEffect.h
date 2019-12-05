/*

  INScore Project

  Copyright (C) 2011  Grame

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


#pragma once

//#include "IMessageHandlers.h"

class QGraphicsEffect;

namespace inscore
{

class IEffect;

/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief an abstraction layer over Qt graphic effects.
*/
class GraphicEffect
{
//	QGraphicsEffect * fEffect;
	
	QGraphicsEffect *	buildBlurEffect 	(const IEffect* effect);
	QGraphicsEffect *	buildColorizeEffect (const IEffect* effect);
	QGraphicsEffect *	buildShadowEffect 	(const IEffect* effect);

//	QGraphicsEffect *	buildBlurEffect (const IMessage* msg);
//	QGraphicsEffect *	buildColorizeEffect (const IMessage* msg);
//	QGraphicsEffect *	buildShadowEffect (const IMessage* msg);

	public :
				 GraphicEffect () {} //: fEffect(0) {}
//				 GraphicEffect (QGraphicsEffect * effect) : fEffect (effect) {}
		virtual ~GraphicEffect () {}

//		MsgHandler::msgStatus set (const IMessage* msg);
		QGraphicsEffect *	set (const IEffect* effect);
//		QGraphicsEffect *	get () const;
//		void				get (IMessage* msg) const;
};


/*!@} */

} // end namespoace
