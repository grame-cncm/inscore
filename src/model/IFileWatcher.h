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

namespace inscore
{

class IFileWatcher;
typedef class libmapping::SMARTP<IFileWatcher>	SIFileWatcher;

/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief an abstract file watcher.
*
*	A file watcher monitors file modifications for the attention of an model object, defined by its osc address.
*	Each time a monitored file is modified (or renamed, or erased), the file watcher posts a 'reload' message for
*	the attention of the model object(s) concerned.
*
*	The file watcher can monitor several files for 1 object ; it can also monitor 1 file for several objects.
*
*	\note Once a monitored file has been removed (or renamed), its monitoring stops.
*/
class IFileWatcher: public IVNode
{
	protected:
		typedef std::map<std::string, SIMessageList>	TWatchList;
		TWatchList	fWatchList;
		using IObject::set;
		using IObject::add;
	
				 IFileWatcher(IObject * parent);
		virtual ~IFileWatcher() {}

		/// \brief fileWatcher \c 'get' message handler
		virtual SIMessageList getMsgs (const IMessage* msg) const;

		/// \brief set a file associated messages
		virtual void set (const std::string& file, SIMessageList msg);
		/// \brief add messages to a file associated message list
		virtual void add (const std::string& file, SIMessageList msg);
		/// \brief clear the messages associated to file
		virtual void clear (const std::string& file);

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus watchMsg (const IMessage* msg);
		/// \brief the \c 'watch+' message handler
		virtual MsgHandler::msgStatus addWatchMsg (const IMessage* msg);

		// overrides get handlers for color, position and time
		virtual void colorAble ()		{}
		virtual void positionAble ()	{}
		virtual void timeAble ()		{}

		static SIMessageList buildMessage(const IMessage* source);

	public:
		static const std::string kFileWatcherType;

		///	\brief Clear the files list and the associated events.
		virtual void clear()								{ fWatchList.clear(); }
		///	\brief send the messages associated to the file 'fileName'.
		virtual void trigger (const std::string& fileName) const;
};

/*!@} */

} // end namespoace

#endif
