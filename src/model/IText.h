/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __IText__
#define __IText__

#include <string>
#include <map>

#include "IObject.h"
#include "IGraphicBasedObject.h"
#include "maptypes.h"
#include "mapbuilder.h"
#include "TLocalMapping.h"

namespace interlude
{

/*!
\addtogroup ITLModel
@{
*/

class VTextView;
class Updater;
class IText;
typedef class SMARTP<IText>	SIText;
//--------------------------------------------------------------------------
/*!
	\brief a text element of the model
*/
class IText : public IGraphicBasedObject
{
	protected:
		std::string	fText;
		VTextView * fView;

	public:		
		static const std::string kTextType;
		static SIText create(const std::string& name, IObject * parent)	{ return new IText(name, parent); }

		/// \brief returns the text of the object
		const std::string&	getText() const						{ return fText; }
		/// \brief set the object text \param text the new text
		void				setText(const std::string& text)	{ fText = text; }

		virtual void		print(std::ostream& out) const;
		virtual void		accept (Updater*);
		
		VTextView *		getView () const				{ return fView; }
		void			setView (VTextView * view)		{ fView = view; }
		VGraphicsItemView*	graphicView() const			{ return (VGraphicsItemView*)fView; }

	protected:
				 IText( const std::string& name, IObject * parent );
		virtual ~IText() {}

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
