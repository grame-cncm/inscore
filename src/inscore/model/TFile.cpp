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

#include <fstream>

#include <QDir>

#include "TFile.h"
#include "IAppl.h"
#include "IScene.h"
#include "ITLError.h"
#include "IUrlIntermediateObject.h"
#include "OSCAddress.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
TFile::TFile(IScene* scene, const std::string& pathname ) 
	: fFilePath (pathname), fPathChanged (true), fScene(scene), fData(0), fDataSize(0)
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
char* TFile::readfile (const std::string& path)
{
	char * buffer = 0;
	ifstream file;
	file.open (path.c_str(), ifstream::binary);
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
	char * content = readfile(fFilePath);
	if (content) {
		out << content;
		delete [] content;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool TFile::read (std::string& str) const
{
	char * content = readfile(fFilePath);
	if (content) {
		str = content;
		delete [] content;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
void TFile::setData(const char* data, int size)
{
	if (fData) delete [] fData;
	fData = new char[size+1];
	fDataSize = size;
	if (fData) {
		memcpy(fData, data, size);
		fData[size] = 0;			// ensure C string compatibility
	}
}

//--------------------------------------------------------------------------
void TFile::print (ostream& out) const
{
	out << "file: \"" << getFile() << "\"" << endl;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus TFile::set (const IMessage* msg )	
{ 
	if (msg->size() == 2) {
		string type, path;
		if (!msg->param(0, type) || !msg->param(1, path)) return MsgHandler::kBadParameters;
		
        // the creation of a url file should not go through TFile::set.
        // this means that the current object is not a URLIntermediate, it is a file whose path has been change to an url
        // we then have to destroy it and re-create the URLIntermediate (we send the message in the form "/urlname set url type path"
        if(Tools::isurl(path) || Tools::isurl(fScene->getRootPath()))
        {
            SIMessage newmsg = IMessage::create(msg->address(), msg->message());
            newmsg->add(IUrlIntermediateObject::kUrlIntermediateType);
            newmsg->add(type);
            newmsg->add(path);
			newmsg->send();
			return MsgHandler::kProcessed;
        }
        
		else if ( path.size())
		{
            std::string completePath = fScene ? fScene->absolutePath(path) : IAppl::absolutePath(path);
			setFile( completePath );
			fFile = path;
			return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;
}

}
