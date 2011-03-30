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

#include <QDebug>
#include <QPainter>
#include <QByteArray>

#include "OSCStream.h"
#include "TComposition.h"
#include "VSVGView.h"
#include "VApplView.h"
#include "ITLError.h"

#include "ISVGFile.h"

namespace inscore
{

//----------------------------------------------------------------------
bool VSVGItem::setFile( const char* filename)
{
	QString file = QString::fromUtf8( filename );
	if (!fRenderer.load(QString(file))) {
		ITLErr << "cannot load SVG file" << filename << ITLEndl;
		return false;
	}
	return true;
}

//----------------------------------------------------------------------
bool VSVGItem::setText( const char* text)
{
	if (!fRenderer.load(QByteArray(text))) {
		ITLErr << "cannot load svg data" << text << ITLEndl;
		return false;
	}
	return true;
}

void VSVGItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
	if (fRenderer.isValid()) {
		fRenderer.render (painter, boundingRect());
	}
}


//----------------------------------------------------------------------
VSVGView::VSVGView(QGraphicsScene * scene, const ISVGFile* svg) 
	: VMappedShapeView( scene , new MouseEventAble<VSVGItem>(svg) )
{
}
VSVGView::VSVGView(QGraphicsScene * scene, const ISVG* svg) 
	: VMappedShapeView( scene , new MouseEventAble<VSVGItem>(svg) )
{
}

//----------------------------------------------------------------------
void VSVGView::updateView( ISVGFile * svg  )
{
	if (svg->changed()) {
		item()->setFile (svg->getFile().c_str());
		svg->changed(false);
	}
	float alpha = svg->getA() / 255.f;
	item()->setOpacity (alpha);
	VShapeView::updateView( svg );	
}

//----------------------------------------------------------------------
void VSVGView::updateView( ISVG * svg  )
{
	if (svg->newData()) {
		item()->setText (svg->getText().c_str());
	}
	float alpha = svg->getA() / 255.f;
	item()->setOpacity (alpha);
	VShapeView::updateView( svg );	
}

} // end namespoace
