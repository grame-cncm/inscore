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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr

*/


#ifndef __msAtomicIntel__
#define __msAtomicIntel__

#ifdef __SMP__
#	define LOCK "lock ; "
#else
#	define LOCK ""
#endif

//----------------------------------------------------------------
// CAS functions
//----------------------------------------------------------------
static inline char CAS (volatile void * addr, volatile void * value, void * newvalue)
{
	register char ret;
	__asm__ __volatile__ (
		"# CAS \n\t"
		LOCK "cmpxchg %2, (%1) \n\t"
		"sete %0               \n\t"
		:"=a" (ret)
		:"c" (addr), "d" (newvalue), "a" (value)
	);
	return ret;
}

#define __BREG__
#if (defined(__BREG__) || (defined(__APPLE__)) && !defined(__x86_64__))

/*
On MacIntel, version 4.0.1 of the gcc compiler gives the following error:
can't find a register in class 'BREG' while reloading 'asm'
To solve that, %%ebx register has to be saved and restored.
*/

static inline char CAS2 (volatile void * addr, volatile void * v1, volatile long v2, void * n1, long n2)
{
	register char ret;
	__asm__ __volatile__ (
		"# CAS2 \n\t"
		"xchgl %%esi, %%ebx \n\t"
		LOCK "cmpxchg8b (%1) \n\t"
		"sete %0             \n\t"
		"xchgl %%ebx, %%esi \n\t"  /* Restore %ebx.  */
		:"=a" (ret)
		:"D" (addr), "d" (v2), "a" (v1), "S" (n1), "c" (n2)
	);
	return ret;
}

#else

static inline char CAS2 (volatile void * addr, volatile void * v1, volatile long v2, void * n1, long n2)
{
	register char ret;
	__asm__ __volatile__ (
		"# CAS2 \n\t"
#ifdef __x86_64__
		LOCK "cmpxchg16b (%1) \n\t"
#else
		LOCK "cmpxchg8b (%1) \n\t"
#endif
		"sete %0               \n\t"
		:"=a" (ret)
		:"D" (addr), "d" (v2), "a" (v1), "b" (n1), "c" (n2)
	);
	return ret;
}

#endif

#endif
