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

#include <QDialogButtonBox>
#include <QBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFont>
#include <QDebug>

#include "TILoader.h"
#include "IObject.h"
#include "VEditBox.h"

namespace inscore
{

//--------------------------------------------------------------------------
VEditBox::VEditBox(QWidget* parent) :
	QDialog(parent), fTextEdit(0), fEdited(0)
{
	setWindowFlags(windowFlags() | Qt::Tool);
	setModal(false);
	resize(300,400);

	QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	
	QDialogButtonBox* buttons = new QDialogButtonBox();
	buttons->setOrientation(Qt::Horizontal);
	QPushButton * apply = buttons->addButton(QDialogButtonBox::Apply);
	QPushButton * clear = buttons->addButton("Clear", QDialogButtonBox::ResetRole);
	QPushButton * cancel = buttons->addButton(QDialogButtonBox::Cancel);
	QPushButton * ok = buttons->addButton(QDialogButtonBox::Ok);
	buttons->setCenterButtons (true);

    connect(apply, SIGNAL(clicked(bool)), this, SLOT(apply(bool)));
    connect(clear, SIGNAL(clicked(bool)), this, SLOT(clear(bool)));
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(cancel(bool)));
    connect(ok, SIGNAL(clicked(bool)), this, SLOT(ok(bool)));
	
	fTextEdit = new QPlainTextEdit();
	fTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
	
	QTextCharFormat format;
	QFont font("Monaco", 11);
	format.setFont(font);
	fTextEdit->setCurrentCharFormat(format);
	layout->addWidget(fTextEdit);
	layout->addWidget(buttons);
}

//--------------------------------------------------------------------------
void VEditBox::edit(IObject* obj)
{
	setWindowTitle(obj->getOSCAddress().c_str());
	fEdited = obj;
	fTextEdit->setPlainText(obj->getEditString().c_str());
	show();
}

//--------------------------------------------------------------------------
void VEditBox::apply(bool) {
	QString content = fTextEdit->toPlainText();
	TILoader loader;
	loader.loadString(content.toStdString(), fEdited);
	fEdited->setEditString(content.toStdString());
}

//--------------------------------------------------------------------------
void VEditBox::clear(bool)	{ fTextEdit->setPlainText(""); }
void VEditBox::cancel(bool)	{ hide(); 	fEdited->clearEdit(); }
void VEditBox::ok(bool)		{
	hide();
	QString content = fTextEdit->toPlainText();
	TILoader loader;
	loader.loadString(content.toStdString(), fEdited);
	fEdited->setEditString(content.toStdString());
}

}

