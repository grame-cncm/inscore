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
class ISignalConnection;

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
    
        std::vector<ISignalConnection* > getConnectionsOf(std::string objectName);

	protected:
		bool fDebug;

        std::vector<ISignalConnection* > fConnections; // the connections between attributes and signals
    
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
//--------------------------------------------------------------------------
/*! \brief the signal-attribute connections 
*/
class ISignalConnection
{	
	public:
    
    
				 ISignalConnection(){}
		virtual ~ISignalConnection() {}
    
    	/*! \brief returns the object whose attribute has been connected to the signal
		*/
        std::string getObject(){return fObject;}
    
    	/*! \brief sets the object
		*/
        void setObject(std::string o) {fObject = o;}
    
        /*! \brief returns the name of the method connected
		*/
		std::string getMethod(){return fMethod;}
    
        /*! \brief sets the name of the method connected
		*/
		void setMethod(std::string method){fMethod = method;}
    
        /*! \brief returns the 'key' of this connection (string "object:method")
		*/
		std::string getObjectMethod(){return fKey;}
    
        /*! \brief sets the 'key' of this connection (string "object:method")
		*/
		void setObjectMethod(std::string objectmethod){fKey = objectmethod;}
    
		/*! \brief returns the signal to be connected
		*/
        SParallelSignal getSignal(){return fSignal;}
    
        /*! \brief sets the signal to be connected
		*/
        void setSignal(SParallelSignal sig){fSignal = sig;}
    
        /*! \brief returns the float range bounds
		*/
		std::pair<float, float> getFloatRange(){return fRangeFloat;}
    
        /*! \brief sets the float range bounds
		*/
		void setFloatRange(float f1, float f2){fRangeFloat = std::pair<float, float>(f1, f2);}
    
        /*! \brief returns the int range bounds
		*/
		std::pair<int, int> getIntRange() {return fRangeInt;}
    
        /*! \brief sets the int range bounds
		*/
		void setIntRange(int i1, int i2){fRangeInt = std::pair<int, int>(i1, i2);}
    
        /*! \brief returns the range type
		*/
		std::string getRangeType(){return fRangeType;}
    
        /*! \brief sets the range type
		*/
		void setRangeType(std::string type){fRangeType = type;}
		
	protected:
    
    	/*! \brief the object whose attribute has been connected to the signal
		*/
        std::string fObject;
    
        /*! \brief the name of the method connected
		*/
		std::string fMethod;
    
		/*! \brief the signal to be connected
		*/
        SParallelSignal fSignal;
    
        /*! \brief the connection key name : "object:method"
		*/
        std::string fKey;
    
        /*! \brief the float range bounds
		*/
		std::pair<float,float> fRangeFloat;
    
        /*! \brief the int range bounds
		*/
        std::pair<int,int> fRangeInt;
    
        /*! \brief the range type
		*/
		std::string fRangeType;
    
    
};


/*!
@}
*/

} // end namespoace

#endif
