/*

  INScore Project

  Copyright (C) 2019  Grame

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


#pragma once

#include "TRect.h"

struct NodeGR;
typedef const struct NodeGR *  CGRHandler;

namespace inscore
{

//--------------------------------------------------------------------------
/**
*	\brief interface to provide score layout information
*/
class ScoreLayoutInfos
{
	public :
		virtual int 		firstPage() 		const = 0;
		virtual int 		lastPage()  		const = 0;
		virtual TFloatPoint	position (int page) const = 0;
		virtual float		pageWidth(int page) const = 0;
		virtual float		pageHeight(int page) const = 0;
		virtual CGRHandler 	handler() 			const = 0;
};

} // end namespoace
