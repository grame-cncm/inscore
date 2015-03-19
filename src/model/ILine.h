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


#ifndef __ILine__
#define __ILine__

#include "IShapeMap.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class ILine;
typedef class libmapping::SMARTP<ILine>	SILine;

//--------------------------------------------------------------------------
/*!
*	\brief a line, with 2 control points. The 1st control point is (0,0).
*/
class ILine : public IShapeMap
{	
	public:
		/// Arrow type for end of line
		enum ArrowHeadType {
			NONE,
			TRIANGLE,
			DIAMOND,
			DISK
		};

	private:
		TFloatPoint fPoint;			// a point that describe the line, assuming that the first point is (0, 0)
		bool		fWAMode;
		enum ArrowHeadType fArrowLeft;
		enum ArrowHeadType fArrowRight;
		double fArrowSizeLeft;
		double fArrowSizeRight;

	public:
		static const std::string kLineType;
		static SILine create(const std::string& name, IObject* parent)	{ return new ILine(name, parent); }

		const TFloatPoint&	getPoint() const			{ return fPoint; }

		virtual void	print(std::ostream& out) const;
		virtual void	accept (Updater*);
		enum ArrowHeadType getArrowLeft() const { return fArrowLeft; }
		enum ArrowHeadType getArrowRight() const { return fArrowRight; }
		double getArrowSizeLeft() const { return fArrowSizeLeft; }
		double getArrowSizeRight() const { return fArrowSizeRight; }

	protected:
				 ILine( const std::string& name, IObject* parent );
		virtual ~ILine() {}

		/// \brief the 'get' form without parameter
		virtual SIMessageList getSetMsg() const;

		void	setPoint(const TFloatPoint& p)		{ fPoint = p; }
		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

	private:
		/// \brief Get arrow enum type from string
		bool getArrowType(std::string typeString, enum ArrowHeadType &type);

		MsgHandler::msgStatus setLineParam(const IMessage* msg);
		MsgHandler::msgStatus setArrowParam(const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
