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
#include "TILoader.h"
#include "TScripting.h"
#include "VSceneView.h"

class QGraphicsScene;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/
//typedef TV8Js		TJSEngine;

class Master;
typedef class libmapping::SMARTP<Master>			SMaster;
class IScene;
typedef class libmapping::SMARTP<IScene>			SIScene;
class IFileWatcher;
typedef class libmapping::SMARTP<IFileWatcher>		SIFileWatcher;
class IJavascript;
typedef class libmapping::SMARTP<IJavascript>		SIJavascript;

//--------------------------------------------------------------------------
/*! \brief a scene model
*/
class IScene : public IRectShape, public TILoader
{	
	bool			fFullScreen;
	bool			fFrameless;
	bool			fAbsoluteCoordinates;
	bool			fWindowOpacity;
	bool			fUpdateVersion;
	SIFileWatcher	fFileWatcher;
	SIJavascript	fJSObject;
	std::string		fRootPath;

	TJSEngine		fJavascript;
	TLua			fLua;
	
	public:		
		static const std::string kSceneType;
		static libmapping::SMARTP<IScene> create(const std::string& name, IObject * parent)	{ return new IScene(name, parent); }
#ifdef ANDROID
		bool			getFullScreen() const		{ return true; }
#else
		bool			getFullScreen() const		{ return fFullScreen; }
#endif
		void			setFullScreen(bool state)	{ fFullScreen = state; }
		bool			getFrameless() const		{ return fFrameless; }
		void			setFrameless(bool state)	{ fFrameless = state; }
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

		void	setState (state s);
		bool	isUpdateVersion() { return fUpdateVersion; }
		inline void	setUpdateVersion(bool isUpdated) { fUpdateVersion = isUpdated; }

		std::string			getRootPath() const;
		std::string			absolutePath( const std::string& path ) const;
		QGraphicsScene *	getGraphicScene () const;

		TJSEngine*		getJSEngine()		{ return &fJavascript; }
		TLua*			getLUAEngine()		{ return &fLua; }

		virtual VSceneView*	getView() const				{ return static_cast<VSceneView *>(fView); }

	protected:
				 IScene(const std::string& name, IObject * parent);
		virtual ~IScene();

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus _watchMsg(const IMessage* msg, bool add);

		void		setRootPath(const std::string& s);
		MsgHandler::msgStatus loadMsg(const IMessage* msg);
		void		foreground ();
		void		newScene ();
		std::string address2scene (const char* addr) const;
		void		del ();
};

/*!
@}
*/

} // end namespoace

#endif
