/*

  Copyright © Grame 1999-2005

  This library is free software; you can redistribute it and modify it under 
  the terms of the GNU Library General Public License as published by the 
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr

*/

#ifndef __msAtomic__
#define __msAtomic__

/* by default, compiles for SMP architecture */
#define __SMP__

#if defined(powerpc) || defined(__ppc__) || defined(__MWERKS__)
	typedef struct {
		long value;
		long reserved[7];
	} TAtomic;
#else
	typedef struct {
		long value;
	} TAtomic;
#endif


#if defined(__GNUC__)
# if defined(powerpc) || defined(__ppc__)
#  include "msAtomicPPC.h"
# else
#  include "msAtomicIntel.h"
# endif

#elif defined(WIN32)
# include "msAtomicWin32.h"

#elif defined(__MWERKS__)  /* this is for CodeWarrior compiler on Macintosh */
# include "msAtomicPPC_CW.h"
#else
# error "msAtomic.h : target compiler and processor undefined"
#endif

static inline long msAtomicInc (volatile TAtomic * val)
{
    long actual;
    do {
        actual = val->value;
    } while (!CAS(val, (void *)actual, (void *)(actual+1)));
	return actual;
}

static inline long msAtomicDec (volatile TAtomic * val)
{
    long actual;
    do {
        actual = val->value;
    } while (!CAS(val, (void *)actual, (void *)(actual-1)));
	return actual;
}

#endif
