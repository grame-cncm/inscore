
#ifndef GDrawArea_h
#define GDrawArea_h

#include <vector>
#include <QFrame>
#include <QObject>

class gfollower;

class GDrawArea : public QFrame
{
	Q_OBJECT
	
	std::vector<QPointF>	fPoints;
	bool					fCollect;
	
	public:
		explicit GDrawArea(QWidget * parent = 0, Qt::WindowFlags f = 0) : QFrame (parent, f), fCollect(false) {}
				~GDrawArea() {}

		void	mouseMoveEvent(QMouseEvent * event);
		void	mousePressEvent(QMouseEvent * event);
		void	mouseReleaseEvent(QMouseEvent * event);

		void	collect()		{ fCollect = true; }
		void	clear();
		void	paintEvent(QPaintEvent * event);
		void	point(QPoint p);


 signals:
		void	stopDraw();
		void	data(float, float);
};

#endif
