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

#include <algorithm>
#include <iostream>
#include <math.h>

#include "IMessage.h"
#include "IObject.h"
#include "IPosition.h"
#include "OSCAddress.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
Position::Position():
	fXPos(kDefaultX), fYPos(kDefaultY), fXOrigin(0), fYOrigin(0), 
	fWidth(0), fHeight(0) , fZOrder(0),
	fVisible(true), fScale(1.0), fModified(true),
	fXAngle(0), fYAngle(0), fZAngle(0), fShear (0,0)
{}

void Position::setPos(const Position& p)
{
	setXPos( p.getXPos() );
	setYPos( p.getYPos() );
	setZOrder( p.getZOrder() );
	setScale( p.getScale() );
	setAngle( p.getRotateZ() );
	setWidth( p.getWidth() );
	setHeight( p.getHeight() );
	setVisible( p.getVisible() );
}

//--------------------------------------------------------------------------
// geometry 
//--------------------------------------------------------------------------
//#define PI 3.1415f
inline float rad2degree(float rad) { return float(rad*360/(2.0f*M_PI)); }
inline float degree2rad(float deg) { return float(deg*2.0f*M_PI/(360.0f)); }
void rotateXY( float startDeg, float rotateDeg, float r , float& outX, float& outY )
{
	float resultingTeta = degree2rad( startDeg + rotateDeg );
	outX = r * cos( resultingTeta );
	outY = r * sin( resultingTeta );
}

TFloatRect Position::getBoundingRect() const
{
	TFloatRect result(0.0f,0.0f);
	result.setSize( getDimension() );
	if ( getRotateZ() != 0 )
	{
		float x = result.size().width() / 2.0f;
		float y = result.size().height() / 2.0f;
		float teta = atan( y / x );
		float r = sqrt( x*x + y*y );
		float topRightAngle = rad2degree( teta );
		float bottomRightAngle = -topRightAngle;

		float Ax, Ay, Bx, By;
		rotateXY( topRightAngle , getRotateZ() , r , Ax , Ay );
		rotateXY( bottomRightAngle , getRotateZ() , r , Bx , By );

		int modAngle = int(getRotateZ()) % 360;
		if ( ( modAngle >= 0 ) && ( modAngle < 90 ) )
		{
			result.setPos( TFloatPoint( -Bx , -Ay ) );
			result.setSize( TFloatSize( Bx*2 , Ay*2 ) );
		}
		else if ( ( modAngle >= 90 ) && ( modAngle < 180 ) )
		{
			result.setPos( TFloatPoint( Ax , -By ) );
			result.setSize( TFloatSize( -Ax*2 , By*2 ) );
		}
		else if ( ( modAngle >= 180 ) && ( modAngle < 270 ) )
		{
			result.setPos( TFloatPoint( Bx , Ay ) );
			result.setSize( TFloatSize( -Bx*2 , -Ay*2 ) );
		}
		else //if ( modAngle >= 270 ) && ( modAngle < 360 )
		{
			result.setPos( TFloatPoint( -Ax , By) );
			result.setSize( TFloatSize( Ax*2 , -By*2 ) );
		}
	}

	//Scale
	result.setSize( result.size() * (double)getScale() );
	//Pos: rectangle is centered on getPos().
	result.setPos( getPos() - TFloatPoint( 0.5f * result.width() , 0.5f * result.height() ) );
	return result;
}

//--------------------------------------------------------------------------
// predicates definitions for the click and select messages
//--------------------------------------------------------------------------
typedef struct clickPredicatBase {
	float	fZOrder;
			 clickPredicatBase(float z) : fZOrder(z) {}
	virtual ~clickPredicatBase() {}
	bool operator() (const SIObject& o) const { return o->getZOrder() < fZOrder; }
} clickPredicatBase;

template <typename T> struct clickPredicat : public clickPredicatBase {
	TPoint<T>	fPoint;
			 clickPredicat(const TPoint<T>& p, float z) : clickPredicatBase(z), fPoint(p) {}
	virtual ~clickPredicat() {}
	bool operator() (const SIObject& o) const { 
		return clickPredicatBase::operator()(o) && o->getBoundingRect().include(fPoint); 
//		return clickPredicatBase::operator()(o) && o->getBoundingRect().include(pair<T,T>(fPoint.x(), fPoint.y())); 
	}
};

template <typename T> struct selectPredicat : public clickPredicatBase {
	TRect<T>	fRect;
			 selectPredicat(const TRect<T>& r, float z) : clickPredicatBase(z), fRect(r) {}
	virtual ~selectPredicat() {}
	bool operator() (const SIObject& o) const { 
		return clickPredicatBase::operator()(o) && fRect.intersect(o->getBoundingRect()); 
	}
};

template <typename T> struct includePredicat : public clickPredicatBase {
	TRect<T>	fRect;
			 includePredicat(const TRect<T>& r, float z) : clickPredicatBase(z), fRect(r) {}
	virtual ~includePredicat() {}
	bool operator() (const SIObject& o) const { 
		return clickPredicatBase::operator()(o) && fRect.include(o->getBoundingRect()); 
	}
};

typedef struct zorderSort {
	bool operator() (const SIObject& i, const SIObject& j) const { return i->getZOrder() > j->getZOrder(); }
} zorderSort;


//--------------------------------------------------------------------------
// click and select messages
//--------------------------------------------------------------------------
bool IPosition::clickPos(const IMessage* msg, IObject* parent, vector<SIObject>& outlist)	const
{ 
	if (!parent || (msg->params().size() > 1)) return false;
	
	string point = "topleft";	// default values
	if (msg->params().size() == 1)
		point = msg->params()[0]->value<string>("");

	TFloatRect r = getBoundingRect();
	TPoint<float> p;
	if (point == "topleft")				p = r.pos();
	else if (point == "bottomright")	p = r.brpos();
	else if (point == "topright")		p = r.trpos();
	else if (point == "bottomleft")		p = r.blpos();
	else if (point == "center")			p = TPoint<float>(r.x()+(r.width()/2), r.y()+(r.height()/2));
	else return false;

	clickPredicat<float> predicat(p, getZOrder());
	parent->selectsubnodes<clickPredicat<float> > (predicat, outlist);
	sort(outlist.begin(), outlist.end(), zorderSort());
	return true;
}


//--------------------------------------------------------------------------
bool IPosition::selectPos(const IMessage* msg, IObject* parent, vector<SIObject>& outlist) const
{ 
	if (!parent || (msg->params().size() > 1)) return false;
	
	string mode = "intersect";	// default values
	if (msg->params().size() == 1)
		mode = msg->params()[0]->value<string>("");

	if (mode == "intersect") {
		selectPredicat<float> p(getBoundingRect(), getZOrder());
		parent->selectsubnodes<selectPredicat<float> > (p, outlist);
	}
	else if (mode == "include") {
		includePredicat<float> p(getBoundingRect(), getZOrder());
		parent->selectsubnodes<includePredicat<float> > (p, outlist);
	}
	else return false;

	sort(outlist.begin(), outlist.end(), zorderSort());
	return true;
}


//--------------------------------------------------------------------------
// debugging facilities
//--------------------------------------------------------------------------
void Position::print (ostream& out) const
{
	out << "  pos: [" << getXPos() << "," << getYPos() << "," << getZOrder() << "]" << endl;
	out << "  size: [" << getWidth() << "," << getHeight() << "]" << endl;
	out << "  scale: " << getScale() << endl;
	out << "  visible: " << (getVisible() ? "yes" : "no") << endl;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const IPosition& o)
{
	o.print(out);
	return out;
}

}
