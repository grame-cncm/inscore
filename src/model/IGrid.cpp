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

#include "IGrid.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string IGrid::kGridType("grid");

static const char* kLeftRightStr = "leftright";
static const char* kTopBottomStr = "topbottom";

//--------------------------------------------------------------------------
IGrid::IGrid( const std::string& name, IObject* parent ) : IRectShape(name, parent), fDimensions(0, 0)
{ 
	fTypeString = kGridType;
//	fColumns = fRows = 0;
	fXBorder = fYBorder = 0.f;
	fOrder = kLeftRight;
	
	setColor (IColor(255,255,255,0));

	fMsgHandlerMap[kcolumns_GetSetMethod]		= TSetMethodMsgHandler<IGrid,int>::create(this, &IGrid::setColumns);
	fMsgHandlerMap[krows_GetSetMethod]			= TSetMethodMsgHandler<IGrid,int>::create(this, &IGrid::setRows);
	fMsgHandlerMap[kxborder_GetSetMethod]		= TSetMethodMsgHandler<IGrid,float>::create(this, &IGrid::setXBorder);
	fMsgHandlerMap[kyborder_GetSetMethod]		= TSetMethodMsgHandler<IGrid,float>::create(this, &IGrid::setYBorder);
	fMsgHandlerMap[korder_GetSetMethod]			= TSetMethodMsgHandler<IGrid,string>::create(this, &IGrid::setOrderStr);

	fGetMsgHandlerMap[""]						= TGetParamMsgHandler<TIntSize>::create(getDims());
	fGetMsgHandlerMap[kcolumns_GetSetMethod]	= TGetParamMethodHandler<IGrid, int (IGrid::*)() const>::create(this, &IGrid::getColumns);
	fGetMsgHandlerMap[krows_GetSetMethod]		= TGetParamMethodHandler<IGrid, int (IGrid::*)() const>::create(this, &IGrid::getRows);
	fGetMsgHandlerMap[kxborder_GetSetMethod]	= TGetParamMethodHandler<IGrid, float (IGrid::*)() const>::create(this, &IGrid::getXBorder);
	fGetMsgHandlerMap[kyborder_GetSetMethod]	= TGetParamMethodHandler<IGrid, float (IGrid::*)() const>::create(this, &IGrid::getYBorder);
	fGetMsgHandlerMap[korder_GetSetMethod]		= TGetParamMethodHandler<IGrid, string (IGrid::*)() const>::create(this, &IGrid::getOrderStr);
}

//--------------------------------------------------------------------------
void IGrid::accept (Updater* u)
{
	u->updateTo (SIGrid(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGrid::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	if (msg->size() == 3) {
		int cols, rows;
		if (msg->param(1, cols) && msg->param(2, rows)) {
			if ( ( cols != getColumns() ) || ( rows != getRows()) )  {
				if (!getWidth())	setWidth( 1. );
				if (!getHeight())	setHeight( 1. );
				setColumns(cols);
				setRows(rows);
				newData(true);
				status = MsgHandler::kProcessed;
			}
		}
		else status = MsgHandler::kProcessedNoChange;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

//--------------------------------------------------------------------------
const char*	IGrid::order2string(int order) const
{
	if (order == kTopBottom) return kTopBottomStr;
	return kLeftRightStr;
}

//--------------------------------------------------------------------------
int IGrid::string2order(const char* order) const
{
	const string o(order);
	if (o == kTopBottomStr) return kTopBottom;
	return kLeftRight;
}

}
