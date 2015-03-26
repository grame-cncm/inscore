/*
  Copyright (c) Grame 2010

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#include <string>

#include "ITLError.h"
#include "IMessage.h"

using namespace std;

namespace inscore
{

ITLError ITLErr;			// static ITL error output stream
ITLErrEnd ITLEndl;			// static ITL error output stream end

ITLError& operator << (ITLError& err, ITLErrEnd )
{
	std::cerr << std::endl;
	oscerr <<  OSCEnd();
	err.oscpending = false;
	return err;
}

ITLError& operator << (ITLError& err, const SIMessageList& msgs )
{
	for (unsigned int i=0; i < msgs->list().size(); i++)
		err << msgs->list()[i];
	return err;
}

ITLError& operator << (ITLError& err, const IMessage* msg )
{
	string addr = msg->extendedAddress() ? (string(msg->url()) + msg->address()) : msg->address();
	err << addr.c_str();
	if (msg->message().size()) err << msg->message();
	for (int i = 0; i < msg->size(); i++)
		msg->param(i)->print(err);
	return err;
}


} // end namespace
