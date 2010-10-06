/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __ISignalProfiler__
#define __ISignalProfiler__

#include <QTime>
#include <string>
#include "smartpointer.h"

namespace interlude
{

/*!
\addtogroup ITLModel
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief 
*/
class ISignalProfiler
{
	std::string		fObjectName;
	std::string		fSignalName;
	int				fTimeUnit;
	QTime			fTimer;
	int				fElapsed;

	public:
	
		enum TimeUnit { PROFILER_MS = 1 , PROFILER_CS = 10 , PROFILER_DS = 100 , PROFILER_SECOND = 1000 };
	
		ISignalProfiler( const std::string& objectName, const std::string& signalName , int timeUnit = PROFILER_SECOND )
			: fObjectName(objectName)  , fSignalName(signalName) , fTimeUnit(timeUnit) , fElapsed(0) {}
		~ISignalProfiler() {}
		
		void start()	{ fTimer.start(); }
		void stop()		{ fElapsed = fTimer.elapsed(); }
		void send();
		
		void setTimeUnit( int timeUnit ) { fTimeUnit = timeUnit; }
};

/*! @} */

} // end namespoace

#endif
