/*

  INScore Project
  Copyright (C) 2010  Grame

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

#ifndef __VQtInit__
#define __VQtInit__

#include "export.h"

#if defined(ANDROID) || defined(IOS)
#include <QTabWidget>

class QMainWindow;
#endif

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

class export VQtInit
{
	public:
	static	void		startQt ();
	static	void		stopQt ();

#if defined(ANDROID) || defined(IOS)
	/*!
	 * \brief getTabWidget
	 * \return the tabWidget of the main window.
	 */
	static	QTabWidget*	getTabWidget();

	private:
	static QMainWindow* sMainWindow;
	static QTabWidget* sTabWidget;
#ifdef ANDROID
	/*!
	 * \brief keepScreenOn Keep the the screen on when inscore is running (no sleep)
	 * This function have to be called after the creation of a QMainWindow
	 */
	static void keepScreenOn();
#endif
#endif
};

/*!@} */

} // end namespoace

#endif
