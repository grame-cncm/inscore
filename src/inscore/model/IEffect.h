/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#pragma once

#include <iostream>

#include "IColor.h"
#include "IMessageHandlers.h"

namespace inscore
{

//--------------------------------------------------------------------------
/*!
	\brief an object graphic effect
*/
class IEffect
{
	protected:
		bool	fChanged = true;

				 IEffect() {}
		virtual ~IEffect() {}
	
	public:
		enum 		   { kNone, kBlur, kColorize, kShadow };
		enum TBlurhint { kPerformance, kQuality, kAnimation };

		typedef struct TBlur {
			int 		fRadius = 0;
			TBlurhint	fHint = kPerformance;
		} TBlur;
		
		typedef struct TColorize {
			float 		fStrength = 1.0;
			IColor		fColor;
		} TColorize;

		typedef struct TShadow {
			int 		fXOffset = 10;
			int 		fYOffset = 10;
			IColor		fColor;
			int			fBlur = 8;
		} TShadow;

		TBlur 		fBlur;
		TColorize	fColorize;
		TShadow		fShadow;

		bool	modified () const			{ return fChanged; }
		void	print (std::ostream& out) const;

		MsgHandler::msgStatus 	setEffect (const IMessage* msg);
		const IEffect *			getEffect () const				{ return this; }
		void					getEffect (IMessage* msg) const;
		int						effectType () const				{ return fEffect; }

	private:
		MsgHandler::msgStatus	blurEffect (const IMessage* msg);
		MsgHandler::msgStatus	colorizeEffect (const IMessage* msg);
		MsgHandler::msgStatus	shadowEffect (const IMessage* msg);

		bool					getColor (const IMessage* msg, int startIndex, IColor& color);
		const char*				blurHint2str (TBlurhint) const;

		int 		fEffect = kNone;
};

std::ostream& operator << (std::ostream& out, const IEffect& o);

/*! @} */

} // end namespoace

