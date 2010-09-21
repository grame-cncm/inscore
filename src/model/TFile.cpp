/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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

#include "IAppl.h"
#include "ITLError.h"
#include "TFile.h"

using namespace std;

namespace interlude
{

//--------------------------------------------------------------------------
TFile::TFile( const std::string& pathname ) : fFilePath (pathname)
{
}

//--------------------------------------------------------------------------
int TFile::getLength (ifstream& f)
{
	  int pos = f.tellg();
	  f.seekg (0, ios::end);
	  int length = f.tellg();
	  f.seekg (pos, ios::beg);
	  return length;
}

//--------------------------------------------------------------------------
char* TFile::read (const std::string& path)
{
	char * buffer = 0;
	ifstream file;
	file.open (path.c_str(), ifstream::in);
	if (file.is_open()) {
		int length = getLength(file);
		if (length) {
			// allocate memory:
			buffer = new char [length+1];
			// read data as a block:
			file.read (buffer,length);
			buffer[length] = 0;
		}
		else {
			buffer = new char [1];
			buffer[0] = 0;
		}
		file.close();
	}
	else ITLErr << "can't open file :" << path << ITLEndl;
	return buffer;
}

//--------------------------------------------------------------------------
bool TFile::read (ostream& out) const
{
	char * content = read(fFilePath);
	if (content) {
		out << content;
		delete content;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool TFile::read (std::string& str) const
{
	char * content = read(fFilePath);
	if (content) {
		str = content;
		delete content;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
void TFile::print (ostream& out) const
{
	out << "file: \"" << getFile() << "\"" << endl;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus TFile::set (const IMessage* msg )	
{ 
	if (msg->params().size() == 2) {
		std::string file = msg->params()[1]->value<std::string>("");
		std::string completePath = IAppl::absolutePath(file);
		if ( file.size())
		{
			setFile( completePath );
			return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;
}

}
