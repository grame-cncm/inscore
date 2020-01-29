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

#include <string>
#include "QPlugin.h"

class GestureFollower;
class GFClient;

namespace inscore
{

class TGestureFollowerPlugin : public QPlugin {

		typedef GestureFollower *	(* TNewFunction) (int maxPhrases, int vecSize, long capacity, GFClient*);
		typedef void				(* TVoidVoidFunction) (GestureFollower * gf);
		typedef void				(* TVoidIntFunction) (GestureFollower * gf, int);
		typedef void				(* TVoidFloatFunction) (GestureFollower * gf, float);
		typedef void				(* TVoidFloatPIntFunction) (GestureFollower * gf, float*, int);
		typedef int					(* TIntVoidFunction) (GestureFollower * gf);
		typedef int					(* TIntIntFunction) (GestureFollower * gf, int);
		typedef float				(* TFloatVoidFunction) (GestureFollower * gf);
		typedef const float*		(* TFloatPVoidFunction) (GestureFollower * gf);
		typedef const float*		(* TFloatPIntFunction) (GestureFollower * gf, int);
		typedef const char*			(* TCharPVoidFunction) ();

		static TCharPVoidFunction	fVersionStr;
		static TNewFunction			fNew;
		static TVoidVoidFunction	fDel;
		static TVoidIntFunction		fStartLearn;
		static TVoidVoidFunction	fStopLearn;
		static TVoidIntFunction		fClear;
		static TVoidVoidFunction	fClearAll;
		static TVoidVoidFunction	fStartFollow;
		static TVoidVoidFunction	fStopFollow;
		static TVoidIntFunction		fSetLikelihoodWindow;
		static TIntVoidFunction		fGetMaxPhrases;
		static TIntVoidFunction		fGetFrameSize;
		static TIntVoidFunction		fGetCapacity;
		static TIntVoidFunction		fGetLikelihoodWindow;
		static TVoidFloatFunction	fSetTolerance;
		static TFloatVoidFunction	fGetTolerance;
		static TVoidFloatPIntFunction fObservation;
		static TIntVoidFunction		fLikeliest;
		static TFloatPVoidFunction	fWhere;
		static TFloatPVoidFunction	fLikelihood;
		static TFloatPVoidFunction	fSpeed;
		static TIntIntFunction		fGetPhraseSize;
		static TFloatPIntFunction	fGetPhraseData;
		static TIntVoidFunction		fGetState;

		
		bool				load ();
		static bool			isResolved ();
		GestureFollower *	create (int maxPhrases, int vecSize, long capacity) const;
		void				del () const;
		
		GestureFollower * fGF;

	public:
				 TGestureFollowerPlugin(int maxPhrases, int vecSize, long capacity);
		virtual ~TGestureFollowerPlugin();

		const char*		versionStr	();
		bool			isAvailable	();
		bool			following	();
		bool			learning	();
		bool			idle		();
		void			stop ();

		void			startLearn	(int phraseIndex);
		void			stopLearn	();
		void			clear		(int phraseIndex);
		void			clearAll	();
		void			startFollow	();
		void			stopFollow	();
		void			setLikelihoodWindow (int size);
		int				getMaxPhrases () const;
		int				getFrameSize () const;
		int				getCapacity () const;
		int				getLikelihoodWindow () const;
		void			setTolerance (float tolerance);
		float			getTolerance () const;
		void			observation (float* data, int size);
		int				likeliest() const;
		const float*	where() const;
		const float*	likelihood() const;
		const float*	speed () const;
		int				getPhraseSize(int) const;
		const float*	getPhraseData(int) const;
		int				getState() const;
};


} // end namespace

#endif

