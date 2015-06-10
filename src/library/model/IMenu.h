/*

  INScore Project

  Copyright (C) 2015  Grame

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

#ifndef IMOBILEMENU_H
#define IMOBILEMENU_H

#include "IVNode.h"
#include "VMobileMenu.h"

namespace inscore {

class VMobileMenu;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IMobileMenu;
typedef class libmapping::SMARTP<IMobileMenu>		SIMobileMenu;

/*!
 * \brief The IMobileMenu class. A model class for the menu for mobile device.
 */
class IMobileMenu : public IVNode
{
    VMobileMenu * fMobileMenu;

    public:
        /// \brief creates a new IApplLog
        static SIMobileMenu create(IObject * parent)		{ return new IMobileMenu(parent); }

		/*!
		 * \brief window get the view of the class
		 * \return a VMobileMenu pointer
		 */
		VMobileMenu* window()				{ return fMobileMenu; }
		void accept (Updater* u);

    protected:
        IMobileMenu(IObject * parent);
        virtual ~IMobileMenu();

		/*!
		 * \brief setVisible To show the menu
		 * \param vis true to show the menu, false to hide the menu.
		 */
        virtual void	setVisible (bool vis);
};
/*! @} */

} // end namespoace

#endif // IMOBILEMENU_H
