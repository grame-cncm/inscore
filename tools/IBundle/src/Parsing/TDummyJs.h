/*
  INScore Project

  Copyright (C) 2009,2016  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/
#ifndef TDUMMYJS_H
#define TDUMMYJS_H

#include <string>
#include <sstream>
#include "IMessage.h"
#include "smartpointer.h"

namespace inscore{
class TEnv;
typedef libmapping::SMARTP<TEnv> STEnv;
}

namespace ibundle {

/*!
 * \brief The TDummyJs class provides a dummy Javascript engine to capture
 * variable and javascript method declaration while preparing a bundle.
 * To do so, the message evaluated by TDummyJS are always:
 * /ITL/bundle js "JS_CODE";
 * where JS_CODE is the code contains in the javascript section where double quote have been escaped
 * ( \\ are inserted in front of them).
 *
 *	Once captured, the collected javascript code will be parsed by ScriptParser
 * to find any reference to a ressources or a script. At the end of the bundle
 * creation when regenerating inscore scripts, the collected javascript will be restored
 * with the correct modification to filepaths.
 */
class TDummyJs
{
	std::string fRootPath;
	std::string fVars;
public:
	TDummyJs();
	virtual ~TDummyJs();

	void	Initialize	();
	void	bindEnv		(const inscore::STEnv& env);

	bool	bindEnv  (std::stringstream& s, const std::string& name, const inscore::IMessage::argPtr& val);
	void	bindEnv  (std::stringstream& s, const std::string& name, const inscore::IMessage::argslist& values);

	bool	eval		(int line, const char* script, std::string& outStr);
	void	setRootPath	(const char* path);
};



} // End namespace
#endif // TDUMMYJS_H
