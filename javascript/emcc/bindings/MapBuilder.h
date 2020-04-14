/*

  INScore Library
  Copyright (C) 2020  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69007 Lyon - France
  research@grame.fr

*/

#include "json.hpp"
#include "maptypes.h"


using namespace std;
using namespace libmapping;

namespace inscore
{

class IGuidoCode;
class MapBuilder {

	bool jsonTimeInterval2inscoreTimeInterval (nlohmann::json j, RationalInterval& interval);
	bool getTime2TimeRelation (nlohmann::json j, RelativeTime2RelativeTimeRelation& rel);
	bool getGraphic2TimeRelation (nlohmann::json j, RelativeTime2RelativeTimeRelation& rel);

	public:
		
		bool updateTime2TimeMap (IGuidoCode* obj, std::string jsonmap);
		bool updateGraphic2TimeMap (IGuidoCode* obj, string name, string jsonmap);

};

}
