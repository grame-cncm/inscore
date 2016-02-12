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
#ifndef BUNDLELOG_H
#define BUNDLELOG_H

#include <string>
#include <iostream>

namespace ibundle {

class BundleLog
{
	bool fActive;

	int fTab;
	bool fNewLine;

public:
	BundleLog();

	void setActive(bool active = true);

	void section(std::string sectionName);
	void exitSection();

	void subSection(std::string subSectionName);
	void exitSubSection();

	template <typename T>
	void printLog(T msg){if(fActive) std::cout<<msg;}

	void printLog(std::string msg);
	void printLog(const char* msg){printLog(std::string(msg));}

	void error(std::string msg) const;
	void warn(std::string msg) const;
};

template <typename T>
BundleLog& operator << (BundleLog& out, T msg) {out.printLog(msg); return out;}

} // end namespace
#endif // BUNDLELOG_H
