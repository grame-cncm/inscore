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
#include "GraphicEffect.h"
#include "IDate.h"
#include "IMessageHandlers.h"
#include "IShape.h"
#include "ISignalHandlers.h"
#include "IColor.h"
#include "IPosition.h"
#include "maptypes.h"
#include "Methods.h"
#include "rational.h"
#include "TSegmentation.h"
#include "TRelation.h"
#include "TMapable.h"
#include "PeriodicTask.h"
#include "smartpointer.h"



namespace inscore
{

class IMessage;
class VObjectView;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IObject;
typedef class libmapping::SMARTP<IObject>	SIObject;
class IAppl;
typedef class libmapping::SMARTP<IAppl>		SIAppl;
class IScene;
typedef class libmapping::SMARTP<IScene>	SIScene;
class IObjectDebug;
typedef class libmapping::SMARTP<IObjectDebug>	SIObjectDebug;
class Master;
typedef class libmapping::SMARTP<Master>			SMaster;
class ISceneSync;
typedef class libmapping::SMARTP<ISceneSync>		SISceneSync;
class ISignalNode;
typedef class libmapping::SMARTP<ISignalNode>		SISignalNode;

class TQtJs;

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
class IObject : public IPosition, public IShape, public IDate, public IColor, public EventsAble,
				public browsable, public TMapable, virtual public libmapping::smartable , public PeriodicTask
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
		bool	fLock;					///< if true the object can't be deleted
		int		fState;					///< the object modification state
		///< the object export flag and the object childexport option flag (if the children should be exported as well)
		std::deque<std::pair<std::string, bool> >	fExportFlag;

		bool	fNewData;

		/*!
			\brief find a named object in the application hierarchy
			\param name the object name
			\param pathtail the target object path
			\return a pointer to the object or null if not found
		*/
		virtual const IObject* findnode (const std::string& name, const std::string& pathtail) const;

		/*!
		 * \brief genericExport Add export flag to the queue object to export the object.
		 * \param msg export message with one or many file path.
		 * \param drawChildren draw or not object's children.
		 * \return MsgHandler::kProcessed or MsgHandler::kBadParameters if failed
		 */
		MsgHandler::msgStatus genericExport(const IMessage* msg, bool drawChildren);

	protected:
		std::string fTypeString;		///< the type string

		SIObjectDebug	fDebug;			///< debug virtual node
        SISceneSync		fSync;
        SISignalNode	fSignals;

		/*!
			\brief message handlers map
			
			Each functor is associated to the corresponding message and is intended
			to handle this specific message. 
		*/
		std::map<std::string,SMsgHandler>			fMsgHandlerMap;
    
        std::map<std::string,SSigHandler>          fSigHandlerMap;

		/// \brief state query handlers map
		std::map<std::string, SGetParamMsgHandler>	fGetMsgHandlerMap;

		/// \brief state query handlers map (handlers returning a message list).
		std::map<std::string, SGetParamMultiMsgHandler>	fGetMultiMsgHandlerMap;
	
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
		/// \brief sets the object name
		virtual void setName(const std::string& name)	{ fName = name; }
		/// \brief returns the \e deleted state object
		virtual bool	getDeleted() const			{ return fDelete; }

		/// \brief returns the object display start location
		virtual float	getDispStart() const			{ return fDispStart; }
		/// \brief returns the object display end lo	cation
		virtual float	getDispEnd() const				{ return fDispEnd; }

		/*!
		 * \brief returns the next object export-flag with file path and draw children flag to draw or not object children.
		 * \return a pair of file path and drawChildren flag. If file path is empty not export are needed.
		 */
		virtual std::pair<std::string, bool> getNextExportFlag() {
			if(!fExportFlag.empty()) {
				std::pair<std::string, bool> flag = fExportFlag.front();
				fExportFlag.pop_front();
				return flag;
			}
			std::pair<std::string, bool> flag;
			return flag;
		}

		/// \brief access to the graphic view
		virtual VObjectView*	getView() const				{ return fView; }

		/// \brief set the object graphic view
		virtual void			setView(VObjectView* view)	{ fView = view; }

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
		virtual void getAllMapNames(std::vector<std::string>& )			const {}
		virtual void getAvailableMapNames(std::vector<std::string>& )	const {}
		
		/// \brief returns the object size i.e. its subnodes count
		virtual int		size (bool recursive = false) const;

		/// \brief returns true when the object has no subnode
		virtual bool	empty () const				{ return size() == 0; }
				
		/// \brief returns the object globalmodification state
				int		getState () const			{ return fState; }
				
		/// \brief sets the object global modification state \see getState
		virtual	void	setState (state s);

		/// \brief returns the object data modification state
				bool			newData () const			{ return fNewData; }
				virtual void	newData (bool state);

		/// \brief returns the mapping debug flag
				int		mapDebug() const;
		/// \brief returns the names debug flag
				bool	nameDebug() const;
		/// \brief returns the signal debug flag
//				bool	signalDebug() const;
		/// \brief returns the click debug flag
				bool	clickDebug() const;

		/*!
			\brief executes a message and possibly modifies the object state.
			\param msg the message
			\return the message processing status
		*/
		virtual int	execute (const IMessage* msg);

		/*!
			\brief executes a signal and possibly modifies the object state.
			\param connections the signal-attribute connection
			\return the signal processing status
		*/
		virtual int	executeSignal (const std::string method, const std::pair<float,float> range, const ParallelSignal* sig);
        virtual int	executeSignal (const std::string method, const std::pair<int,int> range, const ParallelSignal* sig);
    
		/// \brief creates the object virtual nodes
		virtual void	createVirtualNodes ();

		/// \brief propagates signals modification state to graphic signals
		virtual void	propagateSignalsState ();

		/// \brief gives the signals node
		virtual SISignalNode	signalsNode () const;

		/*!
			\brief find a named object in the application hierarchy
			\param objpath the object path name
			\return a pointer to the object or null if not found
		*/
		virtual const IObject* findnode(const std::string& objpath) const;

		/*!
			\brief find a named node within the subnodes (without recursion)
			\param name the name of the node to look for
			\param outlist on output, the found objects list 
			\return true if at least one nooe matches
		*/
		virtual bool exactfind(const std::string& name,  subnodes& outlist) const;

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
		 * \brief accept Check if the message is for the object or one of this child. (Use match method)
		 * \param regexp a regular expression
		 * \return true when the object name matches
		 */
		virtual bool	accept(const std::string& regexp, const IMessage *);

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
		virtual void	del ();
		virtual void	_del (bool delcnx);		// the implementation of del

		/*!
		*	\brief transfers the attributes of the current object to a new one (recently created)
		*	\param the new object
		*/
		virtual void transferAttributes(SIObject newobj);

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

		/*!
			\brief process a signal
			
			\return the signal processing status
		*/
		virtual int processSig ();
    
		/// \brief adds a subnode to the object \param node the subnode
		virtual void	add (const nodePtr& node)	{ fSubNodes.push_back(node); setState(kSubModified); }

		/// \brief returns the object osc address
		virtual std::string getOSCAddress() const;

		/// \brief gives the scene of the object
		virtual SIScene			getScene();
		virtual const IScene*	getScene() const;

		/// \brief gives the application node
		virtual SIAppl			getAppl();
		virtual const IAppl*	getAppl() const;

		/// \brief gives the tree root object
		virtual const IObject*	getRoot() const;
		virtual IObject*		getRoot();

		/// \brief selects objects matching address
		virtual void			getObjects(const std::string& address, std::vector<const IObject*>& outv) const;

		/// \brief return true when the applicaton is initialized in offscreen mode 
		virtual bool			offscreen()	const	{ return fParent ? fParent->offscreen() : false; }

		/// \brief recursively get all objects state
		virtual SIMessageList getAll () const;

		/// \brief recursively get the specified attributes from all objects
		virtual SIMessageList getAttributes (const std::vector<std::string>& attributes) const;
		
		/*!
			\brief gives a handler for the \c get message
			\param param the \c get message parameter
			\return the corresponding handler if any
		*/
		virtual SGetParamMsgHandler getMessageHandler(const std::string& param) const;

		/*!
			\brief gives a multiple messages handler for a \c get message
			\param param the \c get message parameter
			\return the corresponding handler if any
		*/
		virtual SGetParamMultiMsgHandler getMultiMessageHandler(const std::string& param) const;

		/// \brief object \c 'get' message handler.
		virtual SIMessageList getMsgs (const IMessage* msg) const;
		
		/// \brief sets the message handlers.
		virtual void setHandlers ();
		virtual void setdyMsgHandler (); 
		virtual void setdyMsgHandler (Master* m);
    
        virtual IObject* getParent() const {return fParent;}

        /*! \brief cleanup the relations set
			\see ISync::cleanup
		*/
		virtual void cleanupSync();

		/// \brief makes a topological sort of the scene elements according to their synchronizations set
		virtual subnodes	sort ();

        /// \brief makes a topological sort of the scene elements according to their synchronizations set (inverted compared to sort() )
		virtual subnodes	invertedSort ();
    
    
		/*! \brief gives (one of) the masters of an object
			\param o the object to look for in the synchronization set
			\return the object master or 0 when not found
		*/    
        virtual SMaster getMaster(SIObject o) const;

		/*! \brief gives the masters of an object
			\param o the object to look for in the synchronization set
			\return a vector of all the masters or an empty vector when not found
		*/    
        virtual std::vector<SMaster> getMasters(SIObject o) const;
    
		/*! \brief gives the slaves of an object
			\param o the object to look for in the synchronization set
			\return a vector of all the slaves or an empty vector when not found
		*/    
        virtual std::vector<SIObject> getSlaves(const SIObject o) const;
    
        /// \brief a periodic task to propagate modification state from masters to slaves
		virtual void ptask ();
    
        /*!
			\brief gives a handler for a signal
			\param param the string method
			\param match a boolean to evaluate regular expressions
			\return the corresponding handler if any
		*/
		virtual SSigHandler			signalHandler(const std::string& method, bool match=false) const;
 
		virtual TQtJs*	getJSEngine()		{ return 0; }	///< gives the associated javascript engine, defaults to 0
	
	protected:	
		VObjectView* fView;		///< the object view
		IObject*	fParent;	///< the parent node

				 IObject(const std::string& name, IObject* parent);
		virtual ~IObject();

		virtual void colorAble ();				///< \brief set the color message handlers 
		virtual void positionAble ();			///< \brief set the position message handlers
		virtual void shapeAble ();				///< \brief set the shape message handlers
		virtual void timeAble ();				///< \brief set the time message handlers

		virtual void setMouseEventSensibility(bool mouseSensible);


		/// \brief get an object maps
		virtual SIMessageList getMaps () const;

		/// \brief get an object maps
		virtual SIMessageList __getMaps () const;

		/// \brief object \c 'get' without parameter form: gives the corresponding 'set' message list
		virtual SIMessageList getSetMsg () const;

		/// \brief get an object parameters
		virtual SIMessageList getParams() const;

		/// \brief get the specified attributes from an object
		virtual SIMessageList getParams(const std::vector<std::string>& attributes) const;

		/// \brief recursively get object parameters
		virtual SIMessageList getAllParams () const;

		/// \brief recursively get the specified attributes from objects
		virtual SIMessageList getAllParams (const std::vector<std::string>& attributes) const;

		/// \brief object \c 'get' a given param 
		virtual SIMessage getParam(const std::string& what, const SGetParamMsgHandler& h) const;

		/*!
			\brief gives a handler for a message
			\param param the string message
			\param match a boolean to evaluate regular expressions
			\return the corresponding handler if any
		*/
		virtual SMsgHandler			messageHandler(const std::string& param, bool match=false) const;

		
		/*!
			\brief sets an object display range
			
			An object can be made visible on a given range: 0 represents the beginning of the object
			and 1 represents the end.
			\param start the display start location
			\param end the display end location
		*/
		virtual void	setDispRange (float start, float end)	{ fDispStart = start; fDispEnd = end; }

		/*!
		*	\brief add a object export flag to a queue.
		*
		*	\param s the new export flag
		*	\param drawChildren a boolean to draw children of object
		*/
		virtual void	addExportFlag(const std::string& s, bool drawChildren) { fExportFlag.push_back(std::pair<std::string, bool>(s, drawChildren)); }

		/*!
		*	\brief writes the object and subnodes state to a stream
		*	\param out the output stream
		*	\param attributes a list of attributes to be saved, saves all the attributes when the list is empty
		*/
		virtual void	save(std::ostream& out, const std::vector<std::string>& attributes) const;

	//--------------------------------------------------------------------------
	// the message handlers
	//--------------------------------------------------------------------------
		/// \brief the \c 'effect' message handler
		virtual MsgHandler::msgStatus effectMsg(const IMessage* msg);
		virtual bool           getLocked () const {return fLock;}
		virtual GraphicEffect  getEffect () const;
		virtual SIMessageList  getWatch () const;
		virtual SIMessageList  getStack () const;
		virtual SIMessageList  getAliases () const;
		virtual std::vector<float> getFrame () const;

		/// \brief the \c 'alias' message handler
		virtual MsgHandler::msgStatus aliasMsg(const IMessage* msg);

		/// \brief the \c 'export' message handler (export object without children)
		virtual MsgHandler::msgStatus exportMsg(const IMessage* msg);

		/// \brief the \c 'exportAll' message handler (export object with childrens)
		virtual MsgHandler::msgStatus exportAllMsg(const IMessage* msg);

		/// \brief the \c 'rename' message handler
		virtual MsgHandler::msgStatus renameMsg(const IMessage* msg);

		/// \brief the \c 'lock' message handler
		virtual MsgHandler::msgStatus lockMsg(const IMessage* msg);

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus evalMsg(const IMessage* msg);

		/// \brief utility to delegate events acceptability
		virtual bool acceptSimpleEvent(EventsAble::eventype t) const;

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus _watchMsg(const IMessage* msg, bool add);

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus watchMsg(const IMessage* msg)		{ return _watchMsg (msg, false); }

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus watchMsgAdd(const IMessage* msg)	{ return _watchMsg (msg, true); }

		/// \brief the \c 'push' message handler
		virtual MsgHandler::msgStatus pushMsg(const IMessage* msg);

		/// \brief the \c 'pop' message handler
		virtual MsgHandler::msgStatus popMsg(const IMessage* msg);

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

		/// \brief object \c 'get' message handler.
		virtual MsgHandler::msgStatus get (const IMessage* msg) const;

		/// \brief object \c 'get count' message handler.
		int			getSize () const		{ return size(false); }

		/// \brief object \c 'get rcount' message handler.
		int			getRSize () const		{ return size(true); }

		/// \brief object \c 'save' message handler.
		virtual MsgHandler::msgStatus saveMsg (const IMessage* msg) const;

		/// \brief object \c 'event' message handler (provided for events simulation).
		virtual MsgHandler::msgStatus eventMsg (const IMessage* msg);

};

IMessage&		operator << (IMessage&, const SGetParamMsgHandler&);
IMessage&		operator << (IMessage&, const IObject::subnodes&);
std::ostream&	operator << (std::ostream& out, const SIObject& o);


/*! @} */

} // end namespoace

#endif
