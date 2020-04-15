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

#include "IGuidoCode.h"
#include "MapBuilder.h"


using namespace std;
using namespace libmapping;
using namespace nlohmann;

namespace inscore
{

//--------------------------------------------------------------------------
bool MapBuilder::jsonGraphicSegment2inscoreGraphicSegment (json j, GraphicSegment& segment, float width, float height)
{
	float top, left, right, bottom;
	if (j.size() == 4) {
		for (auto& el : j.items()) {
			float val = el.value();
			if (el.key() == "left") 		left 	= 2 * val / width - 1;
			else if (el.key() == "top") 	top 	= 2 * val / height - 1;
			else if (el.key() == "right")	right 	= 2 * val / width - 1;
			else if (el.key() == "bottom")	bottom	= 2 * val / height - 1;
			else return false;
		}
	}
	else return false;
	segment = GraphicSegment (FloatInterval(left, right), FloatInterval(top, bottom));
	return true;
}

//--------------------------------------------------------------------------
bool MapBuilder::jsonTimeInterval2inscoreTimeInterval (json j, RelativeTimeSegment& segment)
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
	segment = RelativeTimeSegment (start, end);
	return true;
}

//--------------------------------------------------------------------------
bool MapBuilder::getTime2TimeRelation (json j, SRelativeTime2RelativeTimeMapping& map)
{
	RelativeTimeSegment from;
	RelativeTimeSegment to;
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
	map->add (from, to);
	return true;
}


//--------------------------------------------------------------------------
bool MapBuilder::updateTime2TimeMap (IGuidoCode* obj, const string& jsonmap)
{
	if (jsonmap.size()) {
		stringstream sstr (jsonmap);
        json j1 = json::parse(sstr);
		SRelativeTime2RelativeTimeMapping mapping = RelativeTime2RelativeTimeMapping::create();
		for (auto elt: j1) {
			if (!getTime2TimeRelation (elt, mapping) ) {
				cerr << "unexpected json element: " << elt << endl;
				return false;
			}
		}
//cout << "IObjectAdapter::updateTime2TimeMap: " << mapping->direct().size() << "\n" << mapping->direct() << endl;
		obj->setTime2TimeMap (mapping);
	}
	return true;
}

//--------------------------------------------------------------------------
bool MapBuilder::getGraphic2TimeRelation (json j, SRelativeTime2GraphicMapping& map, float width, float height)
{
	GraphicSegment graphic;
	RelativeTimeSegment time;
	if (j.size() == 2) {
		for (auto& el : j.items()) {
			if (el.key() == "graph") {
				if (!jsonGraphicSegment2inscoreGraphicSegment(el.value(), graphic, width, height) ) return false;
			}
			else if (el.key() == "time") {
				if (!jsonTimeInterval2inscoreTimeInterval(el.value(), time) ) return false;
			}
			else return false;
		}
	}
	else return false;
	map->add (time, graphic);
	return true;
}

//--------------------------------------------------------------------------
bool MapBuilder::updateGraphic2TimeMap (IGuidoCode* obj, const string& name, const string& jsonmap, float width, float height)
{
	if (jsonmap.size()) {
		stringstream sstr (jsonmap);
		json j1 = json::parse(sstr);
		SRelativeTime2GraphicMapping mapping = RelativeTime2GraphicMapping::create();
		for (auto elt: j1) {
			if (!getGraphic2TimeRelation (elt, mapping, width, height) ) {
				cerr << "unexpected json element: " << elt << endl;
				return false;
			}
		}
//cout << "MapBuilder::updateGraphic2TimeMap: " << mapping->direct().size() << "\n" << mapping->direct() << endl;
		obj->setTime2GraphicMap (name, mapping);
	}
	return true;
}

}
