#include "SlideMenu.h"
#include "INScore.h"

namespace inscore {

SlideMenu::SlideMenu(QWidget *parent) : QFrame(parent)
{
	fMenu = new QQuickWidget(this);
	QStringList l;
	l<<"test"<<"test20";
	fMenu->rootContext()->setContextProperty("contextObject", this);
	fMenu->setSource(QUrl("qrc:///qml/slideMenu.qml"));
	fMenu->rootObject()->setProperty("version", QVariant::fromValue( QString::fromStdString(INScore::versionStr()) ));

	fMenu->setResizeMode(QQuickWidget::SizeRootObjectToView);
	connect(fMenu->rootObject(), SIGNAL(switchToPanel(QString)), this, SIGNAL(switchToPanel(QString)));
	connect(fMenu->rootObject(), SIGNAL(switchToPanel(QString)), this, SLOT(hideMenu()));

	fOpacity = 1;
	setOpacity(0);

	QPropertyAnimation *opacityIn  = new QPropertyAnimation(this, "opacity", this);
	QPropertyAnimation *opacityOut = new QPropertyAnimation(this, "opacity", this);
	opacityIn ->setEndValue(0.4);
	opacityOut->setEndValue(0);
	opacityIn ->setDuration(250);
	opacityOut->setDuration(250);

	QPropertyAnimation *posIn  = new QPropertyAnimation(fMenu, "pos", this);
	posOut = new QPropertyAnimation(fMenu, "pos", this);
	posIn ->setEndValue(QPoint(0,0));
	posOut->setEndValue(QPoint(-fMenu->width(),0));
	posIn ->setDuration(500);
	posOut->setDuration(500);
	posIn ->setEasingCurve(QEasingCurve::OutQuad);
	posOut->setEasingCurve(QEasingCurve::InQuad);

	fAnimIn.addAnimation(opacityIn);
	fAnimIn.addAnimation(posIn);
	fAnimOut.addAnimation(opacityOut);
	fAnimOut.addAnimation(posOut);

	connect(&fAnimOut, &QAbstractAnimation::finished, [this]{hide();});
	setAutoFillBackground(true);
	hide();
}

//_________________________________________________
QStringList SlideMenu::sceneList() const
{
	return fSceneList;
}

QStringList SlideMenu::panelList() const
{
	return fPanelList;
}

//_________________________________________________
void SlideMenu::resizeEvent(QResizeEvent *)
{
	int menuWidth = width()*WIDTH;

	fMenu->resize(menuWidth, height());

	if(!isVisible())
		fMenu->move(-menuWidth, 0);

	posOut->setEndValue(QPoint(-menuWidth,0));
}

//_________________________________________________
void SlideMenu::popupMenu()
{
	show();
	fAnimIn.start();
}

void SlideMenu::hideMenu()
{
	fAnimOut.start();
}

void SlideMenu::setOpacity(float alpha)
{
	if(qAbs(alpha-fOpacity) < 0.05)
		return;

	if(alpha<0 && alpha>1)
		return;

	fOpacity = alpha;

	setPalette(QColor(0,0,0,255*fOpacity));
}

void SlideMenu::panelListChanged(QStringList panelList, int sceneCount)
{
	fSceneList = panelList.mid(0, sceneCount);
	fPanelList = panelList.mid(sceneCount);
	emit sceneListChanged();
	emit panelListChanged();
}


//_________________________________________________
void SlideMenu::keyPressEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_Back) {
		hideMenu();
		e->accept();
		return;
	}

	QWidget::keyPressEvent(e);
}

void SlideMenu::keyReleaseEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_Back){
		e->accept();
		return;
	}

	QWidget::keyReleaseEvent(e);
}

void SlideMenu::mousePressEvent(QMouseEvent *e)
{
	if(e->pos().x() > width()*WIDTH){
		e->accept();
		hideMenu();
	}
}

}//end namespace

