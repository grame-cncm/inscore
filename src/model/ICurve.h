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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __ICurve__
#define __ICurve__

#include "IShapeMap.h"

namespace interlude
{

/*!
\addtogroup ITLModel
@{
*/

class VCurveView;
class Updater;
class ICurve;
typedef class SMARTP<ICurve>	SICurve;

//--------------------------------------------------------------------------
/*!
*	\brief a bezier cubic curve, with 3 control points. The 1st control point is (0,0).
*/
class ICurve : public IShapeMap
{
	public:
	typedef struct BezierCurve {
		std::pair<float,float> fPointA;
		std::pair<float,float> fPointB;
		std::pair<float,float> fPointC;
		std::pair<float,float> fPointD;
		bool operator != (const BezierCurve& other)
		{
			return (fPointA!=other.fPointA) || (fPointB!=other.fPointB) || (fPointC!=other.fPointC) || (fPointD!=other.fPointD);
		}
	} BezierCurve;
	
	typedef std::vector<BezierCurve> CurveData;

	private:
		CurveData fPoints;

	public:
		static const std::string kCurveType;
		static SICurve create(const std::string& name, IObject* parent)	{ return new ICurve(name, parent); }

		const CurveData&	getPoints() const			{ return fPoints; }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);

		VCurveView *	getView () const				{ return fView; }
		void			setView (VCurveView * view) 	{ fView = view; }
		VGraphicsItemView*	graphicView() const			{ return (VGraphicsItemView*)fView; }

	protected:
		VCurveView * fView;
		
				 ICurve( const std::string& name, IObject* parent );
		virtual ~ICurve() {}

		void	setPoints(const CurveData& points)		{ fPoints = points; }

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
};

IMessage& operator <<(IMessage& s, const ICurve::CurveData& val);

/*! @} */

} // end namespoace

#endif
