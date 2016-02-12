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
#include <cmath>

#include "BundleLog.h"

namespace ibundle{

BundleLog::BundleLog()
	: fActive(false)
{

}

void BundleLog::setActive(bool active)
{
	fActive = active;
}

void BundleLog::section(std::string sectionName)
{
	fTab = 0;
	printLog("⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼\n");
	size_t space = sectionName.length()>50? 0 : 50 - sectionName.length();
	sectionName.insert(0,0>floor(space/2.)?0:floor(space/2.), ' ');
	printLog(sectionName);
	printLog("\n⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼\n");
	fTab = 1;
}


void BundleLog::exitSection()
{
	fTab=0;
	printLog("\n                -- -- -- -- -- \n\n");
}

void BundleLog::subSection(std::string subSectionName)
{
	printLog("\n ⏤ "+subSectionName+" ⏤ \n");
	fTab++;
}

void BundleLog::exitSubSection()
{
	if(fTab>1)
		fTab--;
}


void BundleLog::printLog(std::string msg)
{
	if(fActive){
		size_t pos=0;
		while(pos < msg.size()){
			pos = msg.find('\n', pos);
			if(pos+1 >= msg.size() || pos+1==0)
				break;

			for (int i = 0; i < fTab; ++i)
				msg.insert(pos+1, "  ");
			pos += fTab+1;
		}

		if(fNewLine)
			for (int i = 0; i < fTab; ++i)
				msg.insert(0, "  ");
		fNewLine = msg.at(msg.length()-1) == '\n';

		printLog<std::string>(msg);
	}
}

void BundleLog::error(std::string msg) const
{
	std::cerr<<"Error: "<<msg<<std::endl;
}

void BundleLog::warn(std::string msg) const
{
	std::cerr<<"Warning: "<<msg<<std::endl;
}

} // end namespace
