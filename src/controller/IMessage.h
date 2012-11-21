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


#ifndef __IMessage__
#define __IMessage__

#include <string>
#include <vector>
#include <iostream>
#include "message.h"
#include "ITLError.h"
#include "OSCStream.h"
#include "rational.h"
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
};

inline std::ostream& operator << (std::ostream& os, const baseparam* p) { 
	if (p->isType<int>())				os << p->value(0);
	else if (p->isType<float>())		os << p->value(0.);
	else if (p->isType<std::string>())	os << p->value("");
	else os << "unknown parameter type";
	return os; 
}

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
		
		virtual libmapping::SMARTP<baseparam> copy() const { return new IMsgParam<T>(fParam); }
};

class IMessageList;
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
		typedef libmapping::SMARTP<baseparam>		argPtr;		///< a message argument ptr type
		class argslist : public std::vector<argPtr> {
			public:
				void push_back( const argslist& l) {
					for (const_iterator i = l.begin(); i != l.end(); i++) std::vector<argPtr>::push_back(*i);
				}
				void push_back( const argslist* l) {
					for (const_iterator i = l->begin(); i != l->end(); i++) std::vector<argPtr>::push_back(*i);
				}
				void push_back( const argPtr& arg) {
					std::vector<argPtr>::push_back(arg);
				}
		};
		class TUrl {
			public:
				std::string	fHostname;
				int			fPort;
							TUrl () : fPort(0) {}
							TUrl (const char* host, int port) : fHostname(host), fPort(port) {}
		};
//		typedef std::vector<argPtr>		argslist;	///< args list type

	private:
		unsigned long	fSrcIP;			///< the message source IP number
		std::string	fAddress;			///< the message osc destination address
//		std::string	fMessage;			///< the message 'message'
		argslist	fArguments;			///< the message arguments, index 0 is reserved for the message string
		bool		fHasMessage;		///< indicates when arguments start with a message string
		TUrl		fUrl;
		
		inline int index (int i) const	{ return fHasMessage ? i+1 : i; }
	
	public:
			/*!
				\brief an empty message constructor
			*/
			 IMessage() : fHasMessage(false)  {}
			/*!
				\brief a message constructor
				\param address the message destination address
			*/
			 IMessage(const std::string& address) : fAddress(address), fHasMessage(false) {}
			/*!
				\brief a message constructor
				\param address the message destination address
				\param msg the message message
			*/
			 IMessage(const std::string& address, const std::string& msg) : fAddress(address) { setMessage(msg); } //, fMessage(msg) {}
			/*!
				\brief a message constructor
				\param address the message destination address
				\param msg the message message
				\param args the message parameters
			*/
			 IMessage(const std::string& address, const std::string& msg, const argslist& args) 
				: fAddress(address)  /*, fMessage(msg), fArguments(args)*/ { setMessage(msg); add(args); }
			/*!
				\brief a message constructor
				\param address the message destination address
				\param args the message parameters, param 0 is scanned to set the message bool attribute
			*/
			 IMessage(const std::string& address, const argslist& args, const TUrl& url);
			/*!
				\brief a message constructor
				\param msg a message
			*/
//			 IMessage(const IMessage& msg);
	virtual ~IMessage() {}


	/*!
		\brief adds a parameter to the message
		\param val the parameter
	*/
	template <typename T> void add(T val)	{ fArguments.push_back(new IMsgParam<T>(val)); }
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
	void	add( IMessageList* val )		{ fArguments.push_back( new IMsgParam<IMessageList*>(val) ); }
	
	/*!
		\brief adds a set of parameter to the message
		\param params the parameters
	*/
	void	add( const argslist& params );

	/*!
		\brief sets the message address
		\param addr the address
	*/
	void				setSrcIP(unsigned long addr)		{ fSrcIP = addr; }

	/*!
		\brief sets the message address
		\param addr the address
	*/
	void				setAddress(const std::string& addr)		{ fAddress = addr; }
	/*!
		\brief sets the message string
		\param msg the message string
	*/
	void				setMessage(const std::string& msg);
	/*!
		\brief print the message
		\param out the output stream
	*/
	void				print(std::ostream& out) const;

#ifndef NO_OSCSTREAM
	/*!
		\brief send the message to OSC
		\param out the OSC output stream
	*/
	template <typename T> void	print(T& out) const {
														out << OSCStart(address().c_str());
														if (message().size()) out << message();
														printArgs(out);
														out << OSCEnd();
													}
	
	/*!
		\brief print message arguments
		\param out the OSC output stream
	*/
	template <typename T> void printArgs(T& out) const {
														for (int i=0; i < size(); i++) {
															std::string str; float fv; int iv;
															if (param(i, fv))			out << fv;
															else if (param(i, iv))		out << iv;
															else if (param(i, str))		out << str;
															else ITLErr << "IMessage::print: unknown message parameter type" << ITLEndl;
														}
													}
#endif

	/// \brief gives the message address
	const std::string&	address() const		{ return fAddress; }
	/// \brief check for extended address
	bool		extendedAddress() const		{ return fUrl.fPort != 0; }
	/// \brief gives the address extension
	const TUrl&	url() const					{ return fUrl; }
	/// \brief gives the message message
	std::string			message() const;
	/// \brief gives a single parameter by index
	const argPtr&		param(unsigned int i) const		{ return fArguments[index(i)]; }
	/// \brief sets parameter value
	template <typename T> void setparam(unsigned int i, T val)  { fArguments[index(i)] = new IMsgParam<T>(val); }
	/// \brief gives the message source IP
	unsigned long		src() const			{ return fSrcIP; }
	/// \brief gives the message parameters count
	int					size() const		{ int  n = fArguments.size(); return fHasMessage ? n -1 : n; }
	
	bool operator == (const IMessage& other) const;	


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
	bool	param(int i, IMessageList*& val) const { val = param(i)->value<IMessageList*>(val); return param(i)->isType<IMessageList*>(); }
};

typedef libmapping::SMARTP<IMessage>	SIMessage;

//--------------------------------------------------------------------------
/*!
	\brief a messages list utility
	
	Note that IMessageList doesn't delete it's messages unless the \c clear method is called.
*/
class IMessageList : public std::vector<IMessage *>, public libmapping::smartable
{
	public:
				 IMessageList() {}
		virtual ~IMessageList() {}

		void  clear();			///< delete the enclosed messages
		void  operator += (const IMessageList&);	
		void  operator += (IMessage* msg)					{ push_back(msg); }
};

/*!
@}
*/

} // end namespoace

#endif
