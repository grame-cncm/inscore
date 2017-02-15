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


#ifndef __IObjectFactory__
#define __IObjectFactory__

#include <string>
#include <map>
#include "IModelTypes.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief a factory producing objects for the data model.
*/
class IObjectFactory
{
	typedef SIObject (*TCreateMethod)(const std::string& name , IObject* parent);
	static std::map<std::string, TCreateMethod> fCreateMap;

	public:
	
	static void init();		///< intended to initialise the methods map

	/*! \brief creates an IObject
		\param name the object name
		\param type the object type
		\param parent its parent object
	*/
	static SIObject create(const std::string& name , const std::string& type, IObject* parent);

};

/*! @} */

} // end namespoace

#endif
