/*

  INScore Project

  Copyright (C) 2016  Grame

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

#ifndef __VEditBox__
#define __VEditBox__

#include <QDialog>
#include <QPlainTextEdit>
#include <QWidget>

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

class IObject;
//--------------------------------------------------------------------------
/**
*	\brief A Qt edit dialog
*/
class VEditBox : public QDialog
{
    Q_OBJECT
	QPlainTextEdit* fTextEdit;
	IObject*		fEdited;
	
	public :
				VEditBox(QWidget* parent=0);
		virtual ~VEditBox() {}

		void edit(IObject* obj);

	protected slots:
		void  apply(bool checked = false);
		void  cancel(bool checked = false);
		void  ok(bool checked = false);
		void  clear(bool checked = false);

//		virtual void  closeEvent(QCloseEvent *e);
};

/*! @} */

} // end namespoace

#endif
