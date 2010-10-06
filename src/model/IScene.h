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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __IScene__
#define __IScene__

#include "IRectShape.h"
#include "PeriodicTask.h"

class QGraphicsScene;

namespace interlude
{

/*!
\addtogroup ITLModel
@{
*/

class VSceneView;
class Master;
typedef class SMARTP<Master>			SMaster;
class IScene;
typedef class SMARTP<IScene>			SIScene;
class ISceneSync;
typedef class SMARTP<ISceneSync>		SISceneSync;
class IFileWatcher;
typedef class SMARTP<IFileWatcher>		SIFileWatcher;
class ISignalNode;
typedef class SMARTP<ISignalNode>		SISignalNode;

//--------------------------------------------------------------------------
/*! \brief a scene model
*/
class IScene : public IRectShape, public PeriodicTask
{	
	bool			fFullScreen;
	SISceneSync		fSync;
	SIFileWatcher	fFileWatcher;
	SISignalNode	fSignals;
	VSceneView *	fView;
	
	public:		
		static const std::string kSceneType;
		static SMARTP<IScene> create(IObject * parent)	{ return new IScene(parent); }

		bool			getFullScreen() const		{ return fFullScreen; }
		void			setFullScreen(bool state)	{ fFullScreen = state; }
		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);

		/// \brief creates the scene virtual nodes
		virtual void	createVirtualNodes ();

		/// \brief makes a topological sort of the scene elements according to their synchronizations set
		virtual void	sort ();

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
			
		/*! \brief cleanup the relations set
			\see ISync::cleanup
		*/
		virtual void cleanupSync();

		/// \brief a periodic task to propagate modification state from masters to slaves
		virtual void ptask ();

		/// \brief \c del() method: a scene can't be deleted
		virtual void del () {}
		
		QGraphicsScene * getScene () const;
		VSceneView *	getView () const				{ return fView; }
		void			setView (VSceneView * view) 	{ fView = view; }
		VGraphicsItemView*	graphicView() const			{ return (VGraphicsItemView*)fView; }

	protected:
				 IScene(IObject * parent);
		virtual ~IScene();
};

/*!
@}
*/

} // end namespoace

#endif
