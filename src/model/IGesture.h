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


#ifndef __IGesture__
#define __IGesture__

#include <string>
#include <vector>

#include "IVNode.h"

class GestureFollower;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class TGestureFollowerPlugin;
class IGesture;
typedef class libmapping::SMARTP<IGesture>	SIGesture;
//--------------------------------------------------------------------------
/*!
	\brief a rectangle shape.
*/
class IGesture : public IVNode
{
	TGestureFollowerPlugin * fGF;
	int					fIndex;			// the gesture index within the follower
	float				fLikelihoodThreshold;
	std::vector<float>	fValues;

	public:
		static SIGesture create(const std::string& name, IObject* parent, int index, TGestureFollowerPlugin * gf)	
				{ return new IGesture(name, parent, index, gf); }

		virtual void	accept (Updater*);

		/// \brief \c 'get' without parameter form: gives the corresponding 'set' message
		virtual SIMessageList getSetMsg () const;

		void	observe (float* values, int size);
		void	startLearn ();
		void	stopLearn ();
		void	clearGesture ();

	protected:
				 IGesture( const std::string& name, IObject* parent, int index, TGestureFollowerPlugin * gf);
		virtual ~IGesture();	

		void	setLikelihoodThreshold (float value)		{ fLikelihoodThreshold = value; }
		float	getLikelihoodThreshold () const				{ return fLikelihoodThreshold; }

		void	learn (float* values, int size);

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
