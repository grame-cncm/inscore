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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/


#ifndef __IScene__
#define __IScene__

#include "Modules.h"
#include "IRectShape.h"
#include "PeriodicTask.h"
#include "TILoader.h"
#include "TScripting.h"
#include "Forwarder.h"
#include "Connect.h"

#include <vector>

class QGraphicsScene;

namespace inscore
{

class VSceneView;
/*!
\addtogroup ITLModel
@{
*/
//typedef TV8Js		TJSEngine;

class Master;
typedef class libmapping::SMARTP<Master>			SMaster;
class IScene;
typedef class libmapping::SMARTP<IScene>			SIScene;
class IJavascript;
typedef class libmapping::SMARTP<IJavascript>		SIJavascript;
class IFilterForward;
typedef class libmapping::SMARTP<IFilterForward>		SIFilterForward;

#if INCLUDEFileWatcher
class IFileWatcher;
typedef class libmapping::SMARTP<IFileWatcher>		SIFileWatcher;
#endif

//--------------------------------------------------------------------------
/*! \brief a scene model
*/
class IScene : public IRectShape, public TILoader
{	
	bool			fOpenGl;
	bool			fFullScreen;
	bool			fFrameless;
	bool			fAbsoluteCoordinates;
	bool			fWindowOpacity;
	bool			fUpdateVersion;
#if INCLUDEFileWatcher
	SIFileWatcher	fFileWatcher;
#endif
	SIJavascript	fJSObject;
	std::string		fRootPath;

	TJSEngine*		fJavascript;
	SIFilterForward	fFilterForward;
	Forwarder		fForwarder;
	Connect			fConnecter;
	std::string		fParseVersion;

	public:		
		static const std::string kSceneType;
		static libmapping::SMARTP<IScene> create(const std::string& name, IObject * parent)	{ return new IScene(name, parent); }
		bool			getFullScreen() const		{ return fFullScreen; }
		void			setFullScreen(bool state)	{ if (!fFrameless) fFullScreen = state; }
		bool			getOpenGl() const			{ return fOpenGl; }
		void			setOpenGl(bool state);
		bool			getFrameless() const		{ return fFrameless; }
		void			setFrameless(bool state)	{ if (!fFullScreen) fFrameless = state; }
		bool			getAbsoluteCoordinates() const		{ return fAbsoluteCoordinates; }
		void			setAbsoluteCoordinates(bool state)	{ fAbsoluteCoordinates = state; }
		bool			getWindowOpacity() const			{ return fWindowOpacity; }
		void			setWindowOpacity(bool state)		{ fWindowOpacity = state; }
		
		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);
		
		/// \brief end paint event handler
		void endPaint () const;

		/// \brief creates the scene virtual nodes
		virtual void	createVirtualNodes ();

		/// \brief sets the message handlers.
		virtual void setHandlers ();
		/*!
			\brief reset the scene to its default state
		*/
		virtual void	reset ();

		/// \brief gives the scene (actually self)
		virtual SIScene			getScene()					{ return this; }
		virtual const IScene*	getScene() const			{ return this; }
		
		/// \brief adds a subnode to the object \param node the subnode
		virtual void	add (const nodePtr& node);
		/// \brief gives the expected script language version
		virtual int	getParseVersion	() const;

		void	setState (state s);
		bool	isUpdateVersion() { return fUpdateVersion; }
		inline void	setUpdateVersion(bool isUpdated) { fUpdateVersion = isUpdated; }

		std::string			getRootPath() const;
		std::string			absolutePath( const std::string& path ) const;
#ifndef NOVIEW
		QGraphicsScene *	getGraphicScene () const;
#endif
#ifdef EMCC
	virtual void	setWidth(float width)		{ IRectShape::_setWidth(width); refresh(); }
	virtual void	setHeight(float height)		{ IRectShape::_setHeight(height); refresh(); }
#endif
		virtual VSceneView*	getSceneView() const;

		/*!
		 * \brief accept Check if the message is for the scene or his child and if true, do the forward.
		 * \param regexp a regular expression.
		 * \param msg a message
		 * \return true if the message is for the scene
		 */
		virtual bool	accept(const std::string& regexp, const IMessage *msg);

		/*!
		 * \brief execute Forward scene message (accept method is not called if scene is the terminal node of the message) and execute message function.
		 * \param msg Message to execute.
		 * \return the message processing status
		 */
		int	execute (const IMessage* msg);

		const std::vector<IMessage::TUrl> getForwardList() const { return fForwarder.getForwardList(); }
		const std::vector<IMessage::TUrl> getCnxList() const 	 { return fConnecter.getCnxList(); }

		float getSceneWidth() const;
		float getSceneHeight() const;

	protected:
				 IScene(const std::string& name, IObject * parent);
		virtual ~IScene();

		/// \brief override IObject method
		virtual bool acceptSimpleEvent(EventsAble::eventype t) const;
		virtual MsgHandler::msgStatus widthMsg (const IMessage* msg);
		virtual MsgHandler::msgStatus heightMsg (const IMessage* msg);
		virtual SIMessage getSetMsg (const std::string& address) const { return nullptr; }

		void		setRootPath(const std::string& s);
		MsgHandler::msgStatus setRootPath(const IMessage* msg);
		MsgHandler::msgStatus preProcessMsg (const IMessage* msg);
		MsgHandler::msgStatus loadMsg(const IMessage* msg);
		void		foreground ();
		void		newScene ();
		std::string address2scene (const char* addr) const;
		const std::string& parseVersion () const;
		void		del ();
		virtual		SIMessageList getAll () const;

		/// \brief scene \c 'forward' message handler.
		MsgHandler::msgStatus forward(const IMessage* msg);
		/// \brief scene \c 'connect' message handler.
		MsgHandler::msgStatus connect (const IMessage* msg);

		MsgHandler::msgStatus setParseVersion(const IMessage* msg);
};

/*!
@}
*/

} // end namespoace

#endif
