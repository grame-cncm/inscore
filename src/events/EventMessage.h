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


#ifndef __EventMessage__
#define __EventMessage__

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
class EventMessage;
typedef libmapping::SMARTP<EventMessage>	SEventMessage;

typedef struct MouseLocation {
	enum { noloc = -999999 };
	float fx, fy, fabsx, fabsy, fsx, fsy;

	MouseLocation (float x, float y, float ax, float ay, float sx, float sy)
		: fx(x), fy(y), fabsx(ax), fabsy(ay), fsx(sx), fsy(sy) {}
	MouseLocation ()
		: fx(noloc), fy(noloc), fabsx(noloc), fabsy(noloc), fsx(noloc), fsy(noloc) {}
} MouseLocation;

typedef struct EventContext {
	MouseLocation			mouse;
	libmapping::rational	date;
	const IObject*			object;
	const IMessage*			varmsg;

	EventContext (const MouseLocation& ml, const libmapping::rational& d, const IObject* o)
		: mouse(ml), date(d), object(o), varmsg(0) {}
	EventContext (const IObject* o)
		: object(o), varmsg(0) {}
} EventContext;

//----------------------------------------------------------------------
class EventMessage : public libmapping::smartable
{
	IMessage *			fMessage;
	std::map<int, SIMessage>	fVarMsgs;		// messages used as variables stored with their index
	std::string	fDest;
	int			fPort;
	
	void decodeAddress	(const std::string& address, std::string& oscAddress, std::string& host, int& port) const;
	void sockSend		(const IMessage* msg, const std::string& dst, int port) const;
	void localSend		(const IMessage* msg) const;

	void	decodeMessage	(const std::string& objname, const std::string& scene, const IMessage* msg, int startindex);
	std::string checkVariableAddress (const std::string& address, const std::string& objname, const std::string& scene) const;

	void	checkVariableMsg (const std::string& param, int index);
	void	splitMsg (const char * msg, std::vector<std::string>& list);

	float	checkfloatrange		(const std::string& param, float val) const;
	int		checkintrange		(const std::string& param, float val) const;
	bool	checkrange (const char* param) const;
	bool	checkfloat (const char* param) const;
	
	// evaluate the parameters of a message in a given context
	void	eval (const IMessage *msg, EventContext& env, IMessage& outmsg) const;
	// evaluate a message variable in a given context
	void	eval (const std::string& var, EventContext& env, IMessage& outmsg) const;
	// evaluate a variable message in a given context
	void	eval (const IMessage* msg, const IObject * object, IMessage& outmsg) const;
			
	protected:
				 EventMessage(const std::string& objname, const std::string& scene, const IMessage* msg, int startindex);
		virtual ~EventMessage();

	public:
		enum { kDefaultUPDPort = 7001 };
		
		static SEventMessage create (const std::string& objname, const std::string& scene, const IMessage* msg, int startindex)	
					{ return new EventMessage(objname, scene, msg, startindex); }
		void	send () const;
		void	send (EventContext& env);

		bool	hasDateVar (std::string& mapname, int& num, int& denum, bool& relative) const;
		bool	isDateVar (const std::string& var, std::string& mapname, int& num, int& denum, bool& relative) const;
		const IMessage * message() const		{ return fMessage; }
		
		std::string address() const;

	static bool parseMap (const std::string& var, std::string& map);
	static bool parseQuant (const std::string& var, int& n, int& d);
};

} // end namespoace

#endif
