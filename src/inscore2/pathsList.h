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

#ifndef __pathsList__
#define __pathsList__

#include <map>

#include "INode.h"

namespace inscore2
{

class pathsList
{
	static SINode 	delayed (SINode& node);
	static SINode 	_eval (const SINode& node);

	static SINode 	evalDelays (const SINode& node);
	static SINode 	evalDelay (const SINode& node);

	static SINode 	evalForest (const SINode& node);
	static SINode 	evalAddress (const SINode& node);
	static SINode 	evalData (const SINode& node);
	static SINode 	evalDData (const SINode& node);

	public:
				 pathsList() {}
		virtual ~pathsList() {}

	static SINode 	eval (const SINode& node, bool sumdelays=true);
};

} // end namespace

#endif
