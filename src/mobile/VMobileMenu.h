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

#ifndef VMOBILEMENUWIDGET_H
#define VMOBILEMENUWIDGET_H

#include <QWidget>
#include <string>

class QCheckBox;
class QLineEdit;

namespace inscore
{

/*!
\addtogroup ITLMobileView
@{
*/

/*!
 * \brief The VMobileMenu class. A simple menu for mobile application to pass validation when publishing on appstore.
 *
 * The menu write settings on the device to remember user choices.
 */
class VMobileMenu : public QWidget
{
		Q_OBJECT
	public:
		VMobileMenu(const char *name, QWidget *parent = 0);
		
	public slots:
		/*!
		 * \brief showFileDialog Display a file dialog to choose a file to load.
		 */
		void showFileDialog();

		/*!
		 * \brief writeSettings Write settings on the device.
		 */
		void writeSettings();

		/*!
		 * \brief closeMenu Send a message to close the menu.
		 */
		void closeMenu();

		/*!
		 * \brief loadUrlFile Action triggerd by the load button.
		 * The url read is taken from fUrlFile.
		 */
		void loadUrlFile();

		/*!
		 * \brief showChangePortNumber Show the dialog to change port number of the application.
		 */
		void showChangePortNumber();

	private:
		/*!
		 * \brief showNextTime Checkbox to show or not the menu at next startup.
		 */
		QCheckBox * showNextTime;

		/*!
		 * \brief showNextTime Checkbox to load or not the demo scene at next startup.
		 */
		QCheckBox * loadSample;

		/*!
		 * \brief fUrlFile line editor to type the url of an inscore file.
		 */
		QLineEdit * fUrlFile;

		/*!
		 * \brief readSettings Read settings if it exist.
		 */
		void readSettings();

		/*!
		 * \brief loadSampleFile Load the sample file.
		 */
		void loadSampleFile();

		/*!
		 * \brief sendLoadMsg send a load message with the file name file.
		 * \param file the filename.
		 */
		void sendLoadMsg(const char *file);
};
/*! @} */

} // end namespoace

#endif // VMOBILEMENUWIDGET_H
