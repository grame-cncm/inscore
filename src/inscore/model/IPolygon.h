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


#ifndef __IPolygon__
#define __IPolygon__

#include "IShapeMap.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IPolygon;
typedef class libmapping::SMARTP<IPolygon>	SIPolygon;
//--------------------------------------------------------------------------
/*!
*	\brief a polygon. Contains any number of points.
*/
class IPolygon : public IShapeMap
{
	std::vector<float>	fSegmentsLength;
	float				fTotalLength;

	float	getLength(const TFloatPoint& p1, const TFloatPoint& p2) const;
	void	getMetrics();

	public:
		typedef std::vector<TFloatPoint> PolygonData;

		static const std::string kPolygonType;
		static SIPolygon create(const std::string& name, IObject* parent)	{ return new IPolygon(name, parent); }

		const PolygonData&		getPoints() const			{ return fPoints; }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);
		virtual float	getXOffset () const		{ return fXMin; }
		virtual float	getYOffset () const		{ return fYMin; }
        virtual bool	date2FramePoint(const libmapping::rational& date, TFloatPoint& p) const;

	protected:
				 IPolygon( const std::string& name, IObject* parent );
		virtual ~IPolygon() {}

		void	setPoints(const PolygonData& points);

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

	private:
		PolygonData fPoints;
		float		fXMin, fYMin;
};

OSCStream& operator <<(OSCStream& s, const IPolygon::PolygonData& val);
inline std::ostream& operator <<(std::ostream& s, const IPolygon* poly) { poly->print(s); return s; }

/*! @} */

} // end namespoace

#endif
