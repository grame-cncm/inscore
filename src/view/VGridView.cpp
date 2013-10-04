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

#include <QPainter>
#include <algorithm>

#include "VGridView.h"
#include "IGrid.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//----------------------------------------------------------------------
VGridView::VGridView(QGraphicsScene * scene, const IGrid* grid) 
	: VMappedShapeView( scene , new MouseEventAble<QGraphicsRectItem>(grid) )
    {}

//----------------------------------------------------------------------
void VGridView::updateView( IGrid * grid  )
{
    if(!grid->getParent()->getMaster(grid))
    {
        if(grid->getParent()->getTypeString() != IAppl::kApplType && grid->getParent()->getTypeString() != IScene::kSceneType)
            setParentItem(grid->getParent()->getView()?grid->getParent()->getView():0);
    }
	QRectF newRect( 0,0,  relative2SceneWidth(grid->getWidth()), relative2SceneHeight(grid->getHeight()) );
	if ( newRect != item()->rect() )
	{
		item()->setRect( newRect );
		itemChanged();
	}
	VShapeView::updateView( grid );
}

//----------------------------------------------------------------------
void VGridView::updateLocalMapping (IGrid* grid)
{
	int cols = grid->getColumns();
	int rows = grid->getRows();
	if ((cols < 2) || (rows < 2))
		VGraphicsItemView::buildDefaultMapping (grid);
	else
	{
		float xborder = max(0.f, min(1.f, grid->getXBorder()));
		float yborder = max(0.f, min(1.f, grid->getYBorder()));

		float w = 2.f / cols;
		float h = 2.f / rows;
		xborder *= w;
		yborder *= h;
		w -= xborder*2;
		h -= yborder*2;
		
		float left = -1 + xborder;
		float top = -1 + yborder;
		rational d = grid->getDuration() / (cols * rows);
		rational t (0, 1);

		SRelativeTime2GraphicMapping t2g_mapping = TMapping<rational,1, float,2>::create();

		if (grid->getOrder() == IGrid::kLeftRight) {
			for (int i=0; i< rows; i++) {
				for (int j=0; j< cols; j++) {
					RelativeTimeSegment timeseg (t, t+d);
					GraphicSegment	graphseg (left, top, left+w, top+h);
					t2g_mapping->add ( timeseg, graphseg );
					t += d;
					left += w + xborder*2;
				}
				top += h + yborder*2;
				left = -1 + xborder;
			}
		}
		else {
			for (int i=0; i< cols; i++) {
				for (int j=0; j< rows; j++) {
					RelativeTimeSegment timeseg (t, t+d);
					GraphicSegment	graphseg (left, top, left+w, top+h);
					t2g_mapping->add ( timeseg, graphseg );
					t += d;
					top += h + yborder*2;
				}
				left += w + xborder*2;
				top = -1 + xborder;
			}
		}
		grid->setMapping( "" , t2g_mapping);
		grid->fAutoMap = true;
	}
}


} // end namespoace
