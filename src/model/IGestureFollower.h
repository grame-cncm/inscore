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


#ifndef __IGestureFollower__
#define __IGestureFollower__

#include <string>
#include <vector>

#include "TGestureFollowerPlugin.h"
#include "TRect.h"
#include "IRectShape.h"


namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IGesture;
class IGestureFollower;
typedef class libmapping::SMARTP<IGestureFollower>	SIGestureFollower;
//--------------------------------------------------------------------------
/*!
	\brief a rectangle shape.
*/
class IGestureFollower : public IRectShape
{
	TGestureFollowerPlugin*	fGFLib;
	int fGesturesOffset;			// offset to the first gesture in the elements list
	IGesture*	fLearner;

	bool	createGestureFollower (int sigDimension, int buffsize, std::vector<std::string>& gestures);

	public:
		
		static const std::string kGestureFollowerType;
		static SIGestureFollower create(const std::string& name, IObject* parent)	{ return new IGestureFollower(name, parent); }

		virtual void	accept (Updater*);
				int		gesturesCount () const		{ return elements().size() - fGesturesOffset; }

		const float*	where() const				{ return fGFLib->where(); }
		const float*	likelihood() const			{ return fGFLib->likelihood(); }
		int				getPhraseSize(int i) const	{ return fGFLib->getPhraseSize(i); }
		int				getCapacity() const			{ return fGFLib->getCapacity(); }
		int				getFrameSize() const		{ return fGFLib->getFrameSize(); }
		bool			following() const;
		bool			learning() const;
		bool			idle() const;

		float			likelihoodThreshold(int index) const;
		void			learn (IGesture* gesture);

	protected:
				 IGestureFollower( const std::string& name, IObject* parent );
		virtual ~IGestureFollower();	

		IGesture*	getGesture (const std::string& name) const;
		IGesture*	getGesture (int index) const;

		void	setLikelyhoodWindow (int size);
		void	setTolerance (float t);
		int		getLikelyhoodWindow () const;
		float	getTolerance () const;

		void	follow ();
		void	learn (const std::string& gesture);
		void	stop ();

		/// \brief the data message handler
		virtual MsgHandler::msgStatus data (const IMessage* msg);

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

		/// \brief \c 'get' without parameter form: gives the corresponding 'set' message
		virtual SIMessageList getSetMsg () const;
};

/*! @} */

} // end namespoace

#endif
