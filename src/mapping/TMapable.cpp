/*

  INScore Project
  Copyright (C) 2009,2010  Grame

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

#include <string.h>

#include "TMapable.h"
#include "TSegment.h"
#include "TSegmentation.h"

using namespace std;

namespace inscore {

//______________________________________________________________________________
SRelativeTime2GraphicMapping TMapable::find (const std::string& name)
{
	iterator found = fMappings.find(name);
	return (found == fMappings.end()) ? 0 : found->second;
}

const SRelativeTime2GraphicMapping TMapable::find (const std::string& name) const
{
	const_iterator found = fMappings.find(name);
	return (found == fMappings.end()) ? 0 : found->second;
}

//______________________________________________________________________________
SGraphic2GraphicMapping TMapable::findS2M (const std::string& name)
{
	m_iterator found = fSlave2MasterMappings.find(name);
	return (found == fSlave2MasterMappings.end()) ? 0 : found->second;
}

const SGraphic2GraphicMapping TMapable::findS2M (const std::string& name) const
{
	m_const_iterator found = fSlave2MasterMappings.find(name);
	return (found == fSlave2MasterMappings.end()) ? 0 : found->second;
}


//______________________________________________________________________________
bool TMapable::removeMapping(const std::string& name) 
{ 
	if (name.empty()) fAutoMap = false;
	return fMappings.erase(name)==1; 
}

//______________________________________________________________________________
void TMapable::UseGraphic2GraphicMapping (bool val, std::string masterName)
{
    if(masterName.size())
    {
        b_iterator it = fUseMapping.find(masterName);
        if(it != fUseMapping.end())
            it->second = val;
        else
            fUseMapping.insert(std::pair<std::string, bool>(masterName, val));
    }
    else
    {
        for(b_iterator it = fUseMapping.begin(); it != fUseMapping.end();it++)
            it->second = val;
    }
}

//______________________________________________________________________________
void TMapable::setSlave2MasterMapping (const std::string& name, const SGraphic2GraphicMapping map)
{
    if(name.size())
    {
        m_iterator it = fSlave2MasterMappings.find(name);
        if(it != fSlave2MasterMappings.end())
            it->second = map;
        else
            fSlave2MasterMappings.insert(std::pair<std::string, SGraphic2GraphicMapping>(name, map));
    }
}
}
