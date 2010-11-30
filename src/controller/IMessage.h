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
#include "rational.h"
#include "smartpointer.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

class OSCStream;
template <typename T> class IMsgParam;
class baseparam;
typedef SMARTP<baseparam>	Sbaseparam;

//--------------------------------------------------------------------------
/*!
	\brief base class of a message parameters
*/
class baseparam : public smartable
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
			
		virtual SMARTP<baseparam> copy() const = 0;
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
		
		virtual SMARTP<baseparam> copy() const { return new IMsgParam<T>(fParam); }
};

//--------------------------------------------------------------------------
/*!
	\brief a message description
	
	A message is composed of an address (actually an OSC address),
	a message string that may be viewed as a method name
	and a list of message parameters.
*/
class IMessage : public Message
{
//static unsigned long allocated;
//static unsigned long freed;
	public:
		typedef SMARTP<baseparam>		argPtr;		///< a message argument ptr type
		typedef std::vector<argPtr>		argslist;	///< args list type

	private:
		unsigned long	fSrcIP;			///< the message source IP number
		std::string	fAddress;			///< the message osc destination address
		std::string	fMessage;			///< the message 'message'
		argslist	fArguments;			///< the message arguments
	
	public:
			/*!
				\brief an empty message constructor
			*/
			 IMessage() {}
			/*!
				\brief a message constructor
				\param address the message destination address
			*/
			 IMessage(const std::string& address) : fAddress(address) {}
			/*!
				\brief a message constructor
				\param address the message destination address
				\param msg the message message
			*/
			 IMessage(const std::string& address, const std::string& msg) : fAddress(address), fMessage(msg) {}
			/*!
				\brief a message constructor
				\param address the message destination address
				\param msg the message message
				\param args the message parameters
			*/
			 IMessage(const std::string& address, const std::string& msg, const argslist& args) 
				: fAddress(address), fMessage(msg), fArguments(args) {}
			/*!
				\brief a message constructor
				\param msg a message
			*/
			 IMessage(const IMessage& msg);
	virtual ~IMessage() {} //{ freed++; std::cout << "running messages: " << (allocated - freed) << std::endl; }

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
		\brief adds a parameter to the message
		\param val the parameter
	*/
	void	add( argPtr val )				{ fArguments.push_back( val ); }

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
	void				setMessage(const std::string& msg)		{ fMessage = msg; }
	/*!
		\brief print the message
		\param out the output stream
	*/
	void				print(std::ostream& out) const;
	/*!
		\brief send the message to OSC
		\param out the OSC output stream
	*/
	void				print(OSCStream& out) const;
	/*!
		\brief print message arguments
		\param out the OSC output stream
	*/
	void				printArgs(OSCStream& out) const;

	/// \brief gives the message address
	const std::string&	address() const		{ return fAddress; }
	/// \brief gives the message message
	const std::string&	message() const		{ return fMessage; }
	/// \brief gives the message parameters list
	const argslist&		params() const		{ return fArguments; }
	/// \brief gives the message parameters list
	argslist&			params()			{ return fArguments; }
	/// \brief gives the message source IP 
	unsigned long		src() const			{ return fSrcIP; }
	/// \brief gives the message parameters count
	int					size() const		{ return fArguments.size(); }
	
	bool operator == (const IMessage& other) const;	


	/*!
		\brief gives a message float parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, float& val) const		{ val = params()[i]->value<float>(val); return params()[i]->isType<float>(); }
	/*!
		\brief gives a message int parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, int& val) const		{ val = params()[i]->value<int>(val); return params()[i]->isType<int>(); }
	/*!
		\brief gives a message int parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
		\note a boolean value is handled as integer
	*/
	bool	param(int i, bool& val) const		{ int ival = 0; ival = params()[i]->value<int>(ival); val = ival!=0; return params()[i]->isType<int>(); }
	/*!
		\brief gives a message int parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, long int& val) const	{ val = long(params()[i]->value<int>(val)); return params()[i]->isType<int>(); }
	/*!
		\brief gives a message string parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, std::string& val) const { val = params()[i]->value<std::string>(val); return params()[i]->isType<std::string>(); }
	/*!
		\brief gives a message rational parameters
		\param i the parameters start index (0 <= i < size()-1)
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	bool	param(int i, rational& val) const;
};

//--------------------------------------------------------------------------
/*!
	\brief a messages list utility
*/
class IMessageList : public std::vector<IMessage *>
{
	public:
				 IMessageList() {}
		virtual ~IMessageList() {}

		void  clear();
		void  operator += (const IMessageList&);	
		void  operator += (IMessage* msg)					{ push_back(msg); }
};

/*!
@}
*/

} // end namespoace

#endif
