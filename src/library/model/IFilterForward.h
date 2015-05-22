/*

  INScore Project

  Copyright (C) 2015  Grame

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
#ifndef IFILTERFORWARD_H
#define IFILTERFORWARD_H

#include <string>
#include <vector>
#include "IVNode.h"

namespace inscore
{

	class OSCRegexp;

	class IFilterForward;
	typedef class libmapping::SMARTP<IFilterForward>		SIFilterForward;

/*!
	\addtogroup ITLModel Data Model
	@{
*/

class FilterItem {
	public:

		/*!
		 * \brief FilterItem Create an item. The string can be an OSC regexp.
		 * \param str
		 */
		FilterItem(const std::string &str);

		/*!
		 * \brief FilterItem Copy an item.
		 * \param item
		 */
		FilterItem(const FilterItem &item);

		virtual ~FilterItem();

		/*!
		 * \brief match test if the string passed match with the item.
		 * If the item is not a regexp, the string compared to the literal value of the item.
		 * \param str the string to test
		 * \return true if the string match
		 */
		bool match(const std::string &str) const;

		/*!
		 * \brief value Literal value of the item
		 * \return a string
		 */
		std::string value() const { return fValue; }

		/*!
		 * \brief isOscAddress
		 * \return true if the value is an OSC address
		 */
		bool isOscAddress() const;

	private:

		std::string fValue;
		OSCRegexp * fRexp;
};

/*!
 * \brief The IFilterForward class. A class to manage list of accepted and filtered forwarded messages.
 *
 * Two list of item are managed : A list of rejected item and a list of accepted item.
 * An item can be an address or a message. OSC regexp can be used for address.
 *
 */
class IFilterForward : public IVNode
{
	private:
		/*!
		 * \brief fAcceptList List of accepted item (address or message)
		 */
		std::vector<FilterItem> fAcceptList;

		/*!
		 * \brief fRejectList List of rejected item (address or message)
		 */
		std::vector<FilterItem> fRejectList;

		static MsgHandler::msgStatus setListMsg(std::vector<FilterItem> &aList, const IMessage* msg);
		static std::string getListMsg(const std::vector<FilterItem> &aList);

    public:
        /// \brief creates a new IFilterNode
		static SIFilterForward create(IObject * parent)		{ return new IFilterForward(parent); }

		/*!
		 * \brief applyFilter The accepted items are parsed and if the message not correspond to an accepted item, the rejected items are parsed.
		 * The forward message itself is always rejected.
		 * \param msg The message
		 * \return true if the message must be filter, else return false.
		 */
		bool applyFilter(const IMessage* msg) const;

    protected:
		IFilterForward(IObject * parent);
        virtual ~IFilterForward();

		/*!
		 * \brief setAcceptMsg Message to create acceted item list. List is cleared at each call.
		 * \param msg the message with 0 or 1 parameter
		 * \return a status
		 */
		MsgHandler::msgStatus setAcceptMsg(const IMessage* msg);

		/*!
		 * \brief setRejectMsg Message to create rejected item list. List is cleared at each call.
		 * \param msg the message with 0 or 1 parameter
		 * \return a status
		 */
		MsgHandler::msgStatus setRejectMsg(const IMessage* msg);

        /// \brief get the accepted address and message list.
		std::string getAcceptMsg() const;

        /// \brief get the rejected address and message list.
		std::string getRejectMsg() const;
};

/*!
@}
*/

}

#endif // IFILTERFORWARD_H
