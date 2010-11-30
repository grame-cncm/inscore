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


#ifndef __IShape__
#define __IShape__

#include "IObject.h"
#include "maptypes.h"
#include "mapbuilder.h"

#define SOLID_STYLE			"solid"
#define DASH_STYLE			"dash"
#define DOT_STYLE			"dot"
#define DASH_DOT_STYLE		"dashDot"
#define DASH_DOT_DOT_STYLE	"dashDotDot"


namespace INScore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IShape;
typedef class SMARTP<IShape>	SIShape;
//--------------------------------------------------------------------------
/*!
	\brief a basic geometric shape.
*/
class IShape : public IObject
{
	public:
		static const std::string kSolidStyle, kDashStyle, kDotStyle, kDashDotStyle, kDashDotDotStyle;	/// < Pen style supported values.

	protected:
		float		fPenWidth;	/// <Width of the pen used to draw the borders of the shape
		
	private:
		IColor		fPenColor;	/// <Color of the pen used to draw the borders of the shape
		std::string fPenStyle;	/// <Style of the pen used to draw the borders of the shape

	public:

		/// \brief Returns the pen width
		float			getPenWidth() const			{ return fPenWidth; }
		/// \brief Returns the pen color
		const IColor&	getPenColor() const			{ return fPenColor; }
		/// \brief Returns the pen color
		const std::string&	getPenStyle() const		{ return fPenStyle; }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);

	protected:
				 IShape( const std::string& name, IObject* parent );
		virtual ~IShape() {}

		/// \brief Sets the pen width
		void			setPenWidth(float penWidth)					{ fPenWidth = penWidth; }
		/// \brief Sets the pen color
		void			setPenColor(const IColor& penColor)			{ fPenColor = penColor; }
		/// \brief Sets the pen style
		void			setPenStyle(const std::string& penStyle)	{ fPenStyle = penStyle; }
};

/*! @} */

} // end namespoace

#endif
