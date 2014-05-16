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


#ifndef __ISignalNodes__
#define __ISignalNodes__

#include "IVNode.h"
#include "ISync.h"

namespace inscore
{

class IMessage;

/*!
\addtogroup ITLModel
@{
*/

class ISignal;
typedef class libmapping::SMARTP<ISignal>		SISignal;
class ISignalNode;
typedef class libmapping::SMARTP<ISignalNode>	SISignalNode;
//--------------------------------------------------------------------------
/*! \brief the scene signals node
*/
class ISignalNode : public IVNode
{	
	public:
		using IVNode::find;
	
		static libmapping::SMARTP<ISignalNode> create(IObject * parent)	{ return new ISignalNode(parent); }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);
		
		/// \brief find a name signal in the signals node
//		virtual SISignal find (std::string node) const;
		virtual bool find (std::string node, subnodes& outlist);

		/// \brief overrides virtual nodes creation
		virtual void	createVirtualNodes ()   {}

		/*! \brief gives the signal node debug state
		*/
		virtual bool debug () const			{ return fDebug; }
		virtual void debug (bool state)		{ fDebug = state; }
		
		static const std::string kName;
    
        std::map<std::string, SParallelSignal > getConnections() {return fConnections;}
        std::map<std::string, std::pair<SParallelSignal, std::string> > getConnectionsOf(std::string objectName);

	protected:
		bool fDebug;

        std::map< std::string, SParallelSignal > fConnections; // the connections between attributes and signals
    
        std::map< std::string, std::string > fRanges; // the ranges corresponding to each connection
    
        /*! \brief makes the connections between a signal and one ore more methods of an object
		*/
		MsgHandler::msgStatus connect(SParallelSignal signal, std::string object, std::string methods);
    
        /*! \brief breaks the connections of a signal (all of them, or only some specified)
		*/
		MsgHandler::msgStatus disconnect(SParallelSignal signal, std::string object = "", std::string methods = "");
    
        /*! \brief handles the "connect" message
		*/
		MsgHandler::msgStatus connectMsg (const IMessage* msg);
    
        /*! \brief handles the "disconnect" message
		*/
		MsgHandler::msgStatus disconnectMsg (const IMessage* msg);
    
				 ISignalNode(IObject * parent);
		virtual ~ISignalNode() {}
		virtual bool debug (int state);
    
};

/*!
@}
*/

} // end namespoace

#endif
