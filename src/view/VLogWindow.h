/*

  INScore Project

  Copyright (C) 2013  Grame

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

#ifndef __VLogWindow__
#define __VLogWindow__

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
class QToolButton;
QT_END_NAMESPACE


namespace inscore
{

class VLogWindow : public QWidget
{
    Q_OBJECT

public:
	typedef QToolButton		TButton;
			VLogWindow(const char* name);
	
	void			append (const char* text);
	const char*		getText () const;
	virtual void	setVisible(bool visible);

private:
	TButton *		createToolButton(const QString &toolTip, const QIcon &icon, const char *member);

    QPlainTextEdit* fLogArea;
	TButton *		fClearButton;
	TButton *		fWrapButton;

public slots:
    void clear();
    void wrap();
    void wrap(bool state);
};

} // end namespace

#endif
