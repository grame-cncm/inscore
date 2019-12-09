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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#pragma once

#include <iostream>

namespace inscore
{

class IApplLog;
class VLogWindow
{
public:
			VLogWindow(const char* name, IApplLog * logwindow) {}

	void			append (const char* text)	{ std::cerr << text << std::endl;}
	const char*		getText () const			{ return ""; }
	virtual void	setVisible	(bool visible)		{}
	virtual void	imove		(float x, float y)	{}
	virtual void	istretch	(float w, float h)	{}
	virtual void	close		()	{}
	virtual void	raise		() 	{}
	virtual void	activateWindow() {}

//	virtual bool	event(QEvent * e);

    void clear()			{}
    void wrap()				{}
    void wrap(bool state)	{}
};

} // end namespace
