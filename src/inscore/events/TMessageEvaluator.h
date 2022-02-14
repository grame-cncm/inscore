/*

  INScore Project

  Copyright (C) 2009-2012  Grame

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


#ifndef __TMessageEvaluator__
#define __TMessageEvaluator__

#include <map>
#include <string>
#include <vector>

#include "IMessage.h"
#include "rational.h"
#include "smartpointer.h"
 
namespace inscore
{

class IObject;
typedef libmapping::SMARTP<IObject>			SIObject;

//----------------------------------------------------------------------
/**
* \brief current mouse location in various coordinate spaces
*/
typedef struct MouseLocation {
	float fx, fy, fz;		///< coordinates relative to the object, as in internal representation
	float fabsx, fabsy;		///< absolute coordinates relative to the object
	float fsx, fsy;			///< coordinates relative to the scene

	MouseLocation (float x, float y, float ax, float ay, float sx, float sy)
		: fx(x), fy(y), fz(0), fabsx(ax), fabsy(ay), fsx(sx), fsy(sy) {}
	MouseLocation (float x, float y, float z)
		: fx(x), fy(y), fz(z), fabsx(0), fabsy(0), fsx(0), fsy(0) {}
	MouseLocation ()
		: fx(0), fy(0), fz(0), fabsx(0), fabsy(0), fsx(0), fsy(0) {}
} MouseLocation;

//----------------------------------------------------------------------
/**
* \brief context of an objects at the time of an event
*/
typedef struct GestureContext {
	float likelihood, position, speed;
	bool isSet() const	{ return likelihood >= 0; }
	GestureContext () : likelihood(-1.f) , position(-1.f), speed(-1.f) {}
	GestureContext (float l, float p, float s) : likelihood(l) , position(p), speed(s) {}
} GestureContext;

typedef struct EventContext {
	MouseLocation			mouse;		///< the current mouse position
	libmapping::rational	date;		///< the object date at the mouse position
	const IObject*			object;		///< the object which context is attached to	
	GestureContext			gesture;
	void set (const GestureContext& g) { gesture = g; }

	EventContext (const MouseLocation& ml, const libmapping::rational& d, const IObject* o)
		: mouse(ml), date(d), object(o) {}
	EventContext (const libmapping::rational& d, const IObject* o)
		: date(d), object(o) {}
	EventContext (const IObject* o)
		: object(o) { date.set(0, 1); }

} EventContext;

//----------------------------------------------------------------------
class TMessageEvaluator
{
	private:
		static std::map<const char*, int>	fVarLength;		// variable length are stored statically

		/// \brief initializes static object parts
		void init();
		/// \brief evaluates variable parts of an address
		std::string evalAddress (const std::string& address, const IObject* obj) const;
		/// \brief check if a $date variable requests a float value
		bool		floatRequired (const char* param) const;
		Sbaseparam	evalRange (const std::string& range, float pos) const;
		Sbaseparam	evalPosition (const std::string& range, float pos) const;

		/// \brief check if a variable is a position variable
		bool		posVariable (const std::string& param, const char* var) const;
		/// \brief check if a variable is a argument variable ($1...$n)
		bool		argVariable (const char* var) const;
		/// \brief check if a variable is a gesture variable
		bool		gestVariable (const std::string& param, const char* var) const;
		/// \brief extract a variable from a string. The string should start with a '$'
		std::string	getVar (const char* ptr) const;

		/**
		*	\brief parses a date variable
			\param var		the date variable
			\param quant	on output, the required quantification or 0
			\param floatval on output, a boolean to indicate float values requests
			\param relative on output, a boolean to request a date relative to the object current time position
		*/
		void		parseDateVariable (const std::string& var, libmapping::rational& quant, bool& floatval) const;


		/**
		*	\brief evaluates a date variable
			\param var		the date variable
			\param env		the context of the event
			\param relative	a boolean to request a date relative to the object current time position
			\return a list or arguments to be used as parameters in place of the variable
		*/
		IMessage::argslist evalDate (const std::string& var, const EventContext& env, bool relative) const;

		/**
		*	\brief evaluates a message variable
			\param var the message string
			\param env the context of the event
			\return a list or arguments to be used as parameters in place of the variable
		*/
		IMessage::argslist evalMessage (const std::string& var, const EventContext& env) const;

		/**
		*	\brief evaluates a variable
			\param var the variable
			\param env the context of the event
			\return a list or arguments to be used as parameters in place of the variable
		*/
		IMessage::argslist evalVariable (const std::string& var, const EventContext& env, const IMessage::argslist& args) const;

		/**
		*	\brief evaluates a variable in user defined context
			\param var the variable
			\param env the context of the event
			\param args the arguments of the event
			\return a list or arguments to be used as parameters in place of the variable
		*/
		IMessage::argslist evalArgsVariable (const std::string& var, const EventContext& env, const IMessage::argslist& args) const;

		/**
		*	\brief evaluates a string that may contain a variable
			\param str the string
			\param env the context of the event
			\return a list or arguments to be used as parameters in place of the string
		*/
		IMessage::argslist evalVariableString (const std::string& str, const EventContext& env, const IMessage::argslist& args) const;

		/**
		*	\brief convert a location into a date
			\param obj		the object context
			\param x		the point x coordinate
			\param y		the point y coordinate
			\param mapname	the map to be used for conversion
			\param n		the repeat number to be retrieved (indexed from 0)
			\return a date
			
		*/
		libmapping::rational point2date (const IObject * obj, float x, float y, const std::string& mapname, int n) const;

	public:
				 TMessageEvaluator() { init(); }
		virtual ~TMessageEvaluator() {}

		/**
		*	\brief evaluates a user defined message
			\param msg the message to be evaluated
			\param env the event context (only the object ptr and the date are significant)
			\param args a list of arguments
			\return a list of evaluated message i.e. without variable part
		
			Evaluation of a user defined event consists in replacing the variable parameters with the values
			taken from the \c args list. Variables are expected to be name $1, $2 etc...
		*/
		SIMessageList	eval (const IMessageList *msg, const EventContext& env, const IMessage::argslist& args) const;

		/**
		*	\brief evaluates a mouse event
			\param msgs the messages to be evaluated
			\param env the event context
			\return a list of evaluated message i.e. without variable part
		
			Evaluation of a user defined event consists in replacing the variable parameters with the values
			taken from the \c args list. Variables are expected to be name $1, $2 etc...
		*/
		SIMessageList 	eval (const IMessageList* msgs, float x, float y, EventContext& env);

		/**
		*	\brief evaluates a single user defined message
			\param msg the message to be evaluated
			\param env the event context (only the object ptr and the date are significant)
			\param args a list of arguments
			\return an evaluated message i.e. without variable part
		
			Evaluation of a message consists in replacing the variable parameters with values
			evaluated in a given EventContext
		*/
		SIMessage		eval (const IMessage *msg, const EventContext& env, const IMessage::argslist& args) const;

		/**
		*	\brief evaluates a single message
			\param msg the message to be evaluated
			\param env the context of the event
			\return an evaluated message i.e. without variable part
		
			Evaluation of a message consists in replacing the variable parameters with values
			evaluated in a given EventContext
		*/
		SIMessage		eval (const IMessage *msg, const EventContext& env) const;

		/**
		*	\brief evaluates a list of messages
			\param msgs the message list to be evaluated
			\param env the context of the event
			\return an evaluated message list
		*/
		SIMessageList	eval (const IMessageList* msgs, const EventContext& env) const;

		/**
		*	\brief evaluates a message
			\param msg the message
			\param env the context of the event
			\return a list or arguments to be used as parameters in place of the variable
		*/
		IMessage::argslist evalMessage (const IMessage* msg, const EventContext& env) const;

	/// \brief check if a variable is a message variable
	static bool			messageVariable (const std::string& var);
	/// \brief check if a variable is a date variable
	static bool			dateVariable (const std::string& var, bool& relative);
	/// \brief check if a message has a date variable and gives the date requested map name
	static bool			hasDateVar (const IMessage *msg, std::string& mapname);
	/// \brief check if parameter has a defined range
	static bool			checkrange (const char* param);
	/// \brief gives the map name of a date variable or an empty string when no map is specified
	static std::string	parseMap (const std::string& var);
	/// \brief gives the quantification of a date variable or an empty string when no quantification is specified
	static std::string	parseQuant (const std::string& var);
	/// \brief check if a date variable requests a float value 
	static bool			floatRequested (const std::string& var);
};

} // end namespoace

#endif
