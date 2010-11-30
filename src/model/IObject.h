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

#ifndef __IObject__
#define __IObject__

#include <string>
#include <vector>
#include <ostream>
#include <map>
#include <set>

#include "browsable.h"
#include "EventsAble.h"
#include "IDate.h"
#include "IMessageHandlers.h"
#include "IPosition.h"
#include "maptypes.h"
#include "rational.h"
#include "TSegmentation.h"
#include "TRelation.h"
#include "TMapable.h"
#include "smartpointer.h"



namespace inscore
{

class IMessage;
class VGraphicsItemView;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IObject;
typedef class SMARTP<IObject>	SIObject;
class IScene;
typedef class SMARTP<IScene>	SIScene;
class IObjectDebug;
typedef class SMARTP<IObjectDebug>	SIObjectDebug;


//typedef msgHandler<IObject*>	IObjectMsgHandler;
//typedef SMARTP<GetParamMsgHandlerBase> SGetParamMsgHandlerBase;

//--------------------------------------------------------------------------
/*!
	\brief the base class of the data model
	
	The model is organized in a \e tree, thus each node contains a list of subnodes. 
	Each node is identified by a unique name.
	In addition, parameters common to all the objects are handled at this level 
	(x, y coordinates, z order, color, etc.)
	
	\note Note that an object of the model can't be directly deleted: in order to facilitate the view
	synchronization, objects carry a flag to denote pending deletion. Real deletion is in charge
	of the \c cleanup method.
*/
class IObject : public IPosition, public IDate, public IColor, public EventsAble,
				public browsable, public TMapable, virtual public smartable
{
	public:
		friend class IProxy;
		typedef SIObject				nodePtr;	///< the node smart pointer type
		typedef std::vector<nodePtr>	subnodes;	///< the node sub elements container type

	private:
		std::string		fName;		///< the object name, used as identifier
		subnodes		fSubNodes;	///< child objects list

		float	fDispStart, fDispEnd;	///< the object displayed range (0-1 covers the whole range)
		bool	fDelete;				///< true when an object should be deleted
		int		fState;					///< the object modification state
		std::string	fExportFlag;		///< the object export flag

		bool	fNewData;
		
	protected:
		std::string fTypeString;		///< the type string

		SIObjectDebug	fDebug;			///< debug virtual node

		/*!
			\brief message handlers map
			
			Each functor is associated to the corresponding message and is intended
			to handle this specific message. 
		*/
		std::map<std::string,SMsgHandler>			fMsgHandlerMap;

		/// \brief state query handlers map
		std::map<std::string, SGetParamMsgHandler>	fGetMsgHandlerMap;
	
	public:	
		/// \brief the possible objects modification states
		enum state { kClean, kNewObject=1, kModified=2, kSubModified=4, kMasterModified=8 };

		/*!
			\brief creates a new IObject
			\param name the object name
			\param parent its parent object
			\note an object name is used as an unique identifier within the address space
		*/
		static SIObject create(const std::string& name, IObject* parent)	
			{ return new IObject(name, parent); }

		/// \brief returns the object sub-nodes
				subnodes& elements()				{ return fSubNodes; }
		/// \brief returns the object sub-nodes
		const	subnodes& elements() const			{ return fSubNodes; }
		/// \brief returns the object name
		const	std::string& name() const			{ return fName; }
		/// \brief returns the \e deleted state object
		virtual bool	getDeleted() const			{ return fDelete; }

		/// \brief returns the object display start location
		virtual float	getDispStart() const		{ return fDispStart; }
		/// \brief returns the object display end location
		virtual float	getDispEnd() const			{ return fDispEnd; }

		/// \brief returns the object export-flag
		virtual std::string		getExportFlag() const { return fExportFlag; }

		/// \brief base access to graphic view
		virtual VGraphicsItemView*	graphicView() const { return 0; }

		/// \brief events management handler
		virtual EventsAble*	eventsHandler()					{ return this; }
		virtual const EventsAble*	eventsHandler() const 	{ return this; }

		/// \brief selects subnodes using a predicate
		template<typename P>  void	selectsubnodes(P& p, std::vector<SIObject>& outv) const {
			subnodes::const_iterator i = elements().begin();
			subnodes::const_iterator end = elements().end();
			while (i != end) {
				i = find_if (i, end, p);
				if (i != end) { 
					outv.push_back( *i );
					i++;
				}
			}
		}
		
		/// \brief gets the list of mappings
		virtual void getAllMapNames(std::vector<std::string>& result) const {}
		virtual void getAvailableMapNames(std::vector<std::string>& result) const {}
		
		/// \brief returns the object size i.e. its subnodes count
		virtual int		size () const				{ return int(fSubNodes.size()); }
		/// \brief returns true when the object has no subnode
		virtual bool	empty () const				{ return size() == 0; }
				
		/// \brief returns the object globalmodification state
				int		getState () const			{ return fState; }
				
		/// \brief sets the object global modification state \see getState
				void	setState (state s)			{ fState |= s; }

		/// \brief returns the object data modification state
				bool	newData () const			{ return fNewData; }
				void	newData (bool state)		{ fNewData = state; }

		/// \brief returns the mapping debug flag
				bool	mapDebug() const;
		/// \brief returns the names debug flag
				bool	nameDebug() const;
		/// \brief returns the signal debug flag
				bool	signalDebug() const;
		/// \brief returns the click debug flag
				bool	clickDebug() const;

		/*!
			\brief executes a message and possibly modifies the object state.
			\param msg the message
			\return the message processing status
		*/
		virtual int	execute (const IMessage* msg);

		/// \brief creates the object virtual nodes
		virtual void	createVirtualNodes ();

		/*!
			\brief find a named node within the subnodes (without recursion)
			\param name the name of the node to look for
			\return the node if any
		*/
		virtual SIObject exactfind(const std::string& name) const;

		/*!
			\brief find children objects by regular expression
			\param regexp a regular expression
			\param outlist on output, contains the list of objects that match the regular expression
			\return false when no object matches 
		*/
		virtual bool	find(const std::string& regexp, subnodes& outlist) const;

		/*!
			\brief object name matching by regular expression
			\param regexp a regular expression
			\return true when the object name matches
		*/
		virtual bool	match(const std::string& regexp) const;

		/*!
			\brief cleanup the object tree.
			
			The cleanup operation sets the objects modification state to kClean and
			delete objects flagged as \e deleted: 
			actually, an object cannot be directly deleted, it is first flagged and
			real deletion is in charge of the cleanup method. This is intended to make
			objects deletion visible to the view.
			
			The cleanup method should be called after all the views have been updated.
		*/
		virtual void	cleanup ();

		/// \brief call del for all the object subnodes
		virtual void	delsubnodes();

		/*!
			\brief sets an object in deleted state
			\note an object is not directly deleted, it is first flagged as deleted
			actual deletion is in charge of the garbage method.
		*/
		virtual void	del ()						{ fDelete = true; }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& out) const;

		/// \brief accept an Update visitor
		virtual void	accept (Updater*);

		/*!
			\brief gives the type string corresponding to an object
			
			An object type string is expected as the first parameter of the 'set' message.
			\return the type of the object as a string
		*/
		virtual const std::string&	getTypeString() const	{ return fTypeString; }

		/*!
			\brief process a message
			
			Message processing scheme consists in finding the target object in the subnodes list
			and to call its \c execute method. This behavior is overridden at IAppl level since it calls
			its self \c execute method (\see IAppl).
			
			\param address the current osc address location
			\param addressTail the remainging part of the osc address
			\param msg the message to be processed
			\return the message processing status
		*/
		virtual int processMsg (const std::string& address, const std::string& addressTail, const IMessage* msg);

		/// \brief adds a subnode to the object \param node the subnode
		virtual void	add (const nodePtr& node)	{ fSubNodes.push_back(node); setState(kSubModified); }

		/// \brief returns the object osc address
		virtual std::string getOSCAddress() const;

		/// \brief gives the scene of the object
		virtual SIScene			getScene();

		/// \brief recursively get all objects state
		virtual IMessageList getAll () const;
		
		/*!
			\brief gives a handler for the \c get message
			\param param the \c get message parameter
			\return the corresponding handler if any
		*/
		virtual SGetParamMsgHandler getMessageHandler(const std::string& param) const;

		/// \brief object \c 'get' message handler.
		virtual IMessageList getMsgs (const IMessage* msg) const;

		virtual void setdyMsgHandler (); //				{ fMsgHandlerMap["dy"]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYPos); }
		virtual void setdyMsgHandler (Master* m); //	{ fMsgHandlerMap["dy"]	= TSetMethodMsgHandler<Master,float>::create(this, m, m->setDy); }
//		virtual void setdyMsgHandler ()				{ fMsgHandlerMap["dy"]	= TSetMsgHandler<float, TDSetOperator>::create(fYPos); }
//		virtual void setdyMsgHandler (float& field) { fMsgHandlerMap["dy"]	= TSetMsgHandler<float>::create(field); }

	protected:	
		IObject*	fParent;	///< the parent node

				 IObject(const std::string& name, IObject* parent);
		virtual ~IObject();

		virtual void colorAble ();				///< \brief set the color message handlers 
		virtual void positionAble ();			///< \brief set the position message handlers
		virtual void timeAble ();				///< \brief set the time message handlers

		/// \brief object \c 'get' without parameter form: gives the corresponding 'set' message list
		virtual IMessageList getSetMsg () const;

		/// \brief get an object parameters
		virtual IMessageList getParams() const;

		/// \brief recursively get object parameters
		virtual IMessageList getAllParams () const;

		/// \brief object \c 'get' a given param 
		virtual IMessage* getParam(const std::string& what, const SGetParamMsgHandler& h) const;

		/// \brief object \c 'get' a given param 
		virtual IMessage* click(const IMessage* msg) const;

		/// \brief object \c 'get' a given param 
		virtual IMessage* select(const IMessage* msg) const;

		/*!
			\brief gives a handler for a message
			\param param the string message
			\param match a boolean to evaluate regular expressions
			\return the corresponding handler if any
		*/
		virtual SMsgHandler			messageHandler(const std::string& param, bool match=false) const;

		/*!
			\brief gives a handler for a state modification message
			\param param the destination parameter
			\return the corresponding handler if any
		*/
//		virtual SMsgHandler			setMessageHandler(const std::string& param) const;

		/*!
			\brief sets an object display range
			
			An object can be made visible on a given range: 0 represents the beginning of the object
			and 1 represents the end.
			\param start the display start location
			\param end the display end location
		*/
		virtual void	setDispRange (float start, float end)	{ fDispStart = start; fDispEnd = end; }

		/*!
		*	\brief sets the object export flag 
		*
		*	When not empty (<=> the flag is 'on'), the export-flag contains the file path where the object
		*	must be exported. 
		*	If empty (<=> the flag is 'off'), no export needed.
		*
		*	\param s the new export flag
		*/
		virtual void	setExportFlag(const std::string& s) { fExportFlag = s; }

		/*!
		*	\brief writes the object and subnodes state to a stream
		*	\param out the output stream
		*/
		virtual void	save(std::ostream& out) const;

	//--------------------------------------------------------------------------
	// the message handlers
	//--------------------------------------------------------------------------
		/// \brief the \c 'export' message handler
		virtual MsgHandler::msgStatus exportMsg(const IMessage* msg);

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus _watchMsg(const IMessage* msg, bool add);

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus watchMsg(const IMessage* msg)		{ return _watchMsg (msg, false); }

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus watchMsgAdd(const IMessage* msg)	{ return _watchMsg (msg, true); }

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

		/// \brief object \c 'get' message handler.
		virtual MsgHandler::msgStatus get (const IMessage* msg) const;

		/// \brief object \c 'click' message handler.
		virtual MsgHandler::msgStatus clickMsg (const IMessage* msg) const;

		/// \brief object \c 'select' message handler.
		virtual MsgHandler::msgStatus selectMsg (const IMessage* msg) const;

		/// \brief object \c 'save' message handler.
		virtual MsgHandler::msgStatus saveMsg (const IMessage* msg) const;

		/// \brief object \c 'dcolor' message handler.		
		virtual MsgHandler::msgStatus dcolorMsg(const IMessage* msg);

		/// \brief object \c 'dcolor' message handler.				
		virtual MsgHandler::msgStatus dhsvMsg(const IMessage* msg);
};

IMessage&		operator << (IMessage&, const SGetParamMsgHandler&);
IMessage&		operator << (IMessage&, const IObject::subnodes&);
std::ostream&	operator << (std::ostream& out, const SIObject& o);


/*! @} */

} // end namespoace

#endif
