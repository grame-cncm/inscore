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

#ifndef __IVNode__
#define __IVNode__

#include <vector>
#include "IObject.h"

namespace INScore
{

class IMessage;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IVNode;
typedef class SMARTP<IVNode>	SIVNode;

//--------------------------------------------------------------------------
/*!
	\brief an object debug virtual node
*/
class IVNode : public IObject
{
	public:	
		static const std::string fTypeString;
		/*!
			\brief gives the type string corresponding to an object
			
			An object type string is expected as the first parameter of the 'set' message.
			\return the type of the object as a string
		*/
		virtual const std::string&	getTypeString() const	{ return fTypeString; }

	protected:	
				 IVNode(const std::string& name, IObject * parent);
		virtual ~IVNode() {}

		/*! \brief virtual node del implementation
			
			A virtual node can't be deleted.
		*/
		virtual void	del ()	{}
};


/*! @} */

} // end namespoace

#endif
