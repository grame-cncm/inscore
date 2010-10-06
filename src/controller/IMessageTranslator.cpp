/*

  INScore Project

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>

#include "IMessageTranslator.h"
#include "IMessage.h"

using namespace std;

namespace interlude
{

map<string, string>	IMessageTranslator::fFileTypeTranslationTable;

//--------------------------------------------------------------------------
IMessageTranslator::IMessageTranslator()
{
	// initializes the static 'file type translation table if not already done
	if (!fFileTypeTranslationTable.size()) {
		fFileTypeTranslationTable["txt"]	= "txtf";
		fFileTypeTranslationTable["text"]	= "txtf";
		fFileTypeTranslationTable["html"]	= "htmlf";
		fFileTypeTranslationTable["htm"]	= "htmlf";
		fFileTypeTranslationTable["gmn"]	= "gmnf";
		fFileTypeTranslationTable["xml"]	= "gmnf";
		fFileTypeTranslationTable["jpg"]	= "img";
		fFileTypeTranslationTable["jpeg"]	= "img";
		fFileTypeTranslationTable["gif"]	= "img";
		fFileTypeTranslationTable["png"]	= "img";
		fFileTypeTranslationTable["bmp"]	= "img";
		fFileTypeTranslationTable["tiff"]	= "img";
		fFileTypeTranslationTable["wmv"]	= "video";
		fFileTypeTranslationTable["avi"]	= "video";
		fFileTypeTranslationTable["mpg"]	= "video";
		fFileTypeTranslationTable["mpeg"]	= "video";
		fFileTypeTranslationTable["mp4"]	= "video";
		fFileTypeTranslationTable["mov"]	= "video";
	}
}

//--------------------------------------------------------------------------
IMessage * IMessageTranslator::translateFileType(const IMessage* msg)
{
	IMessage * translated = 0;
	string file = msg->params()[1]->value<string>("");
	size_t dotpos = file.find_last_of ('.');
	if (dotpos != string::npos) {
		string extension = file.substr(dotpos + 1);
		map<string, string>::const_iterator t = fFileTypeTranslationTable.find(extension);
		if (t != fFileTypeTranslationTable.end()) {
			string type = t->second;
			translated = new IMessage;
			*translated = *msg;
			translated->params()[0] = new IMsgParam<string>(type);
		}
	}
	return translated;
}

//--------------------------------------------------------------------------
IMessage * IMessageTranslator::translate(const IMessage* msg)
{
	IMessage * translated = 0;
	if ((msg->size() >= 2) && (msg->message() == "set") && (msg->params()[0]->value<string>("") == "file")) {
		translated = translateFileType (msg);
	}
	return translated;
}


} // end namespoace
