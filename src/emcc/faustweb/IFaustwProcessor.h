/*

  INScore Project

  Copyright (C) 2009,2021  Grame

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

#include "IFaustProcessor.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class IFaustwProcessor;
typedef class libmapping::SMARTP<IFaustwProcessor>	SIFaustwProcessor;

//--------------------------------------------------------------------------
/*!
	\brief a Faust processor (that is also a parallel signal)
*/
class IFaustwProcessor : public IFaustProcessor
{
	std::string fJsonFile;
	
    public:
		static const std::string kFaustwProcessorfType;
		static SIFaustwProcessor create(const std::string& name, IObject * parent)	{ return new IFaustwProcessor(name, parent); }
		virtual void	accept (Updater* u);
		virtual MsgHandler::msgStatus 	set 	(const IMessage* msg);
		virtual const IFaustwProcessor* wasmBased() const 	{ return this; }
				const std::string&	json() const 			{ return fJsonFile; }
		
	protected:
				 IFaustwProcessor( const std::string& name, IObject * parent);
		virtual ~IFaustwProcessor() {}

		/// \brief print the set message
		virtual void	print (IMessage& out) const;
};

/*! @} */

} // end namespoace
