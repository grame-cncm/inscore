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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __TILoader__
#define __TILoader__

#include <istream>
#include <string>

#include "IMessageHandlers.h"
#include "TScripting.h"
#include "INode.h"

namespace inscore
{

class IMessage;
class IObject;

//--------------------------------------------------------------------------
/*!
	\brief a base class for IAppl and IScene to provide inscore files loading service
	
*/
class TILoader
{
				int  inferVersion (const char* file) const;
	SIMessageList 	 parsev2(std::istream* stream, int line, IAppl* root) const;
				bool parse(std::istream* stream, int line, IAppl* root, int pversion, bool execute=true) const;
		virtual bool process(const SIMessageList& msgs, IObject* root, const std::string& baseaddress);

	protected:

		virtual MsgHandler::msgStatus	preprocess(const IMessage* msg, IAppl* client, const std::string& rootpath, int pversion);
		virtual MsgHandler::msgStatus	load(const IMessage* msg, IObject* client, const std::string& rootpath, int pversion);
		virtual MsgHandler::msgStatus	loadBundle(const std::string& file, const std::string& rootpath);

		bool	isBundle(const std::string& file);

	public:
				 TILoader() {}
		virtual ~TILoader() {}

		bool	loadString(const std::string& str, IObject* o, int pversion=1);

		static std::string		makeAbsolutePath( const std::string& path, const std::string& file );
		static SIMessageList	inscorev2_to_inscorev1 (const inscore2::SINode& node, TJSEngine* js);
};

} // end namespoace

#endif
