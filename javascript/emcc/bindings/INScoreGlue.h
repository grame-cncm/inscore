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

#include <string>
#include <iostream>

# ifdef INScore_EXPORTS
#  define inscore_export		 __attribute__ ((visibility("default")))
# else
#  define inscore_export		
# endif

#include "INScore.h"


namespace inscore
{

//--------------------------------------------------------------------------
class JSGraphicUpdate : public GraphicUpdateListener
{
	public :
		virtual void update() 	{ std::cerr << "JSGraphicUpdate::update" << std::endl; }
};

//--------------------------------------------------------------------------
class INScoreJSGlue: public INScoreApplicationGlue
{
	public :
				 INScoreJSGlue() {}
		virtual ~INScoreJSGlue() {}

		virtual void 	showMouse (bool state);
		virtual bool 	openUrl (const std::string& url);
		virtual void	startView () 					{}
		virtual void	stopView  () 					{}

		virtual std::string viewVersion() const 	{ return "JSView version 0.1a"; }
		virtual std::string getIP() const			{ return "localhost"; }
};

}
