/*

  INScore Library
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

#ifndef __INScore__
#define __INScore__

#include "export.h"


namespace inscore 
{

/*!
\addtogroup interface Library API
@{
*/

//--------------------------------------------------------------------------
class GraphicUpdateListener
{
	public :
		virtual void update() = 0;
};

class IGlue;
/*! \brief the main library API
*/
class export INScore 
{
	public:
	typedef void *	MessagePtr;		///< an opaque pointer to a message

	/*! \brief Qt environment initiaization + INScore glue setup

		\param address the OSC destination address of the message
		\param params the message parameters
		\warning once a message has been posted, it is owned by the library and must not be deleted
		by the client application
	*/
	static IGlue* init (int timeInterval=10, int udpport=7000);

	/*! \brief sets a listener for the graphic update

		\param glue the system glue as returned by init()
		\param listener a listener that will be called after the scene graphic update
	*/
	static void setListener (const IGlue* glue, GraphicUpdateListener* listener);

	/*! \brief copy the scene data into a bitmap

		\param glue the system glue as returned by init()
		\param bitmap the destination bitmap
		\param w the bitmap width
		\param h the bitmap height
	*/
	static bool getScene (const IGlue* glue, unsigned int* bitmap, int w, int h);

	/*! \brief post a message

		\param address the OSC destination address of the message
		\param params the message parameters
		\warning once a message has been posted, it is owned by the library and must not be deleted
		by the client application
	*/
	static void postMessage	(const char* address, MessagePtr msg);

	/*! \brief create a new message
		\param msg the message string
		\return an opaque pointer to a message
	*/
	static MessagePtr newMessage (const char* msg);

	/*! \brief create an empty new message
		\return an opaque pointer to a message
	*/
	static MessagePtr newMessage ();
	
	/*! \brief delete a message

		\warning do not delete a message that has been posted with \c postMessage
	*/
	static void delMessage(MessagePtr msg);

	/*! \brief adds a string parameter to a message.
		\param msg the message
		\param s a pointer to the string
	*/
	static void add (MessagePtr msg, const char* s);

	/*! \brief adds a \c flot parameter to a message.
		\param msg the message
		\param f a float parameter
	*/
	static void add (MessagePtr msg, float f);

	/*! \brief adds an \c int parameter to a message.
		\param msg the message
		\param n an int parameter
	*/
	static void add (MessagePtr msg, int n);
	
	
	static int version();					///< gives the library version number
	static const char* versionStr();		///< gives the library version number as a string
};

/*! @} */


}

#endif
