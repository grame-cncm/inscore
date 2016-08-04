/*

  INScore Project

  Copyright (C) 2013  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/


#ifndef __IJavascript__
#define __IJavascript__


#include "IVNode.h"
#include "TScripting.h"

namespace inscore
{

class IJavascript;
typedef class libmapping::SMARTP<IJavascript>	SIJavascript;

/*!
\addtogroup ITLModel
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a javascript engine.
*
*/
class IJavascript: public IVNode
{
	protected:
		TScripting	fScripter;
		
				 IJavascript(IObject * parent);
		virtual ~IJavascript() {}

		/// \brief javascript engine \c 'get' message handler
//		virtual SIMessageList getMsgs (const IMessage* msg) const;

		/// \brief the \c 'run' message handler
		virtual MsgHandler::msgStatus runMsg(const IMessage* msg);

		// overrides get handlers for color, position and time
		virtual void colorAble ()		{}
		virtual void positionAble ()	{}
		virtual void timeAble ()		{}
		virtual	SIMessageList getAll () const	{ return IMessageList::create(); }
    
        /// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus _watchMsg(const IMessage* msg, bool add);


	public:
		static SIJavascript create(IObject * parent) { return new IJavascript(parent); }
		static const char* kName;
};

/*!@} */

} // end namespoace

#endif
