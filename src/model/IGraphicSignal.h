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


#ifndef __IGraphicSignal__
#define __IGraphicSignal__

#include <vector>
#include <map>
#include "IShape.h"
#include "ISignal.h"
#include "GraphicSignal.h"
#include "TLocalMapping.h"
#include "TRelation.h"
#include "Updater.h"
#include "TMapMsgHandler.h"


#define ROUND_CURVE_TYPE	"round"
#define STEP_CURVE_TYPE		"step"

#define DRAW_LINE_TOP		"top"
#define DRAW_LINE_BOTTOM	"bottom"
#define DRAW_LINE_BOTH		"both"

#define THICKNESS_CENTERED	"centered"
#define THICKNESS_UP		"up"
#define THICKNESS_DOWN		"down"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IGraphicSignal;
typedef class SMARTP<IGraphicSignal>	SIGraphicSignal;

//--------------------------------------------------------------------------
/*!
	\brief a data graphic representation  
*/
class IGraphicSignal : public IShape
{
	SISignal		fSignal;
	
	protected:
		typedef SMARTP<TLocalMapping<FrameSegment> >	SLocalMapping;
		SLocalMapping	fLocalMappings;
	std::string		fCurveType;		/// < How the border of the graphs are drawn.
	std::string		fDrawLine;		/// < Which border of the graphs are drawn with a pen.
	std::string		fThicknessMode;	/// < The thickness orientation: top, bottom, or centered around the 'y' value.
	bool			fIgnoreSignalColor;		/// < If ON, the graph will be filled using inherited IPosition::fColor attribute.
	bool			fPenIgnoreSignalColor;	/// < If ON, the graph's bounds will be outlined using inherited IPosition::fColor attribute.

	public:	
		static const std::string kGraphicType;
		static const std::string kRoundCurveType, kStepCurveType;
		static const std::string kDrawLineBottom, kDrawLineTop, kDrawLineBoth;
		static const std::string kThicknessCentered, kThicknessUp, kThicknessDown;
		static SIGraphicSignal create(const std::string& name, IObject* parent)	{ return new IGraphicSignal(name, parent); }

		const	SLocalMapping&	localMappings()	const	{ return fLocalMappings; }
				SLocalMapping&	localMappings()			{ return fLocalMappings; }

		///! gives the input signal
		const SISignal &		getSignal() const		{ return fSignal; }
		///! gives the input signal value at index \c i
		virtual GraphicFrames	get (int i) const		{ return fSignal->ParallelSignal::get<GraphicFrames>(i); }

		///! gives the graphic signal dimension i.e. the count of simple graphic signals
		virtual int			dimension () const;
		
		virtual GraphicFrames	defaultValue() const	{ std::vector<float> v; fSignal->ParallelSignal::defaultValue(v); return GraphicFrames(v); }

		virtual void		print(std::ostream& out) const;
		virtual void		accept (Updater*);

		virtual const std::string& getCurveType() const { return fCurveType; }
		virtual const std::string& getThicknessMode() const { return fThicknessMode; }
		virtual const std::string& getDrawLine() const { return fDrawLine; }
		virtual bool getIgnoreSignalColor() const { return fIgnoreSignalColor; }
		virtual bool getPenIgnoreSignalColor() const { return fPenIgnoreSignalColor; }
		
	protected:
				 IGraphicSignal( const std::string& name, IObject* parent );
		virtual ~IGraphicSignal() {}

		///! sets the graphic signal input signal
		virtual void	set (const SISignal& s);

		///! \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus	set (const IMessage* msg);

		/// \brief the \c 'mapf' message handler
		MsgHandler::msgStatus mapFileMsg (const IMessage* msg );
		/// \brief the \c 'map' message handler
		MsgHandler::msgStatus mapMsg (const IMessage* msg );
		/// \brief the \c 'map+' message handler
		MsgHandler::msgStatus mapAddMsg (const IMessage* msg );

		/// \brief get an object maps
		virtual IMessageList __getMaps () const	{ return TMapMsgHandler<FrameSegment>::getMapMsgs( localMappings() , this ); }

		///! \brief get the curve type
//		virtual void setCurveType(const std::string& curveType) { fCurveType = curveType; }

		class getDimParamMsgHandler : public GetParamMsgHandler {
				IGraphicSignal* fGraph;
				getDimParamMsgHandler(IGraphicSignal* o) : fGraph(o) {}
			public: 
				static SGetParamMsgHandler create(IGraphicSignal* o) { return new getDimParamMsgHandler(o); }
				virtual IMessage&  print(IMessage& out) const;
		};
};

OSCStream& operator <<(OSCStream& s, const SISignal& val);
IMessage& operator <<(IMessage& s, const SISignal& val);

//--------------------------------------------------------------------------
class SigModified : public Updater
{
	public:
				 SigModified() {}
		virtual ~SigModified() {}
		virtual bool needupdate (IObject*)		{ return true; }
		virtual void updateTo (IGraphicSignal*);
};


/*! @} */

} // end namespoace

#endif
