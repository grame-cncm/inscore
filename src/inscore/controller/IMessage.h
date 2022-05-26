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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/


#ifndef __IMessage__
#define __IMessage__

#include <string>
#include <vector>
#include <ostream>

#include "Modules.h"
#include "message.h"
#include "ITLError.h"
#if HASOSCStream
#include "OSCStream.h"
#endif
#include "rational.h"
#include "extvector.h"
#include "smartpointer.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

template <typename T> class IMsgParam;
class baseparam;
typedef libmapping::SMARTP<baseparam>	Sbaseparam;
class IExpression;
typedef libmapping::SMARTP<IExpression>	SIExpression;

//--------------------------------------------------------------------------
/*!
	\brief base class of a message parameters
*/
class baseparam : public libmapping::smartable
{
	public:
		virtual ~baseparam() {}

		/*!
		 \brief utility for parameter type checking
		*/
		template<typename X> bool isType() const { return dynamic_cast<const IMsgParam<X>*> (this) != 0; }
		/*!
		 \brief utility for parameter convertion
		 \param errvalue the returned value when no conversion applies
		 \return the parameter value when the type matches
		*/
		template<typename X> X	value(X errvalue) const 
			{ const IMsgParam<X>* o = dynamic_cast<const IMsgParam<X>*> (this); return o ? o->getValue() : errvalue; }
		/*!
		 \brief utility for parameter comparison
		*/
		template<typename X> bool	equal(const baseparam& p) const 
			{ 
				const IMsgParam<X>* a = dynamic_cast<const IMsgParam<X>*> (this); 
				const IMsgParam<X>* b = dynamic_cast<const IMsgParam<X>*> (&p);
				return a && b && (a->getValue() == b->getValue());
			}
		/*!
		 \brief utility for parameter comparison
		*/
		bool operator==(const baseparam& p) const 
			{ 
				return equal<float>(p) || equal<int>(p) || equal<std::string>(p);
			}
		bool operator!=(const baseparam& p) const
			{ 
				return !equal<float>(p) && !equal<int>(p) && !equal<std::string>(p);
			}
			
		virtual libmapping::SMARTP<baseparam> copy() const = 0;

#if HASOSCStream
		virtual void print(ITLError ) const {}
#endif
		virtual void print(std::ostream& ) const {}
};


//--------------------------------------------------------------------------
/*!
	\brief template for a message parameter
*/
template <typename T> class IMsgParam : public baseparam
{
	T fParam;
	public:
				 IMsgParam(T val) : fParam(val)	{}
		virtual ~IMsgParam() {}
		
		T	getValue() const { return fParam; }
		
		virtual libmapping::SMARTP<baseparam> copy() const	{ return new IMsgParam<T>(fParam); }
#if HASOSCStream
		virtual void print(ITLError out) const				{ out << fParam; }
#endif
		virtual void print(std::ostream& out) const			{
			if (isType<std::string>())	out << value<std::string>("");
			else if (isType<int>())		out << value<int>(0);
			else if (isType<float>())	out << value<float>(0.f);
			else out << "";
		}
};


class OSCStream;
class IMessage;
typedef libmapping::SMARTP<IMessage>		SIMessage;
class IMessageList;
typedef libmapping::SMARTP<IMessageList>	SIMessageList;


/// a javascript type definition to handle javascript as message argument
class TJavaScript : public std::string	{
	public:
				 TJavaScript(const char* v) : std::string(v) {}
				 TJavaScript() {}
		virtual ~TJavaScript() {}
};

//--------------------------------------------------------------------------
/*!
	\brief a message description
	
	A message is composed of an address (actually an OSC address),
	a message string that may be viewed as a method name
	and a list of message parameters.
*/
class IMessage : public Message, public libmapping::smartable
{
	public:
		typedef libmapping::SMARTP<baseparam>	argPtr;		///< a message argument ptr type
		typedef extvector<argPtr>				argslist;	///< type for arguments list
		class TUrl {
			public:
				enum { kOSCProtocol, kWSProtocol, kHTTPProtocol, kHTTPSProtocol };
				std::string	fHostname;
				int			fPort;
				int			fProtocol = kOSCProtocol;

						 TUrl () : fPort(0) {}
						 TUrl (const char* host, int port) : fHostname(host), fPort(port) {}
				virtual ~TUrl() {}

				/// \brief parse the string to separate host name and port number
				bool parse(const std::string& host);
				operator std::string() const;
				bool operator ==(const TUrl& other) const	{ return (fPort == other.fPort) && (fHostname == other.fHostname); }
				bool operator !=(const TUrl& other) const	{ return (fPort != other.fPort) || (fHostname != other.fHostname); }
		};

	private:
		enum { kLocalHost = 0x7F000001 };

		unsigned long	fSrcIP;			///< the message source IP number
		std::string	fAddress;			///< the message osc destination address
		argslist	fArguments;			///< the message arguments, index 0 is reserved for the message string
		bool		fHasMessage;		///< indicates when arguments start with a message string
		TUrl		fUrl;
		float		fDelay = 0.f;

		inline int index (int i) const	{ return fHasMessage ? i+1 : i; }
		/*!
			\brief adds a parameter to the message
			\param val the parameter
		*/
		template <typename T> void add(T val)	{ fArguments.push_back(new IMsgParam<T>(val)); }
	
	protected:
			/*!
				\brief an empty message constructor
			*/
			 IMessage() : fSrcIP(kLocalHost), fHasMessage(false)  {}
			/*!
				\brief a clone constructor
			*/
			 IMessage(const IMessage& msg);
			/*!
				\brief a message constructor with an osc address
				\param address the message destination address
			*/
			 IMessage(const std::string& address) : fSrcIP(kLocalHost), fAddress(address), fHasMessage(false) {}
			/*!
				\brief a message constructor with an osc address and a message string
				\param address the message destination address
				\param msg the message message
			*/
			 IMessage(const std::string& address, const std::string& msg);
			/*!
				\brief a message constructor with arguments and address extension
				\param address the message destination address
				\param args the message parameters, param 0 is scanned to set the message bool attribute
				\param url the osc address extension. Empty url discards the extension
			*/
			 IMessage(const std::string& address, const argslist& args, const TUrl& url);
	virtual ~IMessage() {}

	
	public:
		static SIMessage create()													{ return new IMessage(); }
		static SIMessage create(const IMessage& msg)								{ return new IMessage(msg); }
		static SIMessage create(const std::string& address)							{ return new IMessage(address); }
		static SIMessage create(const std::string& address, const std::string& msg)	{ return new IMessage(address, msg); }
		static SIMessage create(const std::string& address, const argslist& args, const TUrl& url)
				{ return new IMessage(address, args, url); }

	//------------------------------------------------------------------------------
	// methods to add parameters
	//------------------------------------------------------------------------------
	/*!
		\brief adds a float parameter to the message
		\param val the parameter value
	*/
	void	add(float val)					{ add<float>(val); }
	/*!
		\brief adds an int parameter to the message
		\param val the parameter value
	*/
	void	add(int val)					{ add<int>(val); }
	/*!
		\brief adds a string parameter to the message
		\param val the parameter value
	*/
	void	add(const std::string& val)		{ add<std::string>(val); }
	/*!
		\brief adds a string parameter to the message
		\param val the parameter value
	*/
	void	add(const char* val)			{ add<std::string>(val); }
	
	/*!
		\brief adds a parameter to the message
		\param val the parameter
	*/
	void	add( argPtr val )				{ fArguments.push_back( val ); }
	
	/*!
		\brief adds a parameter to the message
		\param val the parameter
	*/
	void	add(const SIMessageList& val )	{ fArguments.push_back( new IMsgParam<SIMessageList>(val) ); }
	
	/*!
		\brief adds a parameter to the message
		\param val the parameter
	*/
	void	add(const TJavaScript& val )	{ fArguments.push_back( new IMsgParam<TJavaScript>(val) ); }
	
	/*!
		\brief adds a set of parameter to the message
		\param params the parameters
	*/
	void	add( const argslist& params );

	//------------------------------------------------------------------------------
	// methods for address management
	//------------------------------------------------------------------------------
	/*!
		\brief sets the message address
		\param addr the address
	*/
	void				setSrcIP(unsigned long addr)		{ fSrcIP = addr; }

	/*!
		\brief sets the message address
		\param addr the address
	*/
	void				setAddress(const std::string& addr)	{ fAddress = addr; }

	/*!
		\brief converts a message address to absolute address
		\param prefix the address prefix
	*/
	std::string			relative2absoluteAddress(const std::string& prefix) const;

	/*!
		\brief sets the message url
		\param url the address extension
	*/
	void				setUrl(const TUrl& url)				{ fUrl = url; }
	/*!
		\brief sets the message string
		\param msg the message string
	*/

	//------------------------------------------------------------------------------
	// misc.
	//------------------------------------------------------------------------------
	/*!
		\brief sets the message string
		\param msg the message string
	*/
	void				setMessage(const std::string& msg);

	/*!
		\brief sets the message delay
		\param delay the message delay
	*/
	void				setDelay(float delay)	{ fDelay = delay; }

	/*!
		\brief print the message
		\param out the output stream
		\param suffix the suffix to be used as messages separator
	*/
	void		print(std::ostream& out, int nested=0, const char* suffix=0) const;
	/*!
		\brief print a message parameter
		\param out the output stream
		\param param the param index
		\param nested a flag used for indentation
		\param suffix the suffix to be used as messages separator
	*/
	void		print(std::ostream& out, int param, int nested, const char* suffix=0) const;

	/*!
		\brief convert a message to string
	*/
	std::string	toString() const;

#if HASOSCStream
	/*!
		\brief send the message to OSC
		\param out the OSC output stream
		\param start a boolean to indicate wether the stream needs to be started (OSC specific)
	*/
	void	print(OSCStream& out) const;
	void	print(OSCErrorStream& out) const;

	/*!
		\brief linearize a message to OSC
		\param out the OSC output stream
	*/
	void	linearize(OSCStream& out) const;
	
	/*!
		\brief print message arguments
		\param out the OSC output stream
	*/
	void printArgs(OSCStream& out) const;
#endif

	//------------------------------------------------------------------------------
	// methods to query a message
	//------------------------------------------------------------------------------
	/// \brief gives the message address
	const std::string&	address() const				{ return fAddress; }
	/// \brief check for relative address
	bool				relativeAddress() const		{ return fAddress[0] == '.'; }
	/// \brief check for extended address
	bool				extendedAddress() const		{ return fUrl.fPort != 0; }
	/// \brief gives the address extension
	const TUrl&	url() const							{ return fUrl; }
	/// \brief gives the message message
	std::string			message() const;
	/// \brief gives a single parameter by index
	const argPtr&		param(unsigned int i) const				{ return fArguments[index(i)]; }
	/// \brief sets parameter value
	template <typename T> void setparam(unsigned int i, T val)  { fArguments[index(i)] = new IMsgParam<T>(val); }
	/// \brief gives the message source IP
	unsigned long		src() const				{ return fSrcIP; }
	/// \brief gives the message parameters count
	int					size() const			{ int  n = int(fArguments.size()); return fHasMessage ? n -1 : n; }
	/// \brief gives the message delay
	float				delay() const			{ return fDelay; }

	bool operator == (const IMessage& other) const;	


	//------------------------------------------------------------------------------
	// getting parameters values and types
	/*!
		\brief gives a message value as float value and operates int to float cast if necessary
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when type is not a numreric type
	*/
	bool	cast_param(int i, float& val) const;
	/*!
		\brief gives a message value as int value and operates float to int cast if necessary
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when type is not a numreric type
	*/
	bool	cast_param(int i, int& val) const;

	/*!
		\brief gives a message float parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, float& val) const		{ val = param(i)->value<float>(val); return param(i)->isType<float>(); }
	/*!
		\brief gives a message int parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, int& val) const		{ val = param(i)->value<int>(val); return param(i)->isType<int>(); }
	/*!
		\brief gives a message int parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
		\note a boolean value is handled as integer
	*/
	bool	param(int i, bool& val) const		{ int ival = 0; ival = param(i)->value<int>(ival); val = ival!=0; return param(i)->isType<int>(); }
	/*!
		\brief gives a message int parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, long int& val) const	{ val = long(param(i)->value<int>(val)); return param(i)->isType<int>(); }
	/*!
		\brief gives a message string parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, std::string& val) const { val = param(i)->value<std::string>(val); return param(i)->isType<std::string>(); }
	/*!
		\brief gives a message rational parameters
		\param i the parameters start index (0 <= i < size()-1)
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, libmapping::rational& val) const;
	/*!
		\brief gives a message messages parameters
		\param i the parameters start index (0 <= i < size()-1)
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, SIMessageList& val) const { val = param(i)->value<SIMessageList>(val); return param(i)->isType<SIMessageList>(); }
	/*!
		\brief gives a message messages parameters
		\param i the parameters start index (0 <= i < size()-1)
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, TJavaScript& val) const { val = param(i)->value<TJavaScript>(val); return param(i)->isType<TJavaScript>(); }
    /*!
        \brief gives a message messages parameters
        \param i the parameters start index (0 <= i < size()-1)
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
	bool	param(int i, SIExpression& val) const;


	// ----------------------- utilities ----------------------
private:
	/*!
		\brief extract a 'watch' associated message from a 'watch' message
		\param index the enclosed message start index, updated to the next message index
		\return a message or 0 when the conversion fails
	*/
	SIMessage		watchMsg2Msg(int& index) const;

	/*!
		\brief extract 'watch' associated messages from a 'watch' message
		\param startIndex the enclosed messages start index
		\return a list of messages
		
		Internal implementation of watchMsg2Msgs. 
	*/
	SIMessageList	_watchMsg2Msgs(int& startIndex) const;

public:
	/*!
		\brief extract 'watch' associated messages from a 'watch' message
		\param startIndex the enclosed messages start index
		\return a list of messages
		
		Building a correct 'watch' message is in charge of the parser for inscore scripts.
		This method is provided for watch messages received over OSC. It parses the message 
		arguments from \c startIndex and builds a message list. 
		
		Note that when the OSC message includes several associated messages, they should be 
		separated by a colon or a comma (as part of the arguments). 
	*/
	SIMessageList	watchMsg2Msgs(int startIndex) const;

	/*!
		\brief sends a message
		
		The message is locally distributed (i.e. put on the message stack) when its address is not extended.
		Otherwise, the message is send over the network to the extended address destination.
	*/
	void	send (const bool &delay = false) const;

	/*!
		\brief transforms a 'watch' message with inline associated messages into a message with enclosed messages
		\param startIndex the inlined messages start index
		\return a message or 0 if the conversion fails
	*/
	SIMessage		buildWatchMsg(int startIndex) const;

	/*!
		\brief decode an extended address
		
		\param address the whole address as a string
		\param oscAddress on output, the osc address
		\param url on output, an optional url used for address extension
		\return true when the address is correctly decoded
	*/
	static bool decodeAddress (const std::string& address, std::string& oscAddress, IMessage::TUrl& url);
};

//--------------------------------------------------------------------------
/*!
	\brief a messages list utility	
*/
class IMessageList : public libmapping::smartable
{
	protected:
		extvector<SIMessage> fList;
		
				 IMessageList() {}
		virtual ~IMessageList() {}

	public:
		typedef extvector<SIMessage> TMessageList;

		static SIMessageList create()				{ return new IMessageList; }
		
		const	extvector<SIMessage>& list() const	{ return fList; }
				extvector<SIMessage>& list()		{ return fList; }
				
		/// \brief sends all the messages
		void	send (const bool &delay = false) const;

		/*!
		 * \brief sendWebMsg Add messages to a specific stack for message from web
		 */
		void 	sendWebMsg() const;
	
		/*!
			\brief print the message list
			\param out the output stream
		*/
		void	print(std::ostream& out) const;

};

inline std::ostream& operator << (std::ostream& os, const SIMessage& m)			{ if (m) m->print(os); else os << "null msg"; return os; }
inline std::ostream& operator << (std::ostream& os, const SIMessageList& l)		{ if (l) l->list().print(os); else os << "null msg list"; return os; }

/*!
@}
*/

} // end namespoace

#endif
