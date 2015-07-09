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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>

#include "IMessageTranslator.h"
#include "IMessage.h"
#include "Methods.h"

using namespace std;

namespace inscore
{

map<string, string>	IMessageTranslator::fFileTypeTranslationTable;

//--------------------------------------------------------------------------
IMessageTranslator::IMessageTranslator()
{
	// initializes the static 'file type translation table if not already done
	if (!fFileTypeTranslationTable.size()) {
		fFileTypeTranslationTable["txt"]	= "txtf";
		fFileTypeTranslationTable["text"]	= "txtf";
		fFileTypeTranslationTable["svg"]	= "svgf";
		fFileTypeTranslationTable["html"]	= "htmlf";
		fFileTypeTranslationTable["htm"]	= "htmlf";
		fFileTypeTranslationTable["gmn"]	= "gmnf";
		fFileTypeTranslationTable["xml"]	= "musicxmlf";
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
		fFileTypeTranslationTable["m4v"]	= "video";
		fFileTypeTranslationTable["mov"]	= "video";
		fFileTypeTranslationTable["mid"]	= "pianorollf";
		fFileTypeTranslationTable["midi"]	= "pianorollf";
		fFileTypeTranslationTable["vob"]	= "video";
        fFileTypeTranslationTable["dsp"]	= "faustdspf";
	}
}

//--------------------------------------------------------------------------
SIMessage IMessageTranslator::translateFileType(const IMessage* msg)
{
	SIMessage translated;
	string file;
	if (msg->param(1, file)) {
		size_t dotpos = file.find_last_of ('.');
		if (dotpos != string::npos) {
			string extension = file.substr(dotpos + 1);
			map<string, string>::const_iterator t = fFileTypeTranslationTable.find(extension);
			if (t != fFileTypeTranslationTable.end()) {
				string type = t->second;
				translated = IMessage::create();
				*translated = *msg;
				translated->setparam(0, type);
			}
		}
	}
	return translated;
}

//--------------------------------------------------------------------------
SIMessage IMessageTranslator::translate(const IMessage* msg)
{
	if ((msg->size() >= 2) && (msg->message() == kset_SetMethod) && (msg->param(0)->value<string>("") == "file")) {
		return translateFileType (msg);
	}
	return 0;
}


} // end namespoace
