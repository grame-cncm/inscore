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


#ifndef __IImage__
#define __IImage__

#include <string>
#include "IGraphicBasedObject.h"
#include "TFile.h"
#include "TLocalMapping.h"
#include "TRelation.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class VImageView;
class Updater;
class IImage;
typedef class SMARTP<IImage>	SIImage;
//--------------------------------------------------------------------------
/*!
	\brief a file based image
*/
class IImage : public IGraphicBasedObject,  public TFile
{
	public:		
		static const std::string kImageType;
		static SIImage create(const std::string& name, IObject * parent)	{ return new IImage(name, parent); }
		virtual void	accept (Updater* u);

		/// \brief set the path name \param path the new file path
		void			setFile(const std::string& path);
		
		VImageView *	getView () const				{ return fView; }
		void			setView (VImageView * view) 	{ fView = view; }
		VGraphicsItemView*	graphicView() const			{ return (VGraphicsItemView*)fView; }

	protected:
		VImageView * fView;

				 IImage( const std::string& name, IObject * parent);
		virtual ~IImage() {}

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
