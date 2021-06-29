/*

  INScore Library
  Copyright (C) 2021  Grame

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
*/

#include <emscripten.h>

#include "IMessage.h"

using namespace inscore;
using namespace std;

namespace jscall
{

std::string getGuidoVersion() {
	float v = EM_ASM_DOUBLE( { return getGuidoVersion(); });
	return v ? to_string(v) : "not available";
}

std::string getMusicXmlVersion() {
	float v = EM_ASM_DOUBLE( { return getMusicXMLVersion(); });
	return v ? to_string(v) : "not available";
}

std::string getFaustVersion() {
	float v = EM_ASM_DOUBLE( { return getFaustVersion(); });
	return v ? to_string(v) : "not available";
}

bool loadMsg(const IMessage* msg)
{
	if (msg->size() == 1) {
		string srcfile;
		if (msg->param(0, srcfile)) {
			EM_ASM( { TAppl.load(Module.UTF8ToString($0)); }, srcfile.c_str());
			return true;
		}
	}
	return false;
}

void save(const char* name, const string& text)
{
	EM_ASM( { Download.text(Module.UTF8ToString($0), Module.UTF8ToString($1)); }, name, text.c_str());
}


}
