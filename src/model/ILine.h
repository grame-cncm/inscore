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


#ifndef __ILine__
#define __ILine__

#include "IShapeMap.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class VLineView;
class Updater;
class ILine;
typedef class SMARTP<ILine>	SILine;

//--------------------------------------------------------------------------
/*!
*	\brief a bezier cubic line, with 3 control points. The 1st control point is (0,0).
*/
class ILine : public IShapeMap
{
	VLineView*	fView;
	TFloatPoint fPoint;

	public:
		static const std::string kLineType;
		static SILine create(const std::string& name, IObject* parent)	{ return new ILine(name, parent); }

		const TFloatPoint&	getPoint() const			{ return fPoint; }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);

		VLineView *		getView () const			{ return fView; }
		void			setView (VLineView * view) 	{ fView = view; }
		VGraphicsItemView*	graphicView() const		{ return (VGraphicsItemView*)fView; }

	protected:
				 ILine( const std::string& name, IObject* parent );
		virtual ~ILine() {}

		void	setPoint(const TFloatPoint& p)		{ fPoint = p; }

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
