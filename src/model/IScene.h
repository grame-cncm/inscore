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


#ifndef __IScene__
#define __IScene__

#include "IRectShape.h"
#include "PeriodicTask.h"
#include "TScripting.h"

class QGraphicsScene;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Master;
typedef class libmapping::SMARTP<Master>			SMaster;
class IScene;
typedef class libmapping::SMARTP<IScene>			SIScene;
class ISceneSync;
typedef class libmapping::SMARTP<ISceneSync>		SISceneSync;
class IFileWatcher;
typedef class libmapping::SMARTP<IFileWatcher>		SIFileWatcher;
class ISignalNode;
typedef class libmapping::SMARTP<ISignalNode>		SISignalNode;

//--------------------------------------------------------------------------
/*! \brief a scene model
*/
class IScene : public IRectShape, public PeriodicTask
{	
	bool			fFullScreen;
	bool			fFrameless;
	bool			fAbsoluteCoordinates;
	SISceneSync		fSync;
	SIFileWatcher	fFileWatcher;
	SISignalNode	fSignals;
	std::string		fRootPath;

	TJSEngine		fJavascript;
	TLua			fLua;
	
	public:		
		static const std::string kSceneType;
		static libmapping::SMARTP<IScene> create(const std::string& name, IObject * parent)	{ return new IScene(name, parent); }

		bool			getFullScreen() const		{ return fFullScreen; }
		void			setFullScreen(bool state)	{ fFullScreen = state; }
		bool			getFrameless() const		{ return fFrameless; }
		void			setFrameless(bool state)	{ fFrameless = state; }
		bool			getAbsoluteCoordinates() const		{ return fAbsoluteCoordinates; }
		void			setAbsoluteCoordinates(bool state)	{ fAbsoluteCoordinates = state; }
		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);

		/// \brief creates the scene virtual nodes
		virtual void	createVirtualNodes ();

		/// \brief makes a topological sort of the scene elements according to their synchronizations set
		virtual void	sort ();

		/// \brief sets the message handlers.
		virtual void setHandlers ();
		/*!
			\brief reset the scene to its default state
		*/
		virtual void	reset ();

		/// \brief propagates signals modification state to graphic signals
		virtual void	propagateSignalsState ();

		/// \brief gives the signals node
		virtual SISignalNode	signalsNode () const;

		/*! \brief gives the master of an object
			\param o the object to look for in the synchronization set
			\return the object master or 0 when not found
		*/
		virtual SMaster getMaster(SIObject o) const;
	
		/// \brief gives the scene (actually self)
		virtual SIScene			getScene()					{ return this; }
		virtual const IScene*	getScene() const			{ return this; }
			
		/*! \brief cleanup the relations set
			\see ISync::cleanup
		*/
		virtual void cleanupSync();

		/// \brief a periodic task to propagate modification state from masters to slaves
		virtual void ptask ();
		
		/// \brief adds a subnode to the object \param node the subnode
		virtual void	add (const nodePtr& node);

		std::string			getRootPath() const;
		std::string			absolutePath( const std::string& path ) const;
		QGraphicsScene *	getGraphicScene () const;

#ifdef V8ENGINE
		TV8Js*			getJSEngine()		{ return &fJavascript; }
#else
		TMozillaJs*		getJSEngine()		{ return &fJavascript; }
#endif
		TLua*			getLUAEngine()		{ return &fLua; }


	protected:
				 IScene(const std::string& name, IObject * parent);
		virtual ~IScene();

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus _watchMsg(const IMessage* msg, bool add);
		virtual IMessageList  getWatch () const		{ return IObject::getWatch(); }

		void		setRootPath(const std::string& s);
		MsgHandler::msgStatus loadMsg(const IMessage* msg);
//		void		foreground ();
		void		newScene ();
		void		del ();
		std::string address2scene (const char* addr) const;
};

/*!
@}
*/

} // end namespoace

#endif
