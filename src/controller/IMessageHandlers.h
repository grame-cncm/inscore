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

#ifndef __IMessageHandlers__
#define __IMessageHandlers__

#ifdef WIN32
#pragma warning (disable : 4800 4805 4355)
#endif

#include <algorithm>
#include <iostream>

#include "IMessage.h"
#include "rational.h"
#include "TRect.h"
#include "Tools.h"
#include "smartpointer.h"

namespace inscore
{

/*!
\addtogroup ITLModel Data Model
@{
*/

class IObject;
class Master;
typedef class libmapping::SMARTP<IObject>	SIObject;


//--------------------------------------------------------------------------
/// \brief The base class for message handling
class MsgHandler : public libmapping::smartable {
	protected:
		virtual ~MsgHandler() {}
	public:
		/// \brief the possible message processing states
		enum msgStatus	{ kBadAddress, kProcessed=1, kProcessedNoChange=2, kBadParameters=4, kCreateFailure=8 };
		virtual msgStatus operator ()(const IMessage* msg)  = 0;
};
typedef libmapping::SMARTP<MsgHandler> SMsgHandler;

//--------------------------------------------------------------------------
/// \brief a message handler that calls an object method with the message as argument
template <typename C, typename T = MsgHandler::msgStatus (C::*)(const IMessage*)> class TMethodMsgHandler : public MsgHandler 
{
	public: 
		static SMsgHandler create(C* obj, T method)					{ return new TMethodMsgHandler<C,T> (obj, method); }
		virtual msgStatus operator ()(const IMessage* msg)			{ return (fObject->*fMethod)(msg); }
	protected:
		C*	fObject;
		T	fMethod;
		TMethodMsgHandler(C* obj, T method) : fObject(obj), fMethod(method) {}
};

//--------------------------------------------------------------------------
/// \brief a message handler specialized to method with no argument
template <typename C> class TMethodMsgHandler<C, void (C::*)(void)> : public MsgHandler 
{
	public: 
		typedef void (C::*MsgHandlerMethod)(void);
		static SMsgHandler create(C* obj, MsgHandlerMethod method)	{ return new TMethodMsgHandler<C,MsgHandlerMethod> (obj, method); }
		virtual msgStatus operator ()(const IMessage*)			{ (fObject->*fMethod)(); return kProcessed; }
	protected:
		C*	fObject;
		MsgHandlerMethod	fMethod;
		TMethodMsgHandler(C* obj, MsgHandlerMethod method) : fObject(obj), fMethod(method) {}
};

//--------------------------------------------------------------------------
/// \brief a message handler specialized to const method with no argument
template <typename C> class TMethodMsgHandler<C, void (C::*)(void) const> : public MsgHandler 
{
	public: 
		typedef void (C::*MsgHandlerMethod)(void) const;
		static SMsgHandler create(C* obj, MsgHandlerMethod method)	{ return new TMethodMsgHandler<C,MsgHandlerMethod> (obj, method); }
		virtual msgStatus operator ()(const IMessage*)			{ (fObject->*fMethod)(); return kProcessedNoChange; }
	protected:
		C*	fObject;
		MsgHandlerMethod	fMethod;
		TMethodMsgHandler(C* obj, MsgHandlerMethod method) : fObject(obj), fMethod(method) {}
};

//--------------------------------------------------------------------------
/*!
	\brief a message handler to set an object field.
*/
template <typename O, typename T> class TSetMethodMsgHandler : public MsgHandler 
{
	public: 
		typedef void (O::*MsgHandlerMethod)(T);
		
		static SMsgHandler create(O* obj, MsgHandlerMethod method)	{ return new TSetMethodMsgHandler<O,T> (obj, method); }
		virtual msgStatus operator ()(const IMessage* msg)			{ 
			if ( msg->size() != 1 ) return kBadParameters;

			T val; float fval; int ival;
			if ( !msg->param(0, val) ) {
				if ( msg->param(0, ival) ) val = T(ival);
				else if ( msg->param(0, fval) ) val = T(fval);
				else return kBadParameters;
			}
			(fObject->*fMethod)( val );
			return kProcessed;
		}

	protected:
		O*	fObject;
		MsgHandlerMethod	fMethod;
		TSetMethodMsgHandler(O* obj, MsgHandlerMethod method) : fObject(obj), fMethod(method) {}
};

template <typename O> class TSetMethodMsgHandler<O, libmapping::rational> : public MsgHandler 
{
	protected:
		typedef void (O::*MsgHandlerMethod)(const libmapping::rational&);

		O*	fObject;
		MsgHandlerMethod	fMethod;
		TSetMethodMsgHandler(O* obj, MsgHandlerMethod method) : fObject(obj), fMethod(method) {}

	public:		
		static SMsgHandler create(O* obj, MsgHandlerMethod method)	{ return new TSetMethodMsgHandler<O,libmapping::rational> (obj, method); }
		virtual msgStatus operator ()(const IMessage* msg)			{ 
			if ( msg->size() == 1 ) {
				int n; float nf; std::string datestr;
				if (msg->param(0, n)) (fObject->*fMethod)( libmapping::rational(n,1) );
				else if (msg->param(0, nf)) (fObject->*fMethod)( libmapping::rational(int(nf*10000),10000) );
				else if (msg->param(0, datestr)) {
					libmapping::rational date = Tools::str2rational(datestr);
					if (date.getDenominator()) (fObject->*fMethod)( date );
				}
				else return kBadParameters;
			}
			else if ( msg->size() == 2 ) {
				int n, d;
				if ( !msg->param(0, n) || !msg->param(1, d)) return kBadParameters;
				(fObject->*fMethod)( libmapping::rational(n,d) );
			}
			else return kBadParameters;
			return kProcessed;
		}
};

template <typename O> class TSetMethodMsgHandler<O, std::string> : public MsgHandler 
{
	public: 
		typedef void (O::*MsgHandlerMethod)(const std::string&);
		
		static SMsgHandler create(O* obj, MsgHandlerMethod method)	{ return new TSetMethodMsgHandler<O,std::string> (obj, method); }
		virtual msgStatus operator ()(const IMessage* msg)			{ 
			if ( msg->size() != 1 ) return kBadParameters;
			std::string str;
			if ( !msg->param(0, str)) return kBadParameters;
			(fObject->*fMethod)( str );
			return kProcessed;
		}

	protected:
		O*	fObject;
		MsgHandlerMethod	fMethod;
		TSetMethodMsgHandler(O* obj, MsgHandlerMethod method) : fObject(obj), fMethod(method) {}
};

template <typename O> class TSetMethodMsgHandler<O, TFloatSize> : public MsgHandler 
{
	public: 
		typedef void (O::*MsgHandlerMethod)(const TFloatSize&);
		
		static SMsgHandler create(O* obj, MsgHandlerMethod method)	{ return new TSetMethodMsgHandler<O,TFloatSize> (obj, method); }
		virtual msgStatus operator ()(const IMessage* msg)			{ 
			if ( msg->size() != 2 ) return kBadParameters;
			float n, d;
			if ( msg->cast_param(0, n) && msg->cast_param(1, d)) {
                (fObject->*fMethod)( TFloatSize(n,d) );
            }
			else return kBadParameters;
			return kProcessed;
		}

	protected:
		O*	fObject;
		MsgHandlerMethod	fMethod;
		TSetMethodMsgHandler(O* obj, MsgHandlerMethod method) : fObject(obj), fMethod(method) {}
};

//--------------------------------------------------------------------------
/// \brief a special handler for Master dy changges
template <> class TSetMethodMsgHandler<Master, void (Master::*)(float)> : public MsgHandler 
{
	public: 
		typedef void (Master::*MsgHandlerMethod)(float);
		static SMsgHandler create(IObject* slave, Master*  obj, MsgHandlerMethod method)	
						{ return new TSetMethodMsgHandler<Master,MsgHandlerMethod> (slave, obj, method); }
		virtual msgStatus operator ()(const IMessage* msg);

	protected:
		IObject*	fSlave;
		Master*		fObject;
		MsgHandlerMethod	fMethod;
		TSetMethodMsgHandler(IObject* slave, Master* obj, MsgHandlerMethod method) : fSlave(slave), fObject(obj), fMethod(method) {}
};


//--------------------------------------------------------------------------------
// operators for the \c set messages
//--------------------------------------------------------------------------------
class TSetOperator {
	public: template<typename T> void set(T& dst, const T& src) const { dst = src; }
};

class TDSetOperator {
	public: template<typename T> void set(T& dst, const T& src) const { dst += src; }
};

class TMSetOperator {
	public: template<typename T> void set(T& dst, const T& src) const { dst *= src; }
};


//--------------------------------------------------------------------------------
/// \brief a message handler to set a single field value
//--------------------------------------------------------------------------------
template <typename T, typename S=TSetOperator> class TSetMsgHandler : public MsgHandler
{
	protected:
		T& fValue;
			 TSetMsgHandler(T& val) : fValue(val) {}
	virtual ~TSetMsgHandler() {}

	public:
	static libmapping::SMARTP<TSetMsgHandler> create(T& val) { return new TSetMsgHandler<T,S> (val); }

		msgStatus operator ()(const IMessage* msg)
		{ 
			T val;
			if ((msg->size() == 1) && msg->param(0, val)) {
				S  setOp;
				setOp.set(fValue, val); 
				return MsgHandler::kProcessed;
			}
			return MsgHandler::kBadParameters;
		} 
};

//--------------------------------------------------------------------------------
/// \brief a message handler to set a TFloatSize value
//--------------------------------------------------------------------------------
template <typename S> class TSetMsgHandler<TFloatSize,S> : public MsgHandler
{
	protected:
		TFloatSize& fValue;
			 TSetMsgHandler(TFloatSize& val) : fValue(val) {}
	virtual ~TSetMsgHandler() {}

	public:
	static libmapping::SMARTP<TSetMsgHandler> create(TFloatSize& val) { return new TSetMsgHandler<TFloatSize,S> (val); }

		virtual msgStatus operator ()(const IMessage* msg)
			{ 
				if (msg->size() != 2) return MsgHandler::kBadParameters;
				float n, d;
				if (msg->param(0, n) && msg->param(1, d)) {
					S  setOp;
					setOp.set(fValue, TFloatSize(n,d)); 
					return MsgHandler::kProcessed;
				}
				return MsgHandler::kBadParameters;
			} 
};

//--------------------------------------------------------------------------------
/// \brief a message handler to set a rational value
template <typename S> class TSetMsgHandler<libmapping::rational,S> : public MsgHandler
{
	protected:
		libmapping::rational& fValue;
			 TSetMsgHandler(libmapping::rational& val) : fValue(val) {}
	virtual ~TSetMsgHandler() {}

	public:
	static libmapping::SMARTP<TSetMsgHandler> create(libmapping::rational& val) { return new TSetMsgHandler<libmapping::rational,S> (val); }

		virtual msgStatus operator ()(const IMessage* msg)
			{ 
				if (msg->size() != 2) return MsgHandler::kBadParameters;
				int n, d;
				if (msg->param(0, n) && msg->param(1, d)) {
					S  setOp;
					setOp.set(fValue, libmapping::rational(n,d)); 
					return MsgHandler::kProcessed;
				}
				return MsgHandler::kBadParameters;
			} 
};


//--------------------------------------------------------------------------
///!	\brief The base class for \c get messages handling.
//--------------------------------------------------------------------------
class GetParamMsgHandler : public libmapping::smartable {
	public: 
		virtual ~GetParamMsgHandler() {}
		/// \brief output a value of an object to a message
		virtual SIMessage&  print(SIMessage&) const = 0;
};
typedef libmapping::SMARTP<GetParamMsgHandler> SGetParamMsgHandler;

//--------------------------------------------------------------------------
///!	\brief The base class for handling messages returning a message list.
//--------------------------------------------------------------------------
class GetParamMultiMsgHandler : public libmapping::smartable {
	public: 
		virtual ~GetParamMultiMsgHandler() {}
		/// \brief output a value of an object to a message
		virtual SIMessageList  print(SIMessageList&) const = 0;
};
typedef libmapping::SMARTP<GetParamMultiMsgHandler> SGetParamMultiMsgHandler;

//--------------------------------------------------------------------------
///! \brief a get object parameter message handler 
//--------------------------------------------------------------------------
template <typename T> class TGetParamMsgHandler : public GetParamMsgHandler {
		const T& fValue;
		TGetParamMsgHandler(const T& val) : fValue(val) {}
	public: 
		static SGetParamMsgHandler create(const T& val) { return new TGetParamMsgHandler<T> (val); }
		virtual SIMessage&  print(SIMessage& out) const	{ *out << fValue; return out; }
};

//--------------------------------------------------------------------------
///! \brief a get object parameter method handler 
//--------------------------------------------------------------------------
template <typename C, typename T> class TGetParamMethodHandler : public GetParamMsgHandler {
		C* fObject;
		T fMethod;
		TGetParamMethodHandler(C* obj, T method) : fObject(obj), fMethod(method) {}
	public: 
		static SGetParamMsgHandler create(C* obj, T method) { return new TGetParamMethodHandler<C,T> (obj, method); }
		virtual SIMessage&  print(SIMessage& out) const	{ *out << (fObject->*fMethod)(); return out; }
};

//--------------------------------------------------------------------------
///! \brief a get object multiple messages parameter method handler 
//--------------------------------------------------------------------------
template <typename C, typename T> class TGetParamMultiMethodHandler : public GetParamMultiMsgHandler {
		C* fObject;
		T fMethod;
		TGetParamMultiMethodHandler(C* obj, T method) : fObject(obj), fMethod(method) {}
	public: 
		static SGetParamMultiMsgHandler create(C* obj, T method) { return new TGetParamMultiMethodHandler<C,T> (obj, method); }
		virtual SIMessageList  print(SIMessageList& out) const	{ out->list().push_back( (fObject->*fMethod)()->list() ); return out; }
};

/*! @} */

} // end namespoace

#endif
