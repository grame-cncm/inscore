/*

  INScore Library
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

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

#include "IObject.h"


namespace inscore
{

//--------------------------------------------------------------------------
/*! \brief the interface for iobjects
*/
class inscore_export IObjectAdapter
{
	SIObject fObject;
	
	static std::string color2htmlColor (const IColor& color) {
		std::stringstream sstr;
		sstr << "#" << std::setfill('0') << std::hex << std::setw(2) << color.getR() << std::setw(2) << color.getG() << std::setw(2) << color.getB();
		return sstr.str();
	}
	
	public:
		typedef const std::string	jsString;
	
				 IObjectAdapter() : fObject(0) {}
				 IObjectAdapter(const SIObject& object) : fObject(object) {}
		virtual ~IObjectAdapter() {}
		
		float		getXPos () const			{ return fObject->getXPos(); }
		float		getYPos () const			{ return fObject->getYPos(); }
		float		getXOrigin () const			{ return fObject->getXOrigin(); }
		float		getYOrigin () const			{ return fObject->getYOrigin(); }
		float		getZOrder() const			{ return fObject->getZOrder(); }
		float		getScale () const			{ return fObject->getScale(); }
		TFloatPoint	getPos() const			{ return fObject->getPos(); }
		float		getRotateX() const			{ return fObject->getRotateX(); }
		float		getRotateY() const			{ return fObject->getRotateY(); }
		float		getRotateZ() const			{ return fObject->getRotateZ(); }
		float		getWidth() const			{ return fObject->getWidth(); }
		float		getHeight() const			{ return fObject->getHeight(); }
		TFloatSize	getDimension() const		{ return fObject->getDimension(); }
		TFloatSize	getShear() const			{ return fObject->getShear(); }
		bool		getVisible () const			{ return fObject->getVisible(); }
		std::string getColor () const			{ return color2htmlColor (*fObject); }
		float		getAlpha() const			{ return fObject->getA() / 255.f; }
		bool		colorChanged () const		{ return ((IColor*)fObject)->modified(); }

		float		getPenWidth() const			{ return fObject->getPenWidth(); }
		std::string	getPenColor() const			{ return color2htmlColor( fObject->getPenColor()); }
        std::string	getPenStyle() const			{ return fObject->getPenStyle(); }
        std::string	getBrushStyle() const		{ return fObject->getBrushStyle(); }
		bool		brushChanged () const		{ return ((IShape*)fObject)->modified(); }

		libmapping::rational getDate () const		{ return fObject->getDate(); }
		libmapping::rational getDuration () const	{ return fObject->getDuration(); }

		void	updateWidth(float w)		{ IPosition* pos = (IPosition*)fObject; bool modified= pos->modified(); pos->setWidth (w); if (!modified) pos->cleanup(); }
		void	updateHeight(float h)		{ IPosition* pos = (IPosition*)fObject; bool modified= pos->modified(); pos->setHeight(h); if (!modified) pos->cleanup(); }

	IObjectAdapter* create(int id) 				{ return new IObjectAdapter((IObject*)id); }
	void 			del(IObjectAdapter* obj) 	{ delete obj; }
};

}
