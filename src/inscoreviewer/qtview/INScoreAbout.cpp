/*

  Interlude Prototype
  Copyright (C) 2009,2010  Grame

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

#include <QBitmap>
#include <QLabel>
#include <QString>

#include "INScore.h"
#include "INScoreAbout.h"

using namespace inscore;

static const char* kFontName = "Helvetica";
static int kFontSize  = 9;

//_______________________________________________________________________
INScoreAbout::INScoreAbout (const QPixmap & pixmap) : QSplashScreen (pixmap)
{
    setMask (pixmap.mask());

#ifdef linux
	kFontName = "FreeSans";
#endif
#ifdef WIN32
	kFontSize = 7;
#endif
#ifdef ANDROID
	kFontSize = 7;
#endif
	QFont font (kFontName, kFontSize);
	font.setPixelSize(kFontSize);

	int h = height();
	QString version("INScore v.");
	version += INScore::versionStr();
	QLabel* text = new QLabel(version, this);
	text->setFont(font);
	text->move(27, h - 45);

	QString qt("Using Qt v.");
	qt += qVersion();
	text = new QLabel(qt, this);
	text->setFont(font);
	text->move(22, h - 33);

	QString guido("Using Guido Engine v.");
	guido += INScore::guidoversion();
	text = new QLabel(guido, this);
	text->setFont(font);
	text->move(17, h - 21);
}
