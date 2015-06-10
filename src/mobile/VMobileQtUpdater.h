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
#ifndef VMOBILEQTUPDATER_H
#define VMOBILEQTUPDATER_H

#include "export.h"
#include "VQtUpdater.h"

namespace inscore
{

/*!
\addtogroup ITLMobileView
@{
*/

/*!
 * \brief Extend the VQtUpdater to add log window and mobile menu in tab widget.
 */
class export VMobileQtUpdater : public VQtUpdater
{
    public:
		static libmapping::SMARTP<VQtUpdater> create()	{ return new VMobileQtUpdater(); }

		void updateTo(IScene * scene);

		/*!
		 * \brief updateTo display or not the menu on mobile device. Menu is displayed in a tabwidget.
		 * \param menu the menu object
		 */
        void updateTo (IMenu* menu);

		/*!
		 * \brief updateTo display or not the log wnidow on mobile device. Log window is displayed in a tabwidget.
		 * \param menu the log window object
		 */
        void updateTo (IApplLog * log);
};

/*!@} */

} // end namespoace

#endif // VMOBILEQTUPDATER_H
