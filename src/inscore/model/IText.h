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


#ifndef __IText__
#define __IText__

#include <string>
#include <map>

#include "IObject.h"
#include "IGraphicBasedObject.h"
#include "maptypes.h"
//#include "mapbuilder.h"
#include "TLocalMapping.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IText;
typedef class libmapping::SMARTP<IText>	SIText;
//--------------------------------------------------------------------------
/*!
	\brief a text element of the model
*/
class IText : public IGraphicBasedObject
{
	protected:
		std::string	fText;
		int fFontSize;
		std::string fFontFamily;
		std::string fFontWeight;
		std::string fFontStyle;

	public:		
		static const std::string kTextType;

		// Constants for font style and font weight.
		static const std::string kStyleNormal;
		static const std::string kStyleItalic;
		static const std::string kStyleOblique;
		static const std::string kWeightNormal;
		static const std::string kWeightLight;
		static const std::string kWeightDemiBold;
		static const std::string kWeightBold;
		static const std::string kWeightBlack;

		static SIText create(const std::string& name, IObject * parent)	{ return new IText(name, parent); }

		/// \brief returns the text of the object
		const std::string&	getText() const						{ return fText; }
		/// \brief set the object text \param text the new text
		void				setText(const std::string& text)	{ fText = text; }

		virtual void		print(std::ostream& out) const;
		virtual void		accept (Updater*);
		
		int getFontSize() const { return fFontSize; }
		void setFontSize(int fontSize) {fFontSize = fontSize;}

		std::string getFontFamily() const { return fFontFamily; }
		void setFontFamily(const std::string & fontFamily) { fFontFamily = fontFamily; }

		std::string getFontStyle() const { return fFontStyle; }
		MsgHandler::msgStatus setFontStyle(const IMessage* msg);

		std::string getFontWeight() const { return fFontWeight; }
		MsgHandler::msgStatus setFontWeight(const IMessage* msg);

	protected:
				 IText( const std::string& name, IObject * parent );
		virtual ~IText() {}

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

		/// \brief object \c 'write' message handler.
		virtual MsgHandler::msgStatus writeMsg (const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
