/*

  INScore Project

  Copyright (C) 2012  Grame

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


#ifndef __TWatcher__
#define __TWatcher__

#include <map>
#include "IMessage.h"

namespace inscore
{

//--------------------------------------------------------------------------
/**
*	\brief a generic events watcher.
*
*	A watcher stores associations between arbitrary keys and messages lists.
*/
template <typename T> class TWatcher
{
	private:
		typedef typename std::map<T, SIMessageList>::iterator	iterator;

		///	\brief send a list of messages
		void send (const IMessageList* l, const bool& delay = false) const					{ if (l) l->send(delay); }

	public:
		typedef typename std::map<T, SIMessageList>	TWatchList;
		typedef typename std::map<T, SIMessageList>::const_iterator	const_iterator;
		TWatchList	fWatchList;
	
				 TWatcher()	{}
		virtual ~TWatcher() {}

		const_iterator	begin() const							{ return fWatchList.begin(); }
		const_iterator	end() const								{ return fWatchList.end(); }
		int				size() const							{ return fWatchList.size(); }

		/// \brief gives the map of messages list
		const TWatchList& map() const							{ return fWatchList; }

		const IMessageList* get (const T& key) const			{	const_iterator i = fWatchList.find(key);
																	return (i != end()) ? i->second : 0;
																}
		/// \brief set a key associated messages
		virtual void set (const T& key, SIMessageList msgs)		{	if (msgs) fWatchList[key] = msgs;
																	else {
																		iterator i = fWatchList.find(key);
																		if (i != end()) fWatchList.erase (i);
																	}
																}
		/// \brief add messages to a key associated message list
		virtual void add (const T& key, SIMessageList msgs)		{
																	SIMessageList target = fWatchList[key];
																	if (!target) {
																		if (msgs) fWatchList[key] = msgs;
																	}
																	else if (msgs)
																		target->list().push_back (msgs->list());
																}

		/// \brief clear the messages associated to key
		virtual void clear (const T& key)			{	typename TWatchList::iterator i = fWatchList.find (key);
														if (i != fWatchList.end()) fWatchList.erase(i);
													}

		///	\brief Clear the map and the associated events.
		virtual void clear()								{	fWatchList.clear(); }
		///	\brief send the messages associated to the key 'key'.
		virtual void trigger (const T& key, const bool& delay = false) const			{	typename TWatchList::const_iterator i = fWatchList.find (key);
																if (i != fWatchList.end()) send (i->second, delay);
															}
};

} // end namespoace

#endif
