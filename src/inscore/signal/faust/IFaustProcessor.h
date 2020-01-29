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


#ifndef __IFaustProcessor__
#define __IFaustProcessor__

#include "IFaustSignal.h"
#include "IMessageHandlers.h"
#include "QPlugin.h"
#include "faust-inscore.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IFaustProcessor;
typedef class libmapping::SMARTP<IFaustProcessor>	SIFaustProcessor;
//--------------------------------------------------------------------------
/*!
	\brief a Faust processor (that is also a parallel signal)
*/
class IFaustProcessor : public IFaustSignal, public QPlugin
{
	buildUserInterface	fBuildUI;
	compute				fCompute;
	getNumInputs		fInputs;
	getNumOutputs		fOutputs;
	fpinit				fInit;
	
		virtual void		init();
        virtual void		call_compute (int nframes, int index, int step);
	
    public:		
		static const std::string kFaustProcessorType;
		static SIFaustProcessor create(const std::string& name, IObject * parent)	{ return new IFaustProcessor(name, parent); }
		virtual void	accept (Updater* u);

	protected:

				 IFaustProcessor( const std::string& name, IObject * parent);
		virtual ~IFaustProcessor();
		
		std::string	fLibrary;

		/// \brief print the set message
		virtual void	print (IMessage& out) const;

		/// \brief put the message values into a projection of the signal
//		virtual bool	putAt (const IMessage* msg, int index, int step);

		/// \brief set signals to the message signals
		virtual MsgHandler::msgStatus	set (const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
