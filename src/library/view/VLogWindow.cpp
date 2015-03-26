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


#include <QApplication>
#include <QDesktopWidget>
#include <QPlainTextEdit>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QDebug>
#include "VLogWindow.h"

#include "IApplVNodes.h"

#include "INScore.h"

namespace inscore
{

#define kMargin	4

VLogWindow::VLogWindow(const char* name, IApplLog * logwindow)
	: fLogModel(logwindow)
{
    fLogArea = new QPlainTextEdit;
	fLogArea->setReadOnly(true);
	fLogArea->setLineWrapMode(QPlainTextEdit::NoWrap);
	
	QTextCharFormat format;
	QFont font("Courier", 11);
	format.setFont(font);
	fLogArea->setCurrentCharFormat(format);

    fClearButton = createToolButton(tr("Clear all"), QIcon(":/images/clear.png"), SLOT(clear()));
    fWrapButton = createToolButton(tr("Wrap mode"), QIcon(":/images/wrap.png"), SLOT(wrap()));
	
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->setAlignment(Qt::AlignLeft);
	buttonsLayout->addWidget (fClearButton);
	buttonsLayout->addWidget (fWrapButton);
	
    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setSpacing (4);
	mainLayout->setContentsMargins(kMargin, kMargin, kMargin, kMargin);
    mainLayout->addWidget(fLogArea);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
    setWindowTitle( tr(name) );

	QRect r = QApplication::desktop()->screenGeometry();
	fScreenDim = qMin( r.width(), r.height() );
	fScreenCenter = r.center();
}

#define kButtonSize	24

VLogWindow::TButton * VLogWindow::createToolButton(const QString &toolTip, const QIcon &icon, const char *member)
{
    TButton *button = new TButton(this);
    button->setFixedSize(kButtonSize, kButtonSize);
    button->setToolTip(toolTip);
	button->setToolButtonStyle(Qt::ToolButtonIconOnly);
    button->setIcon(icon);
    button->setIconSize(QSize(kButtonSize, kButtonSize));
	button->setFocusPolicy(Qt::NoFocus);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

const char*	VLogWindow::getText () const
{
	return fLogArea->toPlainText().toUtf8().constData();
}

int VLogWindow::local2screen (float v) const { return v * fScreenDim / 2; }
float VLogWindow::screen2local (int v) const { return float(v) * 2 / fScreenDim; }

bool VLogWindow::event(QEvent * e)
{
	switch (e->type()) {
		case QEvent::Move: {
				fLogModel->setX( screen2local(x() - fScreenCenter.x() + (width()/2.f)) );
				fLogModel->setY( screen2local(y() - fScreenCenter.y() + (height()/2.f)) );
			}
			break;
		case QEvent::Resize: {
				fLogModel->setW( screen2local(width()) );
				fLogModel->setH( screen2local(height()) );
			}
			break;
		default:
			;
	}
	return QWidget::event (e);
}


void VLogWindow::imove (float ox, float oy)
{
	int x = fScreenCenter.x() + ox * fScreenDim / 2.0f - (width()/2);
	int y = fScreenCenter.y() + oy * fScreenDim / 2.0f - (height()/2);
	if ((x != this->x()) || (y != this->y()))
		move( x, y );
}

void VLogWindow::istretch (float ow, float oh)
{
	int w = ow * fScreenDim / 2.0f;
	int h = oh * fScreenDim / 2.0f;
	if ((w != this->width()) || (h != this->height()))
		resize( w, h );
}

void VLogWindow::closeEvent(QCloseEvent * ) {
	INScore::MessagePtr msg = INScore::newMessage ("show");
	INScore::add (msg, 0);
	INScore::postMessage ("/ITL/log", msg);
}

void VLogWindow::setVisible(bool visible) {
	QWidget::setVisible (visible);
	if (visible) {
		raise ();
	}
}


void VLogWindow::clear()
{
	fLogArea->setPlainText("");
}

void VLogWindow::wrap()
{
	QPlainTextEdit::LineWrapMode mode = (fLogArea->lineWrapMode() == QPlainTextEdit::NoWrap) ?
					QPlainTextEdit::WidgetWidth : QPlainTextEdit::NoWrap;
	fLogArea->setLineWrapMode(mode);
}

void VLogWindow::wrap(bool state)
{
	QPlainTextEdit::LineWrapMode mode = state ? QPlainTextEdit::WidgetWidth : QPlainTextEdit::NoWrap;
	fLogArea->setLineWrapMode(mode);
}

void VLogWindow::append (const char* text)
{
	fLogArea->appendPlainText(text);
}

} // end namespace
