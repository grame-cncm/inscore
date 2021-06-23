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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#ifndef __INScore__
#define __INScore__

#include <string>

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

//--------------------------------------------------------------------------
class INScoreApplicationGlue
{
	public :
		virtual void 	showMouse (bool state) = 0;
		virtual bool 	openUrl (const std::string& url) = 0;
		virtual void	startView () = 0;
		virtual void	stopView  () = 0;

		virtual std::string viewVersion() const = 0;
		virtual std::string getIP() const = 0;
};

//--------------------------------------------------------------------------
class INScoreGlue
{
	public :
		virtual ~INScoreGlue() {}

		virtual int 	getRate() const = 0;
		virtual void 	timeTask () = 0;
		virtual void 	sorterTask() = 0;
};

//--------------------------------------------------------------------------
/*! \brief the main library API
*/
class inscore_export INScore
{
	public:
	typedef void *	MessagePtr;		///< an opaque pointer to a message

	/*! \brief Qt environment initialization + INScore glue setup

		\param udpport the udp port number to listen for incoming OSC messages
		\param outport the udp port number for outgoing OSC messages
		\param errport the udp port number for error messages
		\param offscreen a boolean value to select between onscreen and offscreen graphic rendering.
		       When offscreen is selected, the graphic rendering is in charge of the client application,
			   which should set a listener to be notified of the graphic score changes, 
			   which should also use the getGraphicScore method to get the score bitmap.
		\see GraphicUpdateListener
			   
	*/
	static INScoreGlue* start (int udpport, int outport, int errport, INScoreApplicationGlue* ag, bool offscreen=false);

	/*! \brief stops the INScore services

		\param glue the value returned by the last start call
	*/
	static void stop (INScoreGlue* glue);

    /*!
     * \brief restartNetwork Restart network services after a stop.
     */
    static void restartNetwork();

    /*!
     * \brief stopNetwork Stop network services of inscore.
     */
    static void stopNetwork();
	
	/*! \brief load an inscore script
		\param script the text of the script
		\param autoparse a boolean to activate the current parse version (set with the 'parse' message)
	*/
	static bool loadInscore	(const char* script, bool autoparse=false);

	/*! \brief load an inscore script version 2
		\param script the text of the script
	*/
	static bool loadInscore2 (const char* script);

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
	
	
	static float version()					{ return 1.29f; }	///< gives the library version number
	static std::string versionStr()			{ return "1.29"; }	///< gives the library version number as a string

	static std::string guidoversion();						///< gives the guido library version number as a string
	static std::string musicxmlversion();					///< gives the musicxml library version number as a string
	static std::string faustversion();						///< gives the faust library version number as a string

};

/*! @} */


}

#endif
