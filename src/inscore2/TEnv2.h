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

#ifndef __TEnv2__
#define __TEnv2__

#include <map>
#include <memory>
#include <ostream>


namespace inscore2
{

class INode;
typedef std::shared_ptr<INode>	SINode;

class TEnv : public std::map<std::string, SINode>
{

	public:
	typedef std::map<std::string, SINode> TEnvMap;
	
			 TEnv() {}
			 TEnv(const TEnv& e) { *this = e; }
	virtual ~TEnv() {}

	const SINode get (const std::string& name) const {
		TEnvMap::const_iterator i = this->find(name);
		SINode null;
		return (i == this->end()) ? null : i->second;
	}

	void put (const std::string& name, SINode val )	{
		(*this)[name] = val;
	}

	TEnv operator + (const TEnv& e) const	{
 		TEnv ne(e);
 		for (auto n: *this) ne.put(n.first, n.second);
 		return ne;
	}

	void operator += (const TEnv& e) {
 		for (auto n: e) this->put(n.first, n.second);
	}
	std::ostream& print (std::ostream& os) const;
};

inline std::ostream& operator<< (std::ostream& os, const TEnv& e) { return e.print(os); }

} // end namespace

#endif

