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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <math.h>

#include "IGraphicSignal.h"
#include "ITLError.h"
#include "IScene.h"
#include "ISignalNode.h"
#include "GraphicSignal.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const std::string IGraphicSignal::kRoundCurveType = ROUND_CURVE_TYPE;
const std::string IGraphicSignal::kStepCurveType = STEP_CURVE_TYPE;

const std::string IGraphicSignal::kDrawLineTop = DRAW_LINE_TOP;
const std::string IGraphicSignal::kDrawLineBottom = DRAW_LINE_BOTTOM;
const std::string IGraphicSignal::kDrawLineBoth = DRAW_LINE_BOTH;

const std::string IGraphicSignal::kThicknessCentered = THICKNESS_CENTERED;
const std::string IGraphicSignal::kThicknessUp = THICKNESS_UP;
const std::string IGraphicSignal::kThicknessDown = THICKNESS_DOWN;

//--------------------------------------------------------------------------
const string IGraphicSignal::kGraphicType("graph");
const string ISGraphicSignal::kSGraphicType("fastgraph");
const string IRGraphicSignal::kRGraphicType("radialgraph");

IGraphicSignal::IGraphicSignal( const std::string& name, IObject* parent ) : IObject(name, parent),
	fCurveType(kRoundCurveType), fDrawLine(kDrawLineBoth), fThicknessMode(kThicknessCentered),
	fIgnoreSignalColor(false),fPenIgnoreSignalColor(false)
{
	fLocalMappings = TLocalMapping<long,1>::create();
	fTypeString = kGraphicType;
	setWidth(1.0f, false, false);
	setHeight(1.0f, false, false);
}

//--------------------------------------------------------------------------
void IGraphicSignal::setHandlers ()
{
	IObject::setHandlers();
	fGetMsgHandlerMap[""]					= TGetParamMsgHandler<SISignal>::create(fSignal);
	fGetMsgHandlerMap[kdimension_GetMethod]	= getDimParamMsgHandler::create(this);
	
	fMsgHandlerMap[kmap_GetSetMethod]		= TMethodMsgHandler<IGraphicSignal>::create(this, &IGraphicSignal::mapMsg);
	fMsgHandlerMap[kmapplus_SetMethod]		= TMethodMsgHandler<IGraphicSignal>::create(this, &IGraphicSignal::mapAddMsg);
	fMsgHandlerMap[kmapf_SetMethod]			= TMethodMsgHandler<IGraphicSignal>::create(this, &IGraphicSignal::mapFileMsg);

//	fSetMsgHandlerMap["curveType"]	= TSetFieldHandler<std::string>::create( fCurveType );
//	fGetMsgHandlerMap["curveType"]	= TGetParamMsgHandler<std::string>::create(fCurveType);
//	
//	fSetMsgHandlerMap["drawLine"]	= TSetFieldHandler<std::string>::create( fDrawLine );
//	fGetMsgHandlerMap["drawLine"]	= TGetParamMsgHandler<std::string>::create(fDrawLine);
//	
//	fSetMsgHandlerMap["thickness"]	= TSetFieldHandler<std::string>::create( fThicknessMode );
//	fGetMsgHandlerMap["thickness"]	= TGetParamMsgHandler<std::string>::create(fThicknessMode);
//
//	fSetMsgHandlerMap["ignoreSignalColor"]	= TSetFieldHandler<bool>::create( fIgnoreSignalColor );
//	fGetMsgHandlerMap["ignoreSignalColor"]	= TGetParamMsgHandler<bool>::create(fIgnoreSignalColor);
//	
//	fSetMsgHandlerMap["penIgnoreSignalColor"]	= TSetFieldHandler<bool>::create( fPenIgnoreSignalColor );
//	fGetMsgHandlerMap["penIgnoreSignalColor"]	= TGetParamMsgHandler<bool>::create(fPenIgnoreSignalColor );
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicSignal::mapFileMsg (const IMessage* msg )	
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,1>::mapFileMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicSignal::mapMsg (const IMessage* msg )	
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,1>::mapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicSignal::mapAddMsg (const IMessage* msg )	
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,1>::addMapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
OSCStream& operator <<(OSCStream& s, const SISignal& val)
{
	if (val) s << val->name();
	return s;
}

//--------------------------------------------------------------------------
IMessage& operator <<(IMessage& s, const SISignal& val)
{
	if (val) s << val->name();
	return s;
}

//--------------------------------------------------------------------------
void IGraphicSignal::print (ostream& out) const
{
	IObject::print (out);
	out << "  input signal: " << fSignal->name();
	out << "  curveType: " << getCurveType();
	out << "  thickness: " << getThicknessMode();
	out << "  drawLine: " << getDrawLine();
	out << "  ignoreSignalColor: " << getIgnoreSignalColor();
	out << "  penIgnoreSignalColor: " << getPenIgnoreSignalColor();
}

//--------------------------------------------------------------------------
void IGraphicSignal::accept (Updater* u)
{
	u->updateTo (SIGraphicSignal(this));
}

//--------------------------------------------------------------------------
int IGraphicSignal::dimension () const
{
	return fSignal ? int(ceil(fSignal->dimension() / float(GraphicFrame::FrameSize()))) : 0;
}

//--------------------------------------------------------------------------
void IGraphicSignal::set(const SISignal& s)
{
	fSignal = s;
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicSignal::set (const IMessage* msg )	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	if (msg->size() == 2) {
		string signame;
		if (!msg->param(1, signame)) return MsgHandler::kBadParameters;
		SIObject parent = getParent();
        if (!parent) return MsgHandler::kCreateFailure;
		SISignalNode isignals = parent->signalsNode();
		if (!isignals) return MsgHandler::kCreateFailure;

		subnodes sigs;
		if (isignals->find(signame, sigs)) {
			set(dynamic_cast<ISignal*>((IObject*)sigs[0]));
			return MsgHandler::kProcessed;
		}

//		SISignal s =  isignals->find(signame);
//		if (s) {
//			set(s);
//			return MsgHandler::kProcessed;
//		}
		ITLErr << "Graphic signal" << name() << ": unknown signal" << signame << ITLEndl;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
SIMessage& IGraphicSignal::getDimParamMsgHandler::print(SIMessage& out) const
{
	*out << fGraph->dimension();
	return out;
}


}
