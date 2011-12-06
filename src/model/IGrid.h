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


#ifndef __IGrid__
#define __IGrid__

#include <string>

#include "TRect.h"
#include "IRectShape.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
typedef class SMARTP<IGrid>	SIGrid;
//--------------------------------------------------------------------------
/*!
	\brief a rectangle shape.
*/
class IGrid : public IRectShape
{
	TIntSize	fDimensions;
//	int		fColumns, fRows;
	float	fXBorder, fYBorder;
	int		fOrder;
	
	public:
		enum order { kLeftRight, kTopBottom };
		
		static const std::string kGridType;
		static SIGrid create(const std::string& name, IObject* parent)	{ return new IGrid(name, parent); }

		virtual void	accept (Updater*);

		int		getColumns() const		{ return fDimensions.width(); }
		int		getRows() const			{ return fDimensions.height(); }
		float	getXBorder() const		{ return fXBorder; }
		float	getYBorder() const		{ return fYBorder; }
		int		getOrder() const		{ return fOrder; }
		std::string getOrderStr() const	{ return order2string(fOrder); }
		const TIntSize&	getDims() const { return fDimensions; }

	protected:
				 IGrid( const std::string& name, IObject* parent );
		virtual ~IGrid() {}	

		void	setColumns( int c) 		{ localMapModified(true); fDimensions.setWidth(c); }
		void	setRows( int r) 		{ localMapModified(true); fDimensions.setHeight(r); }
		void	setXBorder( float xb)	{ localMapModified(true); fXBorder = xb; }
		void	setYBorder(float yb)	{ localMapModified(true); fYBorder = yb; }
		void	setOrder(int order)		{ localMapModified(true); fOrder = order; }
		void	setOrderStr(const std::string& o) 	{ setOrder (string2order(o.c_str())); }


		const char*	order2string(int order) const;
		int			string2order(const char* order) const;

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
