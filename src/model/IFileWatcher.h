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
	public:
		static const std::string kFileWatcherType;
		
		virtual void	print(std::ostream& out) const;
		
		/// \brief clear the monitoring list.
		virtual void clear() = 0;
				
	protected:
	
		IFileWatcher(IObject * parent);
		virtual ~IFileWatcher() {}
	

		typedef struct WatcherAssociation
		{
			WatcherAssociation() : mFileName("") {}
			WatcherAssociation(const std::string& fileName, const IMessage& message)
								 : mFileName(fileName), mMessage(message) {}
			std::string mFileName;
			IMessage mMessage;
		} WatcherAssociation;
		

		/// \brief fileWatcher \c 'get' message handler
		virtual IMessageList getMsgs (const IMessage* msg) const;

		/*!
		*	\brief Starts notifying changes of the file 'fileName' for the attention of object whose address is 'oscAddress'.
		*/
		virtual void addAssociation(const WatcherAssociation& association) = 0;

		/*!
		*	\brief Stops notifying object whose address is 'oscAdress' on changes of the file 'fileName'.
		*/
		virtual void remove(const WatcherAssociation& association) = 0;
	
		/*!
		*	\brief Stops notifying object whose address is 'oscAdress' on any file changes.
		*/
		virtual void remove(const std::string& oscAddress) = 0;
		
		virtual void getList(std::vector<WatcherAssociation>& outAssociations) const = 0;


		/// \brief the \c 'add' message handler
		virtual MsgHandler::msgStatus addMsg (const IMessage* msg);
		/// \brief the \c 'remove' message handler
		virtual MsgHandler::msgStatus removeMsg (const IMessage* msg);
		/// \brief the \c 'clear' message handler
		virtual MsgHandler::msgStatus clearMsg (const IMessage* msg);
		

		// overrides get handlers for color, position and time
		virtual void colorAble ()		{}
		virtual void positionAble ()	{}
		virtual void timeAble ()		{}

		static bool buildMessage(const IMessage& source,IMessage& target);
};

/*!@} */

} // end namespoace

#endif
