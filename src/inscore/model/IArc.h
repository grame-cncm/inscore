/*

  INScore Project

  Copyright (C) 2016  Grame

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


#ifndef __IArc__
#define __IArc__

#include "IRectShape.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IArc;
typedef class libmapping::SMARTP<IArc>	SIArc;
//--------------------------------------------------------------------------
/*!
	\brief an ellipse.
*/
class IArc : public IRectShape
{
	float	fStartAngle, fEndAngle;
	bool	fCloseArc;

	public:
		static const std::string kArcType;
		static SIArc create(const std::string& name, IObject* parent)	{ return new IArc(name, parent); }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);
				float	getStartAngle () const			{ return fStartAngle; }
				float	getEndAngle () const			{ return fEndAngle; }
				bool	closed () const					{ return fCloseArc; }

	protected:
				 IArc( const std::string& name, IObject* parent );
		virtual ~IArc() {}

		// the set msg handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
		/// \brief the 'get' form without parameter
		virtual SIMessageList getSetMsg() const;

		virtual void setStartAngle (float angle)		{ fStartAngle = angle; }
		virtual void setEndAngle (float angle)			{ fEndAngle = angle; }
		virtual void dStartAngle (float angle)			{ setStartAngle(fStartAngle + angle); }
		virtual void dEndAngle (float angle)			{ setEndAngle  (fEndAngle + angle); }
		virtual void setClosed (bool state)				{ fCloseArc = state; }
};

/*! @} */

} // end namespoace

#endif
