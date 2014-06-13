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


#ifndef __IFaustDSP__
#define __IFaustDSP__

#include "IFaustSignal.h"
#include "IMessageHandlers.h"
#include "TFaustDSPPlugin.h"
#include "llvm-c-dsp.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IFaustDSP;
typedef class libmapping::SMARTP<IFaustDSP>	SIFaustDSP;
    
//--------------------------------------------------------------------------
/*!
	\brief a Faust processor (that is also a parallel signal)
*/
class IFaustDSP : public IFaustSignal
{

	public:		
		static const std::string kFaustDSPType;
		static SIFaustDSP create(const std::string& name, IObject * parent)	{ return new IFaustDSP(name, parent); }
		virtual void	accept (Updater* u);

	protected:
	
        virtual void		init();
        virtual void		call_compute (int nframes, int index, int step);

				 IFaustDSP( const std::string& name, IObject * parent);
		virtual ~IFaustDSP();
    
        bool    createFaustDSP (const std::string& dsp_content);
        void    deleteFaustDSP();
		
    //    Factory and instance of the compiled DSP
        llvm_dsp*           fFD_Instance;
        llvm_dsp_factory*   fFD_Factory;
        TFaustDSPPlugin*    fFDPlugin;
        
        std::string              fSetParam;
    
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
