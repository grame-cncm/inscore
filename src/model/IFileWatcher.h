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


#ifndef __IFileWatcher__
#define __IFileWatcher__

#include <string>
#include <map>

#include "IVNode.h"
#include "TWatcher.h"

namespace inscore
{

class IFileWatcher;
typedef class libmapping::SMARTP<IFileWatcher>	SIFileWatcher;

/*!
\addtogroup ITLModel
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a file watcher.
*
*	A file watcher monitors file modifications.
*	Each time a monitored file is modified (or renamed, or erased), the file watcher sends the associated messages.
*
*	\note Once a monitored file has been removed (or renamed), its monitoring stops.
*/
class IFileWatcher: public IVNode
{
	protected:
		TWatcher<std::string>	fWatchList;
	
				 IFileWatcher(IObject * parent);
		virtual ~IFileWatcher() {}

		/// \brief fileWatcher \c 'get' message handler
		virtual SIMessageList getMsgs (const IMessage* msg) const;

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus watchMsg (const IMessage* msg);
		/// \brief the \c 'watch+' message handler
		virtual MsgHandler::msgStatus addWatchMsg (const IMessage* msg);

		// overrides get handlers for color, position and time
		virtual void colorAble ()		{}
		virtual void positionAble ()	{}
		virtual void timeAble ()		{}

		static SIMessageList getMessages(const IMessage* source);

	public:
		static const std::string kFileWatcherType;

		TWatcher<std::string>			list()			{ return fWatchList; }
		const TWatcher<std::string>&	list() const	{ return fWatchList; }
};

/*!@} */

} // end namespoace

#endif
