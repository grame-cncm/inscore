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
		typedef void				(* TVoidVoidFunction) (GestureFollower * gf);
		typedef void				(* TVoidIntFunction) (GestureFollower * gf, int);
		typedef void				(* TVoidFloatFunction) (GestureFollower * gf, float);
		typedef void				(* TVoidFloatPIntFunction) (GestureFollower * gf, float*, int);
		typedef int					(* TIntVoidFunction) (GestureFollower * gf);
		typedef float				(* TFloatVoidFunction) (GestureFollower * gf);
		typedef const float*		(* TFloatPVoidFunction) (GestureFollower * gf);

		TNewFunction		fNew;
		TVoidVoidFunction	fDel;
		TVoidIntFunction	fStartLearn;
		TVoidVoidFunction	fStopLearn;
		TVoidIntFunction	fClear;
		TVoidVoidFunction	fClearAll;
		TVoidVoidFunction	fStartFollow;
		TVoidVoidFunction	fStopFollow;
		TVoidIntFunction	fSetLikelihoodWindow;
		TIntVoidFunction	fGetMaxPhrases;
		TIntVoidFunction	fGetFrameSize;
		TIntVoidFunction	fGetCapacity;
		TIntVoidFunction	fGetLikelihoodWindow;
		TVoidFloatFunction	fSetTolerance;
		TFloatVoidFunction	fGetTolerance;
		TVoidFloatPIntFunction fObservation;
		TIntVoidFunction	fLikeliest;
		TFloatPVoidFunction	fWhere;
		TFloatPVoidFunction	fLikelihood;
		TFloatPVoidFunction	fSpeed;
		TIntVoidFunction	fGetState;

	public:
				 TGestureFollowerPlugin() : fNew(0), fDel(0) {};
		virtual ~TGestureFollowerPlugin()		{};

		bool	load ();
		GestureFollower *	create (int maxPhrases, int vecSize, long capacity) const;
		void			del (GestureFollower *) const;

		void			startLearn	(GestureFollower * gf, int phraseIndex);
		void			stopLearn	(GestureFollower * gf);		
		void			clear		(GestureFollower * gf, int phraseIndex);
		void			clearAll	(GestureFollower * gf);
		void			startFollow	(GestureFollower * gf);
		void			stopFollow	(GestureFollower * gf);
		void			setLikelihoodWindow (GestureFollower * gf, int size);
		int				getMaxPhrases (GestureFollower * gf) const;
		int				getFrameSize (GestureFollower * gf) const;
		int				getCapacity (GestureFollower * gf) const;
		int				getLikelihoodWindow (GestureFollower * gf) const;
		void			setTolerance (GestureFollower * gf, float tolerance);
		float			getTolerance (GestureFollower * gf) const;
		void			observation (GestureFollower * gf, float* data, int size);
		int				likeliest(GestureFollower * gf) const;
		const float*	where(GestureFollower * gf) const;
		const float*	likelihood(GestureFollower * gf) const;
		const float*	speed (GestureFollower * gf) const;
		int				getState(GestureFollower * gf) const;
};


} // end namespace

#endif

