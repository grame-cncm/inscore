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

#pragma once

#include <cstdint>
#include <mutex>
#include <queue>
#include <vector>

#include "TFifo.h"

namespace inscore2
{

class TSchedulable;
typedef TFifo<TSchedulable> 		TEltsList;
typedef std::vector<TSchedulable*> 	TReadyList;

//-------------------------------------------------------------------
class TSorterDate {
    union {
        int32_t         value;
        unsigned char   part[4];
    } fDate;

   public:
#ifdef __LITTLE_ENDIAN__
    enum { kLsb, kLMsb, kMLsb, kMsb };
#else
    enum { kMsb, kMLsb, kLMsb, kLsb };
#endif
				 TSorterDate( int32_t value) { fDate.value = value; }
        virtual ~TSorterDate() {}
    
        inline TSorterDate& operator = (int32_t value)   { fDate.value = value; return *this; }
        inline int32_t       get() const        { return fDate.value; }
        inline unsigned char part(int i) const  { return fDate.part[i]; }
        inline unsigned char lsb() const        { return fDate.part[kLsb]; }
        inline unsigned char lmsb() const   	{ return fDate.part[kLMsb]; }
        inline unsigned char mlsb() const   	{ return fDate.part[kMLsb]; }
        inline unsigned char msb() const    	{ return fDate.part[kMsb]; }
};

//-------------------------------------------------------------------
class TLevel {
    
        TEltsList   fBuffer[2][256];
        int         fCurrent = 0;
        int         fAlternate = 1;
        unsigned char fPos   = 1;		// the current resort position in the buffer
        unsigned char fLevel = 0;		// used for debug only
        int		 	fNexLevelPart = 0;  // the date part corresponding to the next level
        TLevel*     fNextLevel = 0;		// the next level (where to put sorted events)
	
				void resortAll  (TLevel* to, unsigned char i);
				void resortSome (TLevel* to, unsigned char i, size_t count=20);

        inline void                 puta(TSchedulable *e, unsigned char i)  { fBuffer[fAlternate][i].push( e ); }
        inline 	void 				swap ()        		{ int tmp=fCurrent;  fCurrent=fAlternate; fAlternate=tmp; }

    public:
                 TLevel() {}
        virtual ~TLevel() {}

        inline void                 put(TSchedulable *e, unsigned char i)   { fBuffer[fCurrent][i].push( e ); }
        inline TSchedulable*        pop(unsigned char index) 				{ return fBuffer[fCurrent][index].pop(); }

        void clock (unsigned char i);
        void init  (unsigned char level, TLevel* next, int nextPart);
};

//-------------------------------------------------------------------
class TScheduler {

	std::mutex 	fMutex;
	int32_t 	fDate = 0; 		// the current date
	TLevel		fLevel[4];
	TReadyList 	fReady;

	public:
				 TScheduler();
		virtual ~TScheduler() {}

	void 			put(TSchedulable *);
	TReadyList		clock();
	inline int32_t	date() const 		{ return fDate; }
};

}
