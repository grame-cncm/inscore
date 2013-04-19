/*
  Copyright (c) Grame 2009

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#ifndef __TGestureFollowerPlugin__
#define __TGestureFollowerPlugin__

#include "TPlugin.h"
class GestureFollower;

namespace inscore
{

class TGestureFollowerPlugin : public TPlugin {

		typedef GestureFollower *	(* TNewFunction) (int maxPhrases, int vecSize, long capacity);
		typedef void				(* TDelFunction) (GestureFollower * gf);

		TNewFunction	fNew;
		TDelFunction	fDel;

	public:
				 TGestureFollowerPlugin() : fNew(0), fDel(0) {};
		virtual ~TGestureFollowerPlugin()		{};

		bool	load ();
		GestureFollower *	create (int maxPhrases, int vecSize, long capacity) const;
		void				del (GestureFollower *) const;
};


} // end namespace

#endif
