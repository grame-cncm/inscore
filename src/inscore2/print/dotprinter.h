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

#ifndef __dotprinter__
#define __dotprinter__

#include <iostream>

#include "INode.h"

namespace inscore2
{

class dotprinter
{
	std::ostream*	fStream;
	bool 			fPrintEnv;
	
	void start(std::ostream& os) const		{ os << "digraph impl {\n margin=0.05\n" << std::endl;}
	void end(std::ostream& os) const		{ os <<  "}" << std::endl; }
	void printNames (const INode* node);
	void printLinks (const INode* node);

	std::string id (const INode *) const;
	std::string label (const INode *) const;

	public:
				 dotprinter(bool printenv=false) : fStream(0), fPrintEnv(printenv) {}
		virtual ~dotprinter() {}

		void print (std::ostream& os, const INode* node);
		void print (std::ostream& os, const NList& nodes);
};

} // end namespace

#endif

