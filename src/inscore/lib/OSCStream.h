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

#ifndef __OSCStream__
#define __OSCStream__

#include <string>
#include <vector>
#include <sstream>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include "TRect.h"

namespace inscore
{

//--------------------------------------------------------------------------
typedef struct OSCStart { 
	const char* fAddress;
	OSCStart() {}
	OSCStart(const char* a) : fAddress(a) {}
} OSCStart;

typedef struct OSCErr : public OSCStart { 
	OSCErr() : OSCStart("error:") {}
} OSCErr;

typedef struct OSCWarn : public OSCStart { 
	OSCWarn() : OSCStart("warning:") {}
} OSCWarn;

typedef struct OSCEnd {} OSCEnd;

#define kLocalhost	0x7f000001

class IMessage;
class IMessageList;
class IExpression;
class IExprOperator;
class IColor;

//--------------------------------------------------------------------------
/*!
\brief	OSC output streams
*/
class OSCStream 
{
	public:
	enum state	{ kIdle, kInProgress };
	
	private:
	enum		{ kOutBufferSize = 16384 };
	
	state		fState;
	int			fPort;				// the destination UDP port
	unsigned long fAddress;			// the destination IP address
	char		fBuffer[kOutBufferSize];

	osc::OutboundPacketStream	fOutStream;
	UdpSocket*					fSocket;
	
//	void initSocket();
	
	public:

	static bool start();
	static void stop();
	static void sendEvent(const IMessage* msg, const std::string& dst, int port);

				 OSCStream(UdpSocket* socket);
		virtual ~OSCStream() {}
		
		osc::OutboundPacketStream& stream()				{ return fOutStream; }
		int					getPort () const			{ return fPort; }
		unsigned long		getAddress () const			{ return fAddress; }
		UdpSocket*			socket()					{ return fSocket; }
		int					state()	const				{ return fState; }
		
		virtual OSCStream&			start(const char * address);
		virtual OSCStream&			end();

		void setPort (int port)							{ fPort = port; }
		void setAddress (unsigned long address)			{ fAddress = address; }
		void setAddress (const std::string& address);
};

						OSCStream& operator <<(OSCStream& s, OSCEnd val);
						OSCStream& operator <<(OSCStream& s, const OSCStart& val);
						OSCStream& operator <<(OSCStream& s, const OSCErr& val);
						OSCStream& operator <<(OSCStream& s, const OSCWarn& val);
						OSCStream& operator <<(OSCStream& s, const char* val);
						OSCStream& operator <<(OSCStream& s, const std::string& val);
						OSCStream& operator <<(OSCStream& s, IExpression* val);
                        OSCStream& operator <<(OSCStream& s, IExprOperator* val);
				inline	OSCStream& operator <<(OSCStream& s, int val)		{ s.stream() << val; return s; }
				inline	OSCStream& operator <<(OSCStream& s, long val)		{ s.stream() << (int)val; return s; }
				inline	OSCStream& operator <<(OSCStream& s, float val)		{ s.stream() << val; return s; }
				inline	OSCStream& operator <<(OSCStream& s, double val)	{ s.stream() << float(val); return s; }

template <typename T> 	OSCStream& operator <<(OSCStream& s, const TSize<T>& size)	{ s << size.width() << size.height(); return s; }

						OSCStream& operator <<(OSCStream& s, const IMessage* msg);
						OSCStream& operator <<(OSCStream& s, const IMessageList* msg);
						OSCStream& operator <<(OSCStream& s, const IColor& color);

template <typename T>	OSCStream& operator <<(OSCStream& s, const std::vector<T>& val)
						{ 
							for (unsigned int i =0; i < val.size(); i++) s << val[i];
							return s; 
						}

class IApplLog;
//--------------------------------------------------------------------------
/*!
\brief	OSC error stream
*/
class OSCErrorStream : public OSCStream
{
	std::stringstream	fSStream;
	std::string			fAddress;
	IApplLog*			fLogWindow;
	// Streamstring to concat error. Introduced for scripts posted from the web.
	std::stringstream	fSStreamConcat;
	bool fConcat;

	public:
				 OSCErrorStream(UdpSocket* socket) : OSCStream(socket), fLogWindow(0), fConcat(false) {}
		virtual ~OSCErrorStream() {}
		
		void	setLogWindow (IApplLog* w)						{ fLogWindow = w; }
		std::stringstream& stream()								{ return fSStream; }
		virtual OSCErrorStream&		start(const char * address) { fSStream.str(""); fAddress = address; OSCStream::start(address); return *this; }
		virtual OSCErrorStream&		end();
		/*!
		 * \brief activeConcatError concat all error in a streamstring while it is reactivated.
		 * \param activate if true reset the error streamstring and active concat error.
		 * If false new errors are not added.
		 */
		void activeConcatError(bool activate);

		/*!
		 * \brief streamConcat get the concat streamstring
		 * \return
		 */
		std::stringstream& streamConcat();
};


						OSCErrorStream& operator <<(OSCErrorStream& s, OSCEnd val);
						OSCErrorStream& operator <<(OSCErrorStream& s, const OSCStart& val);
						OSCErrorStream& operator <<(OSCErrorStream& s, const OSCErr& val);
						OSCErrorStream& operator <<(OSCErrorStream& s, const OSCWarn& val);
						OSCErrorStream& operator <<(OSCErrorStream& s, const char* val);
						OSCErrorStream& operator <<(OSCErrorStream& s, const std::string& val);
						OSCErrorStream& operator <<(OSCErrorStream& s, IExpression* val);
				inline	OSCErrorStream& operator <<(OSCErrorStream& s, int val)			{ s.stream() << " " << val; return s; }
				inline	OSCErrorStream& operator <<(OSCErrorStream& s, long val)		{ s.stream() << " " << (int)val; return s; }
				inline	OSCErrorStream& operator <<(OSCErrorStream& s, float val)		{ s.stream() << " " << val; return s; }
				inline	OSCErrorStream& operator <<(OSCErrorStream& s, double val)		{ s.stream() << float(val); return s; }

template <typename T> 	OSCErrorStream& operator <<(OSCErrorStream& s, const TSize<T>& size)	{ s << size.width() << size.height(); return s; }

						OSCErrorStream& operator <<(OSCErrorStream& s, const IMessage* msg);
						OSCErrorStream& operator <<(OSCErrorStream& s, const IMessageList* msg);
						OSCErrorStream& operator <<(OSCErrorStream& s, const IColor& color);

template <typename T>	OSCErrorStream& operator <<(OSCErrorStream& s, const std::vector<T>& val)
						{ 
							for (unsigned int i =0; i < val.size(); i++) s << val[i];
							return s; 
						}



extern OSCStream*		_oscout;		// OSC standard output stream
extern OSCErrorStream*	_oscerr;		// OSC standard input stream
extern OSCStream		gEventsStream;

#define oscout (*_oscout)
#define oscerr (*_oscerr)

} // end namespace

#endif
