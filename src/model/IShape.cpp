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

#include "IShape.h"
#include "IMessage.h"
#include "IAppl.h"
#include "Updater.h"
#include "segment2relativetimereader.h"

using namespace std;

namespace interlude
{

const std::string IShape::kSolidStyle = SOLID_STYLE;
const std::string IShape::kDashStyle = DASH_STYLE;
const std::string IShape::kDotStyle = DOT_STYLE;
const std::string IShape::kDashDotStyle = DASH_DOT_STYLE;
const std::string IShape::kDashDotDotStyle = DASH_DOT_DOT_STYLE;

//--------------------------------------------------------------------------
IShape::IShape( const std::string& name, IObject* parent ) : IObject(name, parent)
{ 
	fPenWidth = 0;
	fPenColor = IColor(0,0,0,255);
	fPenStyle = kSolidStyle;

	fMsgHandlerMap["penColor"]	= TMethodMsgHandler<IColor>::create(&fPenColor, &IColor::set);
	fMsgHandlerMap["penWidth"]	= TSetMethodMsgHandler<IShape, float>::create(this, &IShape::setPenWidth);
	fMsgHandlerMap["penStyle"]  = TSetMethodMsgHandler<IShape, string>::create(this, &IShape::setPenStyle);

//	fMsgHandlerMap["penWidth"]	= TSetMsgHandler<float>::create(fPenWidth);
//	fMsgHandlerMap["penStyle"]  = TSetMsgHandler<std::string>::create(fPenStyle);

	fGetMsgHandlerMap["penWidth"]	= TGetParamMsgHandler<float>::create(fPenWidth);
	fGetMsgHandlerMap["penColor"]	= TGetParamMsgHandler<IColor>::create(fPenColor);
	fGetMsgHandlerMap["penStyle"]	= TGetParamMsgHandler<std::string>::create(fPenStyle);	
}

//--------------------------------------------------------------------------
void IShape::accept (Updater* u)
{
	u->updateTo (SIShape(this));
}

//--------------------------------------------------------------------------
void IShape::print (ostream& out) const
{
	IObject::print (out);
	out << "  penWidth: " << fPenWidth << endl;
	out << "  penStyle: " << fPenStyle << endl;
	out << "  penColor: [" << fPenColor.getR() << "," << fPenColor.getG() << "," << fPenColor.getB() << "]" << endl;
}

/*
//--------------------------------------------------------------------------
RelativeTimeSegment IShape::getRelTimeSegment(const GraphicSegment& gseg,const std::string& mapName) const
{
	std::vector<RelativeTimeSegment> timeSegments;
	gr2rtMappingMap::const_iterator i = fGraphic2RelativeTimeMapping.find(mapName);
	if ( i != fGraphic2RelativeTimeMapping.end() )
	{
		((*i).second)->directRelation( gseg , timeSegments );
		return ( timeSegments.size() ) ? *(timeSegments.begin()) : RelativeTimeSegment();
	}
	else
		return RelativeTimeSegment();
}

//--------------------------------------------------------------------------
void IShape::getRelTimeSegments(const vector<GraphicSegment>& segList, vector<RelativeTimeSegment>& result,const std::string& mapName) const
{
	gr2rtMappingMap::const_iterator i = fGraphic2RelativeTimeMapping.find(mapName);
	if ( i != fGraphic2RelativeTimeMapping.end() )
		((*i).second)->directRelation( segList , result );
}

//--------------------------------------------------------------------------
GraphicSegment IShape::getGraphicSegment(const RelativeTimeSegment& tseg,const std::string& mapName) const
{
	vector<GraphicSegment> graphicSegments;
	gr2rtMappingMap::const_iterator i = fGraphic2RelativeTimeMapping.find(mapName);
	if ( i != fGraphic2RelativeTimeMapping.end() )
	{
		((*i).second)->reverseRelation( tseg , graphicSegments );
		return ( graphicSegments.size() ) ? *(graphicSegments.begin()) : GraphicSegment();
	}
	else
		return GraphicSegment();
}

//--------------------------------------------------------------------------
void IShape::getGraphicSegments(const vector<RelativeTimeSegment>& segList, vector<GraphicSegment>& result,const std::string& mapName) const
{
	gr2rtMappingMap::const_iterator i = fGraphic2RelativeTimeMapping.find(mapName);
	if ( i != fGraphic2RelativeTimeMapping.end() )
		((*i).second)->reverseRelation( segList , result );
}

//--------------------------------------------------------------------------
void IShape::getAllMapNames(std::vector<std::string>& result) const
{
	for ( gr2rtMappingMap::const_iterator i = fGraphic2RelativeTimeMapping.begin() ; i != fGraphic2RelativeTimeMapping.end() ; i++ )
		if ( i->second )
			result.push_back( i->first );
}
*/

}
