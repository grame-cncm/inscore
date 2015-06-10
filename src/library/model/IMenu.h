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

#ifndef IMENU_H
#define IMENU_H

#include "IVNode.h"

class QWidget;

namespace inscore {

/*!
\addtogroup ITLModel Data Model
@{
*/

class IMenu;
typedef class libmapping::SMARTP<IMenu>		SIMenu;

/*!
 * \brief The IMenu class. A model class for a inscore menu.
 * It's an empty menu object without view.
 */
class IMenu : public IVNode
{
    public:
		/// \brief creates a new IMenu
		static SIMenu create(IObject * parent)		{ return new IMenu(parent); }

		/*!
		 * \brief window get the view of the class
		 * \return a VMobileMenu pointer
		 */
		virtual QWidget* window()				{ return 0; }
		void accept (Updater* u);

    protected:
		IMenu(IObject * parent);
		virtual ~IMenu() {}

		/*!
		 * \brief setVisible To show the menu
		 * \param vis true to show the menu, false to hide the menu.
		 */
        virtual void	setVisible (bool vis);
};
/*! @} */

} // end namespoace

#endif // IMENU_H
