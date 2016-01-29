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
#include "OSCStream.h"
#include "IMessage.h"
#include "IExpression.h"
#include "ExprReader.h"
#include "IColor.h"
#include "IApplVNodes.h"
#include "ITLError.h"

using namespace std;

namespace inscore
{

OSCStream* _oscout = 0;				// OSC output stream
OSCErrorStream* _oscerr = 0;		// OSC error stream

static UdpSocket* _socket = 0;		// a shared transmit socket
static UdpSocket  _evtSocket;
OSCStream gEventsStream (&_evtSocket);

//--------------------------------------------------------------------------
OSCStream::OSCStream(UdpSocket* socket)
	: fState(kIdle), fPort(1024), fAddress(kLocalhost), fOutStream(fBuffer, kOutBufferSize), fSocket(socket)
{
	fSocket->allowBroadcast();
}

//--------------------------------------------------------------------------
void OSCStream::sendEvent(const IMessage* msg, const string& dst, int port)
{
	gEventsStream.setAddress (dst);
	gEventsStream.setPort(port);
	msg->print(gEventsStream);
}

//--------------------------------------------------------------------------
bool OSCStream::start ()
{
	_socket = new UdpSocket;
	_oscout = new OSCStream(_socket);
	_oscerr = new OSCErrorStream(_socket);
	return (_socket && _oscout && _oscerr);
}

//--------------------------------------------------------------------------
void OSCStream::stop ()
{
	delete _socket;
	delete _oscout;
	delete _oscerr;
	_oscout = _oscerr = 0;
	_socket = 0;
}

//--------------------------------------------------------------------------
void OSCStream::setAddress (const string& address)
{
	IpEndpointName dst (address.c_str());
	setAddress (dst.address);
}

//--------------------------------------------------------------------------
OSCStream& OSCStream::start(const char * address)
{ 
	stream().Clear();
	if (!stream().IsReady()) cerr << "OSCStream OutboundPacketStream not ready" << endl;
	stream() << osc::BeginMessage( address ) ; 
	fState = kInProgress;
	return *this;
}

//--------------------------------------------------------------------------
OSCStream& OSCStream::end()
{
	if (state() == kInProgress) {
		stream() << osc::EndMessage;
		if (fSocket) 
			fSocket->SendTo (IpEndpointName (fAddress, fPort), stream().Data(), stream().Size() );
		fState = kIdle;
	}
	return *this;
}

#define CATCHOSC	catch (osc::Exception e) { ITLErr<< "error while sending OSC message: " << e.what() <<ITLEndl; }


OSCStream& operator <<(OSCStream& s, int val)		{ try { s.stream() << val; } CATCHOSC return s; }
OSCStream& operator <<(OSCStream& s, long val)		{ try { s.stream() << (int)val; } CATCHOSC return s; }
OSCStream& operator <<(OSCStream& s, float val)		{ try { s.stream() << val; } CATCHOSC return s; }
OSCStream& operator <<(OSCStream& s, double val)	{ try { s.stream() << float(val); } CATCHOSC return s; }

//--------------------------------------------------------------------------
OSCStream& operator <<(OSCStream& s, const string& val)	
{ 
	try { s.stream() << val.c_str(); } CATCHOSC
	return s;
}
//--------------------------------------------------------------------------
OSCStream &operator <<(OSCStream &s, const IExpression *val){
	if(val) {
		try { s.stream() << val->definition().c_str(); } CATCHOSC
	}
	return s;
}
//--------------------------------------------------------------------------
OSCStream &operator <<(OSCStream &s, IExprArgBase *val){
    string r;
	if(ExprReader::read(val, r))
		try { s.stream() << " " << r.c_str(); } CATCHOSC
    return s;
}
//--------------------------------------------------------------------------
OSCStream &operator <<(OSCStream &s, IExprOperator *val)
{
	//This method is normally useless (its only purpose is to keep Visual studio quite)
    string arg1, arg2;
    if(ExprReader::read(val->arg1(), arg1) && ExprReader::read(val->arg2(), arg2))
		try {  s.stream() << "expr( " << arg1.c_str() << " " << arg2.c_str() << ")"; } CATCHOSC
    return s;
}

//--------------------------------------------------------------------------
OSCStream& operator <<(OSCStream& s, const IMessageList* list)	
{ 
	for (unsigned int i =0; i < list->list().size(); i++) {
		IMessage* msg = (list->list())[i];
		s << msg;
	}
	return s; 
}

OSCStream& operator <<(OSCStream& s, const IColor& color)	{ color.print(s); return s; }
OSCStream& operator <<(OSCStream& s, const IMessage* msg)	{ msg->print(s); return s; }
OSCStream& operator <<(OSCStream& s, const char* val)		{ string str(val); s << str; return s; }

//--------------------------------------------------------------------------
OSCStream& operator <<(OSCStream& s, const OSCErr& val)		{ return s.start(val.fAddress); }
OSCStream& operator <<(OSCStream& s, const OSCWarn& val)	{ return s.start(val.fAddress); }
OSCStream& operator <<(OSCStream& s, const OSCStart& val)	{ return s.start(val.fAddress); }
OSCStream& operator <<(OSCStream& s, const OSCEnd )			{ return s.end(); }



//--------------------------------------------------------------------------
OSCErrorStream&	OSCErrorStream::end()
{
	if (fLogWindow) {
		fAddress+=fSStream.str();
		fLogWindow->print(fAddress.c_str());
	}
	if(fConcat) {
		fSStreamConcat << fSStream.str() << ";";
	}
	OSCStream::stream() << fSStream.str().c_str(); OSCStream::end();
	return *this;
}

//--------------------------------------------------------------------------
stringstream& OSCErrorStream::streamConcat()
{
	return fSStreamConcat;
}

//--------------------------------------------------------------------------
void OSCErrorStream::activeConcatError(bool activate)
{
	fConcat = activate;
	if (activate)
		fSStreamConcat.str("");
}

//--------------------------------------------------------------------------
OSCErrorStream& operator <<(OSCErrorStream& s, const string& val)	
{ 
	s.stream() << " " << val.c_str();
	return s; 
}
//--------------------------------------------------------------------------
OSCErrorStream& operator <<(OSCErrorStream& s, const IExpression *val){
	if(val)
		s.stream() << val->definition().c_str();
	return s;
}
//--------------------------------------------------------------------------
OSCErrorStream &operator <<(OSCErrorStream &s, const IExprArgBase *val){
    string r;
	if(ExprReader::read(val, r))
        s.stream() << " " << r;

    return s;
}



//--------------------------------------------------------------------------
OSCErrorStream& operator <<(OSCErrorStream& s, const IMessageList* list)	
{ 
	for (unsigned int i =0; i < list->list().size(); i++) {
		IMessage* msg = (list->list())[i];
		s << msg;
	}
	return s; 
}

OSCErrorStream& operator <<(OSCErrorStream& s, const IColor& color)	{ color.print(s); return s; }
OSCErrorStream& operator <<(OSCErrorStream& s, const IMessage* msg)	{ msg->print(s); return s; }
OSCErrorStream& operator <<(OSCErrorStream& s, const char* val)		{ s.stream() << " " << val; return s; }

//--------------------------------------------------------------------------
OSCErrorStream& operator <<(OSCErrorStream& s, const OSCErr& val)	{ return s.start(val.fAddress); }
OSCErrorStream& operator <<(OSCErrorStream& s, const OSCWarn& val)	{ return s.start(val.fAddress); }
OSCErrorStream& operator <<(OSCErrorStream& s, const OSCStart& val)	{ return s.start(val.fAddress); }
OSCErrorStream& operator <<(OSCErrorStream& s, const OSCEnd )		{ return s.end(); }




} // end namespace

