/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __IObjectVNodes__
#define __IObjectVNodes__

#include "IVNode.h"

namespace interlude
{

class IMessage;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IObjectDebug;
typedef class SMARTP<IObjectDebug>			SIObjectDebug;
//--------------------------------------------------------------------------
/*!
	\brief an object debug virtual node
*/
class IObjectDebug : public IVNode
{
	protected:
		bool fMap;						///< flag to display the graphic map
		bool fName;						///< flag to display names
		bool fSignal;					///< flag to emit profiling signal
		bool fClick;					///< flag to send osc feedback on mouse-click
	
	public:	
		/// \brief creates a new IObjectDebug
		static SIObjectDebug create(IObject * parent)		{ return new IObjectDebug(parent); }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& out) const;

		/// \brief accept an Update visitor
		virtual void	accept (Updater*);

		virtual bool	getMapDebug () const	{ return fMap; }
		virtual bool	getNameDebug () const	{ return fName; }
		virtual bool	getSignalDebug () const { return fSignal; }
		virtual bool	getClickDebug () const	{ return fClick; }
		
	protected:	
				 IObjectDebug(IObject * parent);
		virtual ~IObjectDebug() {}

		/// \brief object \c 'get' without parameter form: gives the corresponding 'set' message list
		virtual IMessageList get () const;

		virtual int	execute (const IMessage* msg);

		/// \brief sets the mapping debug flag
		void		setMapDebug(bool state)				{ fMap = state; }
		/// \brief sets the mapping debug flag
		void		setNameDebug(bool state)			{ fName = state; }
		/// \brief sets the mapping debug flag
		void		setSignalDebug(bool state)			{ fSignal = state; }
		/// \brief sets the click debug flag
//		void		setClickDebug(bool state)			{ fClick = state; }
};
std::ostream&	operator << (std::ostream& out, const SIObjectDebug& o);


/*! @} */

} // end namespoace

#endif
