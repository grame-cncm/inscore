/*

  Interlude Library
  Copyright (C) 2009  Grame

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

#ifndef __message__
#define __message__

#include <ostream>
#include <string>
#include "export.h"

namespace interlude 
{

/*!
\addtogroup interface Library API
@{
*/

/*! \brief the messages public API
*/
class export Message
{
	public:

	/*!
		\brief adds a float parameter to the message
		\param val the parameter value
	*/
	virtual void	add(float val) = 0;
	/*!
		\brief adds an int parameter to the message
		\param val the parameter value
	*/
	virtual void	add(int val) = 0;
	/*!
		\brief adds a string parameter to the message
		\param val the parameter value
	*/
	virtual void	add(const std::string& val) = 0;

	/*!
		\brief sets the message address
		\param addr the address
	*/
	virtual void	setAddress(const std::string& addr)	= 0;
	/*!
		\brief sets the message string
		\param msg the message string
	*/
	virtual void	setMessage(const std::string& msg) = 0;
	/*!
		\brief print the message
		\param out the output stream
	*/
	virtual void	print(std::ostream& out) const = 0;


	/// \brief gives the message address
	virtual const std::string&	address() const	= 0;
	/// \brief gives the message message
	virtual const std::string&	message() const	= 0;
	
	/// \brief gives the message parameters count
	virtual int					size() const = 0;
	/*!
		\brief gives a message float parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when type doesn't matches
	*/
	virtual bool	param(int i, float& val) const = 0;
	/*!
		\brief gives a message int parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when type doesn't matches
	*/
	virtual bool	param(int i, int& val) const = 0;
	/*!
		\brief gives a message int parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when type doesn't matches
	*/
	virtual bool	param(int i, bool& val) const = 0;
	/*!
		\brief gives a message string parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when type doesn't matches
	*/
	virtual bool	param(int i, std::string& val) const = 0;
	
	protected:
		virtual ~Message() {}
	
};

/*! @} */


}

#endif
