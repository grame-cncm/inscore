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

#include "CustomScripts.h"
#include "OSCStream.h"
#include "IAppl.h"
#include "INScore.h"

#include <QVariantList>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace inscore
{

CustomScripts::CustomScripts(QObject *parent) : QObject(parent)
{
}

CustomScripts::~CustomScripts()
{
}

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
#ifdef IOS
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
#ifdef IOS
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
    cout << "javascript: ";
#ifndef NO_OSCSTREAM
    oscout << OSCStart("javascript:");
#endif
    for (QVariantList::const_iterator iter = args.constBegin(); iter != args.constEnd(); iter++) {
            if (first)
                    first = false;
            else cout << " ";

            string myString = (*iter).toString().toStdString();
            cout << myString;
#ifndef NO_OSCSTREAM
            oscout << myString;
#endif
    }
    cout << endl;
#ifndef NO_OSCSTREAM
    oscout << OSCEnd();
#endif
}

void CustomScripts::post(const QVariantList &args)
{
	INScore::MessagePtr msg = INScore::newMessage ();
	string address;
	const char* argErr = "v8::PostMsg: unknown arg type";
	const char* adrErr = "v8::PostMsg: incorrect OSC address";
	for (int i = 0; i < args.size(); i++) {
		if (i==0) {
			if (args[i].type() == QVariant::String) {
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
			if (args[i].type() == QVariant::String) {
				INScore::add(msg,  args[i].toString().toStdString().c_str());
			}
			else if (args[i].type() == QVariant::Int) {
				INScore::add(msg, args[i].toInt());
			}
			else if (args[i].type() == QVariant::UInt) {
				INScore::add(msg, args[i].toInt());
			}
			else if (args[i].type() == QVariant::Double) {
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
