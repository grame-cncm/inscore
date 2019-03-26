/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame - Centre national de création musicale,
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/

#include <iostream>
#include <algorithm>

#include "TSchedulable.h"
#include "TScheduler.h"

using namespace std;

//-------------------------------------------------------------------
void TLevel::resortSome (TLevel* to, unsigned char index, size_t count)
{
	while (count--) {
		TSchedulable* e = pop(index);
		if (!e) break;
        TSorterDate d (e->date());
        to->puta (e, d.part(fNexLevelPart));
	}
}

//-------------------------------------------------------------------
void TLevel::resortAll (TLevel* to, unsigned char index)
{
	TSchedulable* e = pop(index);
	while (e) {
        TSorterDate d (e->date());
        to->puta (e, d.part(fNexLevelPart));
        e = pop(index);
	}
}

//-------------------------------------------------------------------
void TLevel::clock (unsigned char i)
{
	if ( i != fPos ) resortSome(fNextLevel, fPos);
	else {
		resortAll (fNextLevel, i);
		fNextLevel->swap();
		fPos++;
	}
}

//-------------------------------------------------------------------
void TLevel::init  (unsigned char level, TLevel* next, int nextPart)
{
    fNextLevel 		= next;
    fNexLevelPart 	= nextPart;
    fLevel 			= level;
    if (level == 3) fAlternate = 0;     // no alternate buffer for top level
}

//-------------------------------------------------------------------
TScheduler::TScheduler() : fDate(0)
{
    fLevel[3].init (3, &fLevel[2], TSorterDate::kMLsb);
    fLevel[2].init (2, &fLevel[1], TSorterDate::kLMsb);
    fLevel[1].init (1, &fLevel[0], TSorterDate::kLsb);
    fLevel[0].init (0, 0, 0);
}

//-------------------------------------------------------------------
void TScheduler::put(TSchedulable * e)
{
	fMutex.lock();
	TSorterDate date ( e->date() );
	if (date.get() <= fDate) {
		fReady.push_back(e);
	}
	else {
		TSorterDate current (fDate);
		if (date.msb() > current.msb())
			fLevel[3].put (e, date.msb());
		else if (date.mlsb() > current.mlsb())
			fLevel[2].put (e, date.mlsb());
		else if (date.lmsb() > current.lmsb())
			fLevel[1].put (e, date.lmsb());
		else if (date.lsb() > current.lsb())
			fLevel[0].put (e, date.lsb());
		else fReady.push_back(e);
	}
	fMutex.unlock();
}

//-------------------------------------------------------------------
TReadyList TScheduler::clock()
{
	fMutex.lock();
	TReadyList out = fReady;
	
    TSorterDate current (++fDate);
    fLevel[3].clock (current.msb());
    fLevel[2].clock (current.mlsb());
    fLevel[1].clock (current.lmsb());

	TSchedulable* e = fLevel[0].pop(current.lsb());
	while (e) {
 		out.push_back(e);
        e = fLevel[0].pop(current.lsb());
	}

	fReady.clear();
	fMutex.unlock();
	return out;
}
