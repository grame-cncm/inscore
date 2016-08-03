/*

  INScore Project

  Copyright (C) 2016  Grame

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

#ifndef __TMaths__
#define __TMaths__


#include "IMessage.h"


namespace inscore 
{

//--------------------------------------------------------------------------------------------
// simple math operations between messages arguments
//--------------------------------------------------------------------------------------------
/*
	supported operators are + - * and /
	in addition, a test form is supported ( testval ? trueval : falseval)
	
*/
class TMaths
{
//	bool check (const IMessage::argslist& args) const;

	float		tofloat (const IMessage::argPtr& arg) const;
	std::string tostring (const IMessage::argPtr& args) const;
	
	typedef bool (TMaths::*booloperation) (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	typedef IMessage::argPtr (TMaths::*operation) (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	typedef IMessage::argPtr (TMaths::*unaryoperation) (const IMessage::argPtr& arg) const;
	typedef enum	{ kUnknow, kInt, kFloat, kString } TType;

	TType	type (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;


	IMessage::argPtr	add		(int, int) const;
	IMessage::argPtr	add		(float, float) const;
	IMessage::argPtr	add		(int, std::string) const;

	IMessage::argPtr	add		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	IMessage::argPtr	inc		(const IMessage::argPtr& arg) const;
	IMessage::argPtr	dec		(const IMessage::argPtr& arg) const;
	IMessage::argPtr	minus	(const IMessage::argPtr& arg) const;
	IMessage::argPtr	sub		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	IMessage::argPtr	mult	(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	IMessage::argPtr	div		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	IMessage::argPtr	mod		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;

	bool	tobool		(const IMessage::argPtr& arg) const;
	bool	equal		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	bool	greater		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	bool	greatereq		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	bool	less		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;
	bool	lesseq		(const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const;

	IMessage::argslist*	apply	(operation op, const IMessage::argslist& arg1, const IMessage::argslist& arg2) const ;
	IMessage::argslist*	apply	(unaryoperation op, const IMessage::argslist& args) const ;
	bool				apply	(booloperation op, const IMessage::argslist& arg1, const IMessage::argslist& arg2) const ;

	public:
				 TMaths() {}
		virtual ~TMaths() {}

		IMessage::argslist* inc		(const IMessage::argslist& arg) const;
		IMessage::argslist* dec		(const IMessage::argslist& arg) const;
		IMessage::argslist*	add		(IMessage::argslist* arg1, IMessage::argslist* arg2) const;
		IMessage::argslist*	minus	(IMessage::argslist* arg) const;
		IMessage::argslist*	sub		(IMessage::argslist* arg1, IMessage::argslist* arg2) const;
		IMessage::argslist*	mult	(IMessage::argslist* arg1, IMessage::argslist* arg2) const;
		IMessage::argslist*	div		(IMessage::argslist* arg1, IMessage::argslist* arg2) const;
		IMessage::argslist*	mod		(IMessage::argslist* arg1, IMessage::argslist* arg2) const;


		bool	tobool		(const IMessage::argslist& arg) const;
		bool	equal		(const IMessage::argslist& arg1, const IMessage::argslist& arg2) const;
		bool	greater		(const IMessage::argslist& arg1, const IMessage::argslist& arg2) const;
		bool	greatereq	(const IMessage::argslist& arg1, const IMessage::argslist& arg2) const;
		bool	less		(const IMessage::argslist& arg1, const IMessage::argslist& arg2) const;
		bool	lesseq		(const IMessage::argslist& arg1, const IMessage::argslist& arg2) const;
};


} // namespace

#endif
