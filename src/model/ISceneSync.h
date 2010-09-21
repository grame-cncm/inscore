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


#ifndef __ISceneSync__
#define __ISceneSync__

#include "IVNode.h"
#include "ISync.h"

namespace interlude
{

class IMessage;

/*!
\addtogroup ITLModel
@{
*/

class ISceneSync;
typedef class SMARTP<ISceneSync>	SISceneSync;
//--------------------------------------------------------------------------
/*! \brief the scene synchronization node
*/
class ISceneSync : public IVNode
{	
	ISync	fSync;
	
	public:	
		static const std::string fTypeString;
		static SMARTP<ISceneSync> create(IObject * parent)	{ return new ISceneSync(parent); }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);

		/*! \brief gives the master of an object
			\param o the object to look for in the synchronization set
			\return the master when found
		*/
		virtual SMaster getMaster(SIObject o) const;

		/*! \brief synchronizes two objects
			\param o a slave object
			\param m the master object
		*/
		virtual void sync(const SIObject& o, SMaster m)	{ fSync.sync (o, m);}

		/*! \brief breaks a synchronization link
			\param o a slave object
		*/
		virtual void delsync(SIObject& o)						{ fSync.remove (o);}

		/*! \brief cleanup the relations set
			\see ISync::cleanup
		*/
		virtual void cleanup()	{ fSync.cleanup(); }

		/// \brief makes a topological sort of the scene elements according to their synchronizations set
		virtual void	sort (IObject::subnodes& nodes);

		/// \brief a periodic task to propagate modification state from masters to slaves
		virtual void ptask ();


				ISync& getSync()			{ return fSync; }
		const	ISync& getSync() const		{ return fSync; }

	protected:
				 ISceneSync(IObject * parent);
		virtual ~ISceneSync() {}

		/// \brief splits a compound name to a name and map name
		virtual bool name2mapName (const std::string& str, std::string& name, std::string& map) const;

		/// \brief sync \c 'get' message handler
		virtual IMessageList getAllParams () const;
		/// \brief sync \c 'get' message handler
		virtual IMessageList getMsgs (const IMessage* msg) const;
		/// \brief sync message handler
		virtual MsgHandler::msgStatus syncMsg (const IMessage*);
};

/*!
@}
*/

} // end namespoace

#endif
