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
#ifndef VMOBILEQTINIT_H
#define VMOBILEQTINIT_H

#include "export.h"
#include "VQtInit.h"

#include <QTabWidget>

class QMainWindow;

namespace inscore
{

/*!
\addtogroup ITLMobileView
@{
*/

/*!
 * \brief A class to init Qt environnement for mobile.
 *
 * It extend VQtInit by creating a main window with a tab widget to add all scene in tab.
 * Auto screen off is desactivated on Android.
 */
class inscore_export VMobileQtInit : public VQtInit
{
    public:
        static	void		startQt ();
        static	void		stopQt ();
        /*!
         * \brief getTabWidget
         * \return the tabWidget of the main window.
         */
        static	QTabWidget*	getTabWidget();

    private:
        static QMainWindow* sMainWindow;    ///< Main window of the application. Contains the tab widget
        static QTabWidget* sTabWidget;      ///< Contains all tabs.

        /*!
         * \brief keepScreenOn Keep the the screen on when inscore is running (no sleep)
         * This function have to be called after the creation of a QMainWindow
         */
        static void keepScreenOn();
};

/*! @} */

} // end namespoace
#endif // VMOBILEQTINIT_H
