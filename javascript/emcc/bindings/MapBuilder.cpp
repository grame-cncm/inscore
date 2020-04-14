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

#include <iostream>

#include "MapBuilder.h"


using namespace std;
using namespace libmapping;
using namespace nlohmann;

namespace inscore
{

//--------------------------------------------------------------------------
bool MapBuilder::jsonTimeInterval2inscoreTimeInterval (json j, RationalInterval& interval)
{
	rational start;
	rational end;
	if (j.size() == 2) {
		for (auto& el : j.items()) {
			string val = el.value();
			if (el.key() == "start") {
				rational date(val);
				if ( !date.getDenominator() ) return false;
				start = date;
			}
			else if (el.key() == "end") {
				rational date(val);
				if ( !date.getDenominator() ) return false;
				end = date;
			}
			else return false;
		}
	}
	else return false;
	interval = RationalInterval (start, end);
	return true;
}

//--------------------------------------------------------------------------
bool MapBuilder::getTime2TimeRelation (json j, RelativeTime2RelativeTimeRelation& rel)
{
	RationalInterval from;
	RationalInterval to;
	if (j.size() == 2) {
		for (auto& el : j.items()) {
			if (el.key() == "score") {
				if (!jsonTimeInterval2inscoreTimeInterval(el.value(), from) ) return false;
			}
			else if (el.key() == "perf") {
				if (!jsonTimeInterval2inscoreTimeInterval(el.value(), to) ) return false;
			}
			else return false;
		}
	}
	else return false;
	rel.add (from, to);
	return true;
}

//--------------------------------------------------------------------------
bool MapBuilder::updateTime2TimeMap (IGuidoCode* obj, std::string jsonmap)
{
	if (jsonmap.size()) {
		stringstream sstr (jsonmap);
        json j1 = json::parse(sstr);
		RelativeTime2RelativeTimeRelation relation;
		for (auto elt: j1) {
			if (!getTime2TimeRelation (elt, relation) ) {
				cerr << "unexpected json element: " << elt << endl;
				return false;
			}
		}
//cout << "IObjectAdapter::updateTime2TimeMap: " << relation.size() << "\n" << relation << endl;
	}
	return true;
}

//--------------------------------------------------------------------------
bool MapBuilder::updateGraphic2TimeMap (IGuidoCode* obj, string name, string jsonmap)
{
	if (jsonmap.size()) {
		stringstream sstr (jsonmap);
		json j1 = json::parse(sstr);
		
		cerr << "MapBuilder::updateGraphic2TimeMap: " << name << " -> " << j1.size() << endl;
	}
	return true;
}

}
