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
#include "Forwarder.h"

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
class IFileWatcher;
typedef class libmapping::SMARTP<IFileWatcher>		SIFileWatcher;
class IJavascript;
typedef class libmapping::SMARTP<IJavascript>		SIJavascript;
class IFilterForward;
typedef class libmapping::SMARTP<IFilterForward>		SIFilterForward;

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
	SIFileWatcher	fFileWatcher;
	SIJavascript	fJSObject;
	std::string		fRootPath;

	TJSEngine*		fJavascript;
	SIFilterForward	fFilterForward;
	Forwarder		fForwarder;

	public:		
		static const std::string kSceneType;
		static libmapping::SMARTP<IScene> create(const std::string& name, IObject * parent)	{ return new IScene(name, parent); }
		bool			getFullScreen() const		{ return fFullScreen; }
		void			setFullScreen(bool state)	{ if (!fFrameless) fFullScreen = state; }
		bool			getOpenGl() const			{ return fOpenGl; }
		void			setOpenGl(bool state)		{ fOpenGl = state; }
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

		void	setState (state s);
		bool	isUpdateVersion() { return fUpdateVersion; }
		inline void	setUpdateVersion(bool isUpdated) { fUpdateVersion = isUpdated; }

		std::string			getRootPath() const;
		std::string			absolutePath( const std::string& path ) const;
		QGraphicsScene *	getGraphicScene () const;

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

	protected:
				 IScene(const std::string& name, IObject * parent);
		virtual ~IScene();

		/// \brief override IObject method
		virtual bool acceptSimpleEvent(EventsAble::eventype t) const;

		void		setRootPath(const std::string& s);
		MsgHandler::msgStatus setRootPath(const IMessage* msg);
		MsgHandler::msgStatus preProcessMsg (const IMessage* msg);
		MsgHandler::msgStatus loadMsg(const IMessage* msg);
		void		foreground ();
		void		newScene ();
		std::string address2scene (const char* addr) const;
		void		del ();
		virtual		SIMessageList getAll () const;

		/*!
		 * \brief forward The scene accept forward message.
		 * \param msg a message
		 * \return
		 */
		MsgHandler::msgStatus forward(const IMessage* msg);
};

/*!
@}
*/

} // end namespoace

#endif
