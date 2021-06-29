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

#include <string>

#include "AudioNode.h"
#include "IObjectVNodes.h"
#include "IRectShape.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class AudioIO;
typedef class libmapping::SMARTP<AudioIO>	SAudioIO;

//--------------------------------------------------------------------------
/*!
	\brief audio IO handler
*/
class AudioIO : public IRectShape, public AudioNode
{
    public:
		static const std::string kAudioIOType;
		static SAudioIO create(const std::string& name, IObject * parent)	{ return new AudioIO(name, parent); }
		virtual void	accept (Updater* u);

	protected:
				 AudioIO(const std::string& name, IObject * parent);
		virtual ~AudioIO() {}

		virtual void setHandlers() 				{ timeAble(); }
		virtual void createVirtualNodes ()  	{ fDebug = IObjectDebug::create(this); add ( fDebug ); }

		std::vector<int> getInOut() const;
		/// \brief method handlers
		virtual MsgHandler::msgStatus	set (const IMessage* msg);
};

/*! @} */

} // end namespoace
