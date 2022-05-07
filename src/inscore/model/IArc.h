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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
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
	float	fStartAngle, fAngularRange;
	float	fArcLen, fR1, fR2;
	bool	fCloseArc;

	float   arcLength () const;			// computes an approximation of the arc length
	float	getR(float angle) const;	// computes the radius at a given angle
    bool	arc2FramePoint(float ratio, TFloatPoint& p) const;

	public:
		static const std::string kArcType;
		static SIArc create(const std::string& name, IObject* parent)	{ return new IArc(name, parent); }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);
				float	getStartAngle () const			{ return fStartAngle; }
				float	getAngularRange () const		{ return fAngularRange; }
				bool	closed () const					{ return fCloseArc; }

        virtual bool date2FramePoint(const libmapping::rational& date, TFloatPoint& p) const;
		virtual void setWidth(float width, bool scenewidth, bool sceneheight)		{ IRectShape::setWidth(width, scenewidth, sceneheight); newData(true); }
		virtual void setHeight(float height, bool scenewidth, bool sceneheight)		{ IRectShape::setHeight(height, scenewidth, sceneheight); newData(true); }

	protected:
				 IArc( const std::string& name, IObject* parent );
		virtual ~IArc() {}

		// the set msg handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
		/// \brief the 'get' form without parameter
		virtual SIMessageList getSetMsg() const;

		virtual void setStartAngle (float angle)		{ fStartAngle = angle; }
		virtual void setAngularRange(float angle)		{ fAngularRange = angle; }
		virtual void dStartAngle (float angle)			{ setStartAngle (fStartAngle + angle); }
		virtual void dRange (float angle)				{ setAngularRange (fAngularRange + angle); }
		virtual void setClosed (bool state)				{ fCloseArc = state; }
};

/*! @} */

} // end namespoace

#endif
