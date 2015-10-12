/*
  Copyright (c) Grame 2010

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

#ifndef __benchtools__
#define __benchtools__

#include <string>
#include <vector>
#include <map>

namespace inscore
{

#define __is_uint32	unsigned int
#define __is_int32	int

#ifdef __x86_64__
#define __is_uint64	unsigned long int
#define __is_int64	long int
#else
#define __is_uint64	unsigned long long int
#define __is_int64		long long int
#endif

#ifndef WIN32
__is_uint64  rdtsc(void);
#else
__is_uint64 __cdecl rdtsc(void);
#endif
__is_uint64  getTime(void);

//_________________________________________________________________________________
class bench
{
	public:
		static float	usec2ticks(void);
		static void		init(const char* sigs[], unsigned short size = 3000);
		static void		start();
		static void		stop();
		static bool		running();
		static void		put(const std::string& sig, float val);
		static void		write(const std::string& toFile);
};


//#define RUNBENCH

#ifdef RUNBENCH
#define  timebench(name,f)				\
{										\
	__is_uint64 start = getTime();			\
	f;									\
	__is_uint64 elapsed = getTime() - start;	\
	bench::put (name, elapsed);			\
}
#else
#define  timebench(name,f) f
#endif

} // end namespace

#endif
