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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __ISignalHandlers__
#define __ISignalHandlers__

#ifdef WIN32
#pragma warning (disable : 4800 4805 4355)
#endif

#include <algorithm>
#include <iostream>

#include "TSignal.h"
#include "rational.h"
#include "TRect.h"
#include "Tools.h"
#include "smartpointer.h"

#include "deelx.h"

namespace inscore
{

/*!
\addtogroup ITLModel Data Model
@{
*/

class IObject;
typedef class libmapping::SMARTP<IObject>	SIObject;

//--------------------------------------------------------------------------
/// \brief The base class for signal handling
class SigHandler : public libmapping::smartable {
	protected:
		virtual ~SigHandler() {}
	public:
		/// \brief the possible signal processing states
		enum sigStatus	{ kBadParameters, kProcessed=1};
		virtual sigStatus operator ()(const ParallelSignal* sig, std::pair<float,float> range)  = 0;
        virtual sigStatus operator ()(const ParallelSignal* sig, std::pair<int,int> range) = 0;
};
typedef libmapping::SMARTP<SigHandler> SSigHandler;

//--------------------------------------------------------------------------
/*!
	\brief a signal handler to set an object field.
*/
template <typename O, typename T> class TSetMethodSigHandler : public SigHandler
{
	public: 
		typedef void (O::*SigHandlerMethod)(T);
		
		static SSigHandler create(O* obj, SigHandlerMethod method)	{ return new TSetMethodSigHandler<O,T> (obj, method); }
		virtual sigStatus operator ()(const ParallelSignal* sig, std::pair<float,float> range)			{
            if(sig->dimension() != 1) return kBadParameters;
			T val; float fval;
            std::vector<float> dump = sig->signal(0)->dump();
            fval = dump.empty() ? sig->signal(0)->defaultValue() : dump.back(); // we take the last written value of the buffer
            // apply the range
            fval = range.first + (range.second-range.first)*(fval+1)/2;
            val = T(fval);
            (fObject->*fMethod)(val);
            return kProcessed;
		}
        virtual sigStatus operator ()(const ParallelSignal* sig, std::pair<int,int> range) {
            return operator()(sig, std::pair<float,float>((float)(range.first), (float)(range.second)));
        }

	protected:
		O*	fObject;
		SigHandlerMethod	fMethod;
		TSetMethodSigHandler(O* obj, SigHandlerMethod method) : fObject(obj), fMethod(method) {}
};

template <typename O> class TSetMethodSigHandler<O, libmapping::rational> : public SigHandler
{
	protected:
		typedef void (O::*SigHandlerMethod)(const libmapping::rational&);

		O*	fObject;
		SigHandlerMethod	fMethod;
		TSetMethodSigHandler(O* obj, SigHandlerMethod method) : fObject(obj), fMethod(method) {}

	public:		
		static SSigHandler create(O* obj, SigHandlerMethod method)	{ return new TSetMethodSigHandler<O,libmapping::rational> (obj, method); }
		virtual sigStatus operator ()(const ParallelSignal* sig, std::pair<float, float> range)			{
			if(sig->dimension() != 1) return kBadParameters;
            std::vector<float> dump = sig->signal(0)->dump();
            float fval = dump.empty() ? sig->signal(0)->defaultValue() : dump.back();
            // apply the range
            fval = range.first + (range.second-range.first)*(fval+1)/2;
            (fObject->*fMethod)(libmapping::rational(fval));
            return kProcessed;
		}
        virtual sigStatus operator ()(const ParallelSignal* sig, std::pair<int,int> range) {
            return operator()(sig, std::pair<float,float>((float)(range.first), (float)(range.second)));
        }
};



/*! @} */

} // end namespoace

#endif
