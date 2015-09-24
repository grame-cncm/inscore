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


#ifndef __IHtml__
#define __IHtml__

#include <string>

#include "IText.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IHtml;
typedef class libmapping::SMARTP<IHtml>	SIHtml;
//--------------------------------------------------------------------------
/*!
	\brief a text element of the model
*/
class IHtml : public IText
{
	protected:
		std::string	fHtml;

	public:		
		static const std::string kHtmlType;
		static SIHtml create(const std::string& name, IObject * parent)	{ return new IHtml(name, parent); }

		virtual void		accept (Updater*);

	protected:
				 IHtml( const std::string& name, IObject * parent );
		virtual ~IHtml() {}
};

/*! @} */

} // end namespoace

#endif
