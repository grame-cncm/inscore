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

#ifndef __IApplVNodes__
#define __IApplVNodes__

#include "IVNode.h"
#include "IObjectVNodes.h"

namespace interlude
{

class IMessage;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IApplDebug;
typedef class SMARTP<IApplDebug>		SIApplDebug;

//--------------------------------------------------------------------------
/*!
	\brief an object debug virtual node
*/
class IApplDebug : public IObjectDebug
{
	protected:
		bool fOSCDebug;					///< flag to debug OSC messages
	
	public:	
		/// \brief creates a new IApplDebug
		static SIApplDebug create(IObject * parent)		{ return new IApplDebug(parent); }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& out) const;

		/// \brief accept an Update visitor
		virtual void	accept (Updater*);

		virtual bool	getOSCDebug () const		{ return fOSCDebug; }

	protected:	
				 IApplDebug(IObject * parent);
		virtual ~IApplDebug() {}

		/// \brief object \c 'get' without parameter form: gives the corresponding 'set' message list
		virtual IMessageList get () const;

		void		setOSCDebug(bool state)		{ fOSCDebug = state; }
};
std::ostream&	operator << (std::ostream& out, const SIApplDebug& o);


/*! @} */

} // end namespoace

#endif
