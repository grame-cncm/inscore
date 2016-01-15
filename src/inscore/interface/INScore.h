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


#if defined(WIN32) && defined(MSVC)

# ifdef INScore_EXPORTS
#  define inscore_export		 _declspec (dllexport)
# else
#  define inscore_export		 _declspec (dllimport)
# endif

# pragma warning ( disable : 4275 4251 )

#else

# ifdef INScore_EXPORTS
#  define inscore_export		 __attribute__ ((visibility("default")))
# else
#  define inscore_export		
# endif

#endif

class QApplication;
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
class inscore_export INScore
{
	public:
	typedef void *	MessagePtr;		///< an opaque pointer to a message

	/*! \brief Qt environment initialization + INScore glue setup

		\param timeInterval the time task tme interval (in mls). 0 means no time task
		\param udpport the udp port number to listen for incoming OSC messages
		\param outport the udp port number for outgoing OSC messages
		\param errport the udp port number for error messages
		\param offscreen a boolean value to select between onscreen and offscreen graphic rendering.
		       When offscreen is selected, the graphic rendering is in charge of the client application,
			   which should set a listener to be notified of the graphic score changes, 
			   which should also use the getGraphicScore method to get the score bitmap.
		\see GraphicUpdateListener
			   
	*/
	static IGlue* start (int timeInterval, int udpport, int outport, int errport, QApplication* appl, bool offscreen=false);

	/*! \brief stops the INScore services

		\param glue the value returned by the last start call
	*/
	static void stop (IGlue* glue);

    /*!
     * \brief restartNetwork Restart network services after a stop.
     */
    static void restartNetwork();

    /*!
     * \brief stopNetwork Stop network services of inscore.
     */
    static void stopNetwork();

//	/* \brief sets a listener for the graphic update
//
//		\param glue the system glue as returned by init()
//		\param listener a listener that will be called after the scene graphic update
//	*/
//	static void setListener (IGlue* glue, GraphicUpdateListener* listener);
//
//	/* \brief copy the graphic score data into a bitmap
//
//		\param glue the system glue as returned by init()
//		\param bitmap the destination bitmap
//		\param w the bitmap width
//		\param h the bitmap height
//	*/
//	static bool getGraphicScore (IGlue* glue, unsigned int* bitmap, int w, int h);
//
//	/* \brief copy the scene data into a bitmap
//
//		\param glue the system glue as returned by init()
//	*/
//	static void timeTask (IGlue* glue);

	/*! \brief post a message

		\param address the OSC destination address of the message
		\param msg the message to send
		\warning once a message has been posted, it is owned by the library and must not be deleted
		by the client application
	*/
	static void postMessage	(const char* address, MessagePtr msg);

	/*! \brief high level method to post a message

		\param address the OSC destination address of the message
		\param msg a message string
	*/
	static void postMessage	(const char* address, const char* msg);

	/*! \brief high level method to post a message

		\param address the OSC destination address of the message
		\param msg a message string
		\param int a value
	*/
	static void postMessage	(const char* address, const char* msg, int val);

	/*! \brief high level method to post a message

		\param address the OSC destination address of the message
		\param msg a message string
		\param int a value
	*/
	static void postMessage	(const char* address, const char* msg, float val);

	/*! \brief high level method to post a message

		\param address the OSC destination address of the message
		\param msg a message string
		\param int a value
	*/
	static void postMessage	(const char* address, const char* msg, const char* val);

	/*! \brief post a message for delayed processing i.e. its processing is delayed by one time task

		\param address the OSC destination address of the message
		\param msg the message to send
		\warning once a message has been posted, it is owned by the library and must not be deleted
		by the client application
	*/
	static void delayMessage	(const char* address, MessagePtr msg);

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
	
	
	static float version();					///< gives the library version number
	static const char* versionStr();		///< gives the library version number as a string

	static const char* guidoversion();		///< gives the guido library version number as a string
	static const char* musicxmlversion();	///< gives the musicxml library version number as a string
	static const char* qtversion();			///< gives the Qt library version number as a string
};

/*! @} */


}

#endif
