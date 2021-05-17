/*

  INScore Project

  Copyright (C) 2009,2021  Grame

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


#pragma once

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class IObject;
//--------------------------------------------------------------------------
/*!
	\brief proportional width and height management
*/
class IProportionalAsyncDims
{
	float	fRequestedWidth = 0;
	float 	fRequestedHeight = 0;
	bool	fUserDims = false;
	
	public:
				 IProportionalAsyncDims() {}
		virtual ~IProportionalAsyncDims() {}

		bool 	userDims () const 	{ return fUserDims; }

	protected:
		// real object dimensions need to be captured for the event system
		float 	fRealWidth = 0;
		float 	fRealHeight = 0;

		/// \brief Sets the width with height adjustment
		void	checkPending(IObject* obj);
		/// \brief Sets the width with height adjustment
		void	setPropWidth(IObject* obj, float width);
		/// \brief Sets the height with width adjustment
		void	setPropHeight(IObject* obj, float height);
		/// \brief Sets the height with width adjustment
		void	setDimensions(IObject* obj, float width, float height);
};

/*! @} */

} // end namespoace
