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


#ifndef __ISVGFile__
#define __ISVGFile__

#include <string>
#include "TFile.h"
#include "IGraphicBasedObject.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class ISVGFile;
typedef class libmapping::SMARTP<ISVGFile>	SISVGFile;
//--------------------------------------------------------------------------
/*!
	\brief a SVG element based on a file
*/
class ISVGFile :  public IGraphicBasedObject, public TFile
{
	public:		
		static const std::string kSVGFileType;
		static SISVGFile create(const std::string& name, IObject * parent)	{ return new ISVGFile(name, parent); }

		virtual void		print(std::ostream& out) const;
		virtual void		accept (Updater*);

	protected:
				 ISVGFile( const std::string& name, IObject * parent );
		virtual ~ISVGFile() {}

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
