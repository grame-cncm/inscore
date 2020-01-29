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

  Grame Research Laboratory, 11 cours Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/
#ifndef IMOBILEMENU_H
#define IMOBILEMENU_H

#include "IMenu.h"


class INScoreApplicationGlue;

namespace inscore {

/*!
	\addtogroup ITLModel Data Model
	@{
*/

class IMobileMenu;
typedef class libmapping::SMARTP<IMobileMenu>		SIMobileMenu;

/*!
 * \brief The IMobileMenu class. A menu model object for mobile. It take a QWdiget as view.
 */
class IMobileMenu : public IMenu
{
	QWidget * fMobileMenu;

	public:
		/// \brief creates a new IApplLog
		static SIMenu create(const INScoreApplicationGlue* glue, IObject * parent);

		/*!
		 * \brief window get the view of the class
		 * \return a VMobileMenu pointer
		 */
		QWidget* window();

	protected:
		IMobileMenu(IObject * parent) : IMenu(parent) {}
		virtual ~IMobileMenu();

		void setWindow(QWidget * menu) { this->fMobileMenu = menu; }
};
/*! @} */

} // end namespoace

#endif // IMOBILEMENU_H
