/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame - Centre national de création musicale, 
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/

#pragma once

#include <exception>
#include <string>

#include "INode.h"

namespace inscore2
{

class expandValException: public std::exception
{
	std::string fWhat;
	public:
			 expandValException(const char* reason) : fWhat(reason) {}
	virtual ~expandValException() noexcept {}
	virtual const char* what() const noexcept { return fWhat.c_str(); }
};

class expandVal
{
	static SINode duration 		(const TEnv& env);
	static double step 			(const TEnv& env);
	static std::string style 	(const TEnv& env);

	public:
				 expandVal() {}
		virtual ~expandVal() {}

		static SINode 	eval 	 (const SINode& node, const TEnv& env) throw(expandValException);
};

} // end namespace
