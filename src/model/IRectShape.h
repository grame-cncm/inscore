/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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


#ifndef __IRectShape__
#define __IRectShape__

#include "IShape.h"
#include "IShapeMap.h"

namespace interlude
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IRectShape;
typedef class SMARTP<IRectShape>	SIRectShape;
//--------------------------------------------------------------------------
/*!
	\brief a rectangle shape.
	
	Actually, objects that support \c width and \c height messages.
*/
class IRectShape : public IShapeMap
{

	public:
		static const std::string kRectShapeType;
		static SIRectShape create(const std::string& name, IObject* parent)	{ return new IRectShape(name, parent); }

		virtual void	accept (Updater*);

	protected:
				 IRectShape( const std::string& name, IObject* parent );
		virtual ~IRectShape() {}

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
		
};

/*! @} */

} // end namespoace

#endif
