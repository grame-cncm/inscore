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

#include <iostream>
#include "IAppl.h"
#include "TGestureFollowerPlugin.h"

using namespace std;

namespace inscore
{

static const char* gflibName = "GFLib";
static const char* gflibNewStr = "newGestureFollower";
static const char* gflibDelStr = "delGestureFollower";

//----------------------------------------------------------------------------
bool TGestureFollowerPlugin::load ()
{
	string file = IAppl::absolutePath (gflibName);
	if (TPlugin::load(file.c_str())) {
		fNew = resolve<TNewFunction> (gflibNewStr);
		if (fNew == 0) return false;
		fDel = resolve<TDelFunction> (gflibDelStr);
		if (fDel == 0) return false;
	}
	else return false;
	return true;
}
		
//----------------------------------------------------------------------------
GestureFollower * TGestureFollowerPlugin::create (int maxPhrases, int vecSize, long capacity) const
		{ return fNew ? fNew( maxPhrases, vecSize, capacity) : 0; }

void TGestureFollowerPlugin::del (GestureFollower * gf) const
		{ if (fDel) fDel(gf); }


} // end namespace
