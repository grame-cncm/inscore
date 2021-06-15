/*

  INScore Project

  Copyright (C) 2021  Grame

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


#pragma once

#include <set>
#include <string>

#include "IMessage.h"

namespace inscore
{

//--------------------------------------------------------------------------
/*!
	\brief Midi input filter
*/
class TMidiFilter 
{
	public:

		typedef struct msgfilter {
			virtual ~msgfilter () {}
			virtual void print (SIMessage msg) const = 0;
			virtual bool accept (char status, char data1, char data2) = 0;
		} TMsgFilter;
	
	
	private:
	enum { kKeyFilter=1, kCtrlFilter };

//	typedef bool (TMidiFilter::*TFilter) (char status, char data1, char data2) const;

	typedef struct midistatus {
		int chan;
		int type;
		midistatus (unsigned char status) { type = status >> 4; chan = status & 0xf; }
	} TMidiStatus;

	typedef struct valuefilter {
		virtual bool accept (int val) = 0;
	} TValueFilter;

	typedef struct midivaluerange : public valuefilter {
		enum { kIn, kEnter, kLeave };
		int low		= 0;			// the low value of the range
		int high 	= 0;			// the upper value
		int mode	= kIn;			// denotes if new values must enter or leave the interval
		int last    = -1;			// the last value checked
		midivaluerange() {}
		midivaluerange(const midivaluerange& val) { *this = val; }
		
		bool accept (int val) override;
		bool operator == (const midivaluerange& v) const { return (low == v.low) && (high == v.high) && (mode == v.mode); }
		bool operator != (const midivaluerange& v) const { return !(*this == v); }
		bool operator < (const midivaluerange& v) const { return (mode < v.mode) || (low < v.low) || (high < v.high); }
	} TMidiValueRange;

	typedef struct midivaluesel : public valuefilter {
		std::set<int> literal;
		TMidiValueRange  range;
		midivaluesel () {}
		midivaluesel (const midivaluesel& val) { literal = val.literal; range = val.range; }
		
		bool accept (int val) override;
		bool operator == (const midivaluesel& v) const	{ return (literal == v.literal) && (range == v.range); }
		bool operator != (const midivaluesel& v) const	{ return !(*this == v); }
		bool operator < (const midivaluesel& v) const;
		operator std::string () const;
	} TMidiValueSelector;

	typedef struct midikeysel : public msgfilter {
		bool 				keyon;
		TMidiValueSelector  keyval;
		bool				vel = false;
		TMidiValueSelector  velval;

		void print (SIMessage msg) const override;
		bool accept (char status, char data1, char data2) override;
		bool operator == (const midikeysel& v) const	{ return (keyon == v.keyon) && (keyval == v.keyval) && (vel == v.vel) && (velval == v.velval); }
		bool operator != (const midikeysel& v) const	{ return !(*this == v); }
		bool operator < (const midikeysel& v) const		{ return (keyon < v.keyon) || (keyval < v.keyval) || (vel == v.vel) || (velval == v.velval); }
	} TMidiKeySelector;

	typedef struct midiothersel : public msgfilter {
		int 				type;
		int 				num;
		TMidiValueSelector  val;

		void print (SIMessage msg) const override;
		bool accept (char status, char data1, char data2) override;
		bool operator == (const midiothersel& v) const 	{ return (type == v.type) && (val == v.val); }
		bool operator != (const midiothersel& v) const	{ return !(*this == v); }
		bool operator < (const midiothersel& v) const 	{ return (type < v.type) || (val < v.val); }
	} TMidiCtrlSelector;
	
	// conversion utilities, used to build the filter from strings
	bool string2valueList 		(const char* str, std::set<int>& list) const;
	bool string2valueRange 		(const char* str, TMidiValueRange& val) const;
	bool string2valueSelector 	(const std::string& str, TMidiValueSelector& val) const;

	int 				fType = 0;		// indicates the filter type (key or ctrl)
	int 				fChan = -1;		// the optional midi channel
	TMidiKeySelector 	fKey;			// filters key messages
	TMidiCtrlSelector 	fCtrl;			// filters other messages

	public:
				 TMidiFilter() {}
		virtual ~TMidiFilter() {}

		bool 	accept (char status, char data1, char data2);
		void	setChan (int chan)		{ fChan = chan; }
		bool	setKey  (bool keyon, const std::string& val);
		bool	setKey  (bool keyon, const std::string& val, const std::string& vval);
		bool	setCtrl (int num, const std::string& val );
		bool	setProg (int num );

		int 						getType() const		{ return fType; }
		int 						getChan() const		{ return fChan; }
		TMidiKeySelector* 			getKey() 			{ return &fKey; }
		TMidiCtrlSelector* 			getCtrl() 			{ return &fCtrl; }
		const TMidiKeySelector* 	getKey() const 		{ return &fKey; }
		const TMidiCtrlSelector* 	getCtrl() const 	{ return &fCtrl; }
		TMsgFilter* 				getCurrent()  		{ if (fType == kKeyFilter)  return getKey();
														  if (fType == kCtrlFilter) return getCtrl();
														  return nullptr; }
		const TMsgFilter* 			getCurrent() const  { if (fType == kKeyFilter)  return getKey();
														  if (fType == kCtrlFilter) return getCtrl();
														  return nullptr; }

		bool operator == (const TMidiFilter& f) const;
		bool operator != (const TMidiFilter& f) const { return !(*this == f); }
		bool operator < (const TMidiFilter& f) const;
		bool operator > (const TMidiFilter& f) const	{ return !(*this < f) && !(*this == f); }
};

} // end namespoace

