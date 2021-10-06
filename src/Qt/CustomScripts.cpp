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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <QVariantList>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Modules.h"
#include "CustomScripts.h"
#include "OSCStream.h"
#include "IAppl.h"
#include "INScore.h"

using namespace std;

namespace inscore
{

QString CustomScripts::version()
{
	return QT_VERSION_STR;
}

QString CustomScripts::osname()
{
#ifdef MACOS
	return "MacOS";
#endif
#ifdef WINDOWS
	return "Windows";
#endif
#ifdef __LINUX__
	return "Linux";
#endif
#ifdef ANDROID
	return "Android";
#endif
#ifdef INSCORE_IOS
	return "iOS";
#endif
}

int CustomScripts::osid()
{
#ifdef MACOS
	return 4;
#endif
#ifdef WINDOWS
	return 5;
#endif
#ifdef __LINUX__
	return 3;
#endif
#ifdef ANDROID
	return 1;
#endif
#ifdef INSCORE_IOS
	return 2;
#endif
}

QJSValue CustomScripts::readfile(const QString &filename)
{
	if (filename.isEmpty()) {
		ITLErr << "javascript : readfile invoked with incorrect arguments" << ITLEndl;
		return QJSValue::UndefinedValue;
	}
	string path = IAppl::absolutePath (filename.toStdString());
	ifstream file (path.c_str());
	if (!file.is_open()) {
		ITLErr << "javascript : readfile can't open file " << path << ITLEndl;
		return QJSValue::UndefinedValue;
	}
	file.seekg (0, file.end);
	int length = file.tellg();
	file.seekg (0, file.beg);
	char * buffer = new char [length];
	// read data as a block:
	file.read (buffer,length);
	QJSValue content(buffer);
	delete[] buffer;
	return content;
}

void CustomScripts::print(const QVariantList &args)
{
    bool first = true;
	stringstream sstr;
#ifndef NO_OSCSTREAM
    oscout << OSCStart("javascript:");
#endif
    for (QVariantList::const_iterator iter = args.constBegin(); iter != args.constEnd(); iter++) {
            if (first)
                    first = false;
            else sstr << " ";

            string myString = (*iter).toString().toStdString();
            sstr << myString;
#ifndef NO_OSCSTREAM
            oscout << myString;
#endif
    }
    fLog->write(sstr.str());
#ifndef NO_OSCSTREAM
    oscout << OSCEnd();
#endif
}

#if Qt6
# define VType(a)	(a).metaType().id()
# define VString	QMetaType::QString
# define VInt		QMetaType::Int
# define VUInt		QMetaType::UInt
# define VDouble	QMetaType::Double
#else
# define VType(a)	(a).type()
# define VString	QVariant::String
# define VInt		QVariant::Int
# define VUInt		QVariant::UInt
# define VDouble	QVariant::Double
#endif

void CustomScripts::post(const QVariantList &args)
{
	INScore::MessagePtr msg = INScore::newMessage ();
	string address;
	const char* argErr = "v8::PostMsg: unknown arg type";
	const char* adrErr = "v8::PostMsg: incorrect OSC address";
	for (int i = 0; i < args.size(); i++) {
		if (i==0) {
			if (VType(args[i]) == VString) {
				address = args[i].toString().toStdString();
			}
			else {
				cerr << adrErr << endl;
#ifndef NO_OSCSTREAM
				oscerr << adrErr;
#endif
				return;
			}
		}
		else {
			if (VType(args[i]) == VString) {
				INScore::add(msg,  args[i].toString().toStdString().c_str());
			}
			else if (VType(args[i]) == VInt) {
				INScore::add(msg, args[i].toInt());
			}
			else if (VType(args[i]) == VUInt) {
				INScore::add(msg, args[i].toInt());
			}
			else if (VType(args[i]) == VDouble) {
				INScore::add(msg, args[i].toFloat());
			}
			else {
				cerr << argErr << endl;
#ifndef NO_OSCSTREAM
				oscerr << argErr;
#endif
			}
		}
	}
	INScore::delayMessage(address.c_str(), msg);	// post the message for delayed processing
}

} // namespace
