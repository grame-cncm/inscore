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


#ifndef __msAtomicWin32__
#define __msAtomicWin32__

#ifdef __SMP__
#	define LOCK lock
#else
#	define LOCK 
#endif

#define inline __inline

//----------------------------------------------------------------
// CAS functions
//----------------------------------------------------------------
inline char CAS (volatile void * addr, volatile void * value, void * newvalue) 
{
	register char c;
	__asm {
		push	ebx
		push	esi
		mov		esi, addr
		mov		eax, value
		mov		ebx, newvalue
		LOCK cmpxchg dword ptr [esi], ebx
		sete	c
		pop		esi
		pop		ebx
	}
	return c;
}

inline char CAS2 (volatile void * addr, volatile void * v1, volatile long v2, void * n1, long n2) 
{
	register char c;
	__asm {
		push	ebx
		push	ecx
		push	edx
		push	esi
		mov		esi, addr
		mov		eax, v1
		mov		ebx, n1
		mov		ecx, n2
		mov		edx, v2
		LOCK    cmpxchg8b qword ptr [esi]
		sete	c
		pop		esi
		pop		edx
		pop		ecx
		pop		ebx
	}
	return c;
}

#endif
