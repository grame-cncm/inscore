

#include <QDebug> 
#include <QMouseEvent> 
#include <QPainter> 

#include "gdrawarea.h"
#include "gfollower.h"

void GDrawArea::mouseMoveEvent(QMouseEvent * event)
{
	if (!fCollect) return;
	point (event->pos());
}

void GDrawArea::mousePressEvent(QMouseEvent * event)
{
	if (!fCollect) return;
	fPoints.clear();
	point (event->pos());
}

void GDrawArea::mouseReleaseEvent(QMouseEvent * event)
{
	if (!fCollect) return;
	point (event->pos());
	fCollect = false;
	emit stopDraw();
}

void GDrawArea::point(QPoint p)
{
	if (!fCollect) return;
	if (!rect().contains (p.x(), p.y())) return;

	fPoints.push_back(p);
	repaint();
	QSize s = size();
	emit data(p.x()/float(s.width()), p.y()/float(s.height()));
};

void GDrawArea::clear()
{
	fPoints.clear();
	repaint();
}

void GDrawArea::paintEvent(QPaintEvent * )
{
	QPainter painter (this);
	painter.setBrush(Qt::white);
	painter.drawRect (rect());
	painter.setPen(Qt::black);
	unsigned long n = fPoints.size() ? fPoints.size() - 1 : 0;
	for (unsigned long i=0; i < n; i++) {
		painter.drawLine(fPoints[i], fPoints[i+1]);
	}
}
