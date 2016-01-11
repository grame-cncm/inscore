#include "SwipePanel.h"
#include <QtQuickWidgets>

namespace inscore{

SwipePanel::SwipePanel(QWidget *parent) : QWidget(parent)
{
	fCurrentPanelID = -1;
	fNextPanelID = -1;
	fFullScreenPanel = -1;
	fSceneCount = 0;

	fSwipeFilter = new SwipeEventFilter(this);
	installEventFilter(fSwipeFilter);

	setMinimumHeight(500);
	setMinimumWidth(200);
	setAttribute(Qt::WA_AcceptTouchEvents);

	connect(&fAnim, SIGNAL(finished()), this, SLOT(animationEnded()));
	connect(fSwipeFilter, SIGNAL(swipeLeft()), this, SLOT(nextPanel()));
	connect(fSwipeFilter, SIGNAL(swipeRight()), this, SLOT(previousPanel()));
}

void SwipePanel::addPanel(QString name, QWidget *panel)
{
	if(panelID(name)>=0)
		return;

	panel->setParent(this);
	panel->setAttribute(Qt::WA_AcceptTouchEvents);
	panel->hide();

	QPair<QString, QWidget*> p(name, panel);

	fPanelList.append(p);

	emitPanelListChanged();

	if(fPanelList.size()==1){
		//If the panel is the only panel (first added), automatically show it as the default panel
		setPanel(0);
	}else if(fCurrentPanelID == fPanelList.size()-2){
		//If the current panel id was the last (and not anymore) update isLast
		emitCurrentPanelChanged();
	}
}

void SwipePanel::addScene(QString name, QWidget *panel)
{
	if(panelID(name)>=0)
		return;

	//Because we do not own scene panel, show signal are sometimes triggered outside of the SwipePanel,
	//to ensure a correct display, the scene widget is placed inside a frame that only the SwipePanel can show or hide
	QWidget* frame = new QWidget(this);
	QHBoxLayout* l = new QHBoxLayout(frame);
	l->addWidget(panel);
	l->setMargin(0);
	frame->setLayout(l);
	frame->setParent(this);
	frame->hide();
	connect(panel, SIGNAL(destroyed()), frame, SLOT(deleteLater()));

	QPair<QString, QWidget*> p(name, frame);
	fPanelList.insert(fSceneCount, p);

	if(fCurrentPanelID>=fSceneCount)
		fCurrentPanelID++;
	if(fNextPanelID>=fSceneCount)
		fNextPanelID++;
	fSceneCount++;

	emitPanelListChanged();
	if(receivers(SIGNAL(sceneListChanged(QStringList))))
		emit sceneListChanged(sceneList());

	if(fPanelList.size()==1){
		//If the panel is the only panel (first added), automatically show it as the default panel
		setPanel(0);
	}else if(fCurrentPanelID == fPanelList.size()-2){
		//If the current panel id was the last (and not anymore) update isLast
		emitCurrentPanelChanged();
	}
}

void SwipePanel::addQmlPanel(QString name, QUrl qmlFile)
{
	QQuickWidget* w = new QQuickWidget(this);
	w->setResizeMode(QQuickWidget::SizeRootObjectToView);
	w->setSource(qmlFile);
	addPanel(name, w);
}

bool SwipePanel::removePanel(QString name, bool deleteWidget)
{
	int id = panelID(name);

	if(id == -1)
		return false;

	if(fNextPanelID!=-1){
		if(fCurrentPanelID == id)
			setPanel(fNextPanelID);
		else if(fNextPanelID == id)
			setPanel(fCurrentPanelID);
	}

	if(fCurrentPanelID == id){
		if(!isFirstPanel())
			setPanel(fCurrentPanelID-1);
		else if(!isLastPanel())
			setPanel(fCurrentPanelID+1);
		else
			setPanel(-1);
	}

	if(deleteWidget)
		fPanelList.at(id).second->deleteLater();
	else
		fPanelList.at(id).second->setParent(0);
	fPanelList.removeAt(id);

	if(id<fSceneCount){
		fSceneCount--;
		if(receivers(SIGNAL(sceneListChanged(QStringList))))
			emit sceneListChanged(sceneList());
	}

	if(fCurrentPanelID>id)
		fCurrentPanelID--;

	if(fNextPanelID>id)
		fNextPanelID--;

	emitPanelListChanged();

	if( (id==0 && isFirstPanel()) || (id==fPanelList.size()-1 && isLastPanel()) )
		emitCurrentPanelChanged();

	return true;
}

//__________________________________________________
bool SwipePanel::setPanel(QString name)
{
	int id = panelID(name);
	if(id==-1)
		return false;

	setPanel(id);
	return true;
}

void SwipePanel::setPanel(int panelID)
{

	if(fNextPanelID!=-1){
		fAnim.stop();
		fAnim.clear();
		fNextPanelID = -1;
	}

	if(panelID != fCurrentPanelID){
		//cleaning
		if(currentWidget()){
			currentWidget()->hide();
			currentWidget()->removeEventFilter(fSwipeFilter);
		}

		fCurrentPanelID = panelID;

		if(fCurrentPanelID >= fPanelList.size() || fCurrentPanelID < 0){
			fCurrentPanelID = -1;
		}else{
			currentWidget()->show();
			currentWidget()->installEventFilter(fSwipeFilter);
			currentWidget()->setGeometry(0,0,width(),height());
		}
		emitCurrentPanelChanged();
	}

}

void SwipePanel::setFullScreen(QString name, bool fullscreen)
{
	int id = panelID(name);
	if(id==-1)
		return;
	//ensure the fullscreen state of the panel changed
	if( fullscreen == (fFullScreenPanel == id))
		return;

	if(fNextPanelID!=-1){
		fAnim.stop();
		fAnim.clear();
		fNextPanelID = -1;
	}


	if(fFullScreenPanel!=-1){
		//remove the previous full screen panel

		QWidget* previousPanel = fPanelList.at(fFullScreenPanel).second;
		previousPanel->hide();
		previousPanel->setParent(this);
		fFullScreenPanel = -1;
	}else if(fullscreen){
		//setup the Swipe panel for fullscreen
		window()->hide();
		setPanel(-1);
	}

	if(fullscreen){
		//setup the new fullscreen panel
		fFullScreenPanel = id;
		QWidget* newPanel = fPanelList.at(fFullScreenPanel).second;
		newPanel->setParent(0);
		newPanel->showFullScreen();
	}else{
		//setup the swipe panel back from fullscreen
		window()->showMaximized();
		setPanel(id);
	}

}

//__________________________________________________
bool SwipePanel::isFirstPanel()
{
	return !fCurrentPanelID;
}

bool SwipePanel::isLastPanel()
{
	return fPanelList.size() <= fCurrentPanelID+1;
}

QStringList SwipePanel::panelList()
{
	QStringList l;
	for (int i = 0; i < fPanelList.size(); ++i)
		l<<fPanelList.at(i).first;

	return l;
}

QStringList SwipePanel::sceneList()
{
	QStringList l;
	for (int i = 0; i < fSceneCount; ++i)
		l<<fPanelList.at(i).first;

	return l;
}

//__________________________________________________
bool SwipePanel::nextPanel()
{

	return switchToPanel(fCurrentPanelID+1);
}

bool SwipePanel::previousPanel()
{
	return switchToPanel(fCurrentPanelID-1);
}

bool SwipePanel::switchToPanel(QString name)
{
	int id = panelID(name);
	return switchToPanel(id);
}

bool SwipePanel::switchToPanel(int panelID)
{
	if(fNextPanelID!=-1)
		return false;
	if(panelID<0 || panelID >= panelList().size())
		return false;
	if(fCurrentPanelID==panelID)
		return false;

	fNextPanelID = panelID;
	animateSlide(fNextPanelID>fCurrentPanelID);
	return true;
}


void SwipePanel::resizeEvent(QResizeEvent *e)
{

	int h = e->size().height();
	int w = e->size().width();

	if(currentWidget())
		currentWidget()->setGeometry(0,0, w, h);

	//If the animation is running compute the destination again
	if(fAnim.state()==QAbstractAnimation::Running && fAnim.animationCount()==2){
		QPropertyAnimation* animOut = qobject_cast<QPropertyAnimation*>(fAnim.animationAt(0));
		QPropertyAnimation* animIn = qobject_cast<QPropertyAnimation*>(fAnim.animationAt(1));
		bool fromLeft = animOut->endValue().toRect().x() < 0;
		animOut->setEndValue(QRect(w * (fromLeft?-1:1), 0, w, h));
		animIn->setEndValue(QRect(0,0,w,h));
	}

	fSwipeFilter->minX = qMin(w, h) / 2;
	fSwipeFilter->maxY = qMin(w, h) * 1/3;
}


//____________________________________________________
void SwipePanel::animateSlide( bool fromLeft)
{
	if(fNextPanelID==-1)
		return;

	fAnim.clear();

	QWidget* in = fPanelList.at(fNextPanelID).second;
	in->setGeometry(QRect(width() * (fromLeft?1:-1), 0, width(), height()));
	in->show();

	QPropertyAnimation *animOut = new QPropertyAnimation(currentWidget(), "geometry");
	QPropertyAnimation *animIn = new QPropertyAnimation(in, "geometry");
	animOut->setEndValue(QRect(width() * (fromLeft?-1:1), 0, width(), height()));
	animIn->setEndValue(QRect(0,0,width(),height()));

	animOut->setDuration(250);
	animIn->setDuration(250);

	fAnim.addAnimation(animOut);
	fAnim.addAnimation(animIn);

	fAnim.start();

	emitCurrentPanelChanged();
}

void SwipePanel::animationEnded()
{
	setPanel(fNextPanelID);
}

//____________________________________________________
int SwipePanel::panelID(QString name)
{
	for (int i = 0; i < fPanelList.size(); ++i) {
		if(fPanelList.at(i).first==name)
			return i;
	}
	return -1;
}

void SwipePanel::emitCurrentPanelChanged()
{
	if(fNextPanelID!=-1)
		emit currentPanelChanged(fPanelList.at(fNextPanelID).first, !fNextPanelID, fNextPanelID == fPanelList.size()-1);
	else if(fCurrentPanelID!=-1)
		emit currentPanelChanged(fPanelList.at(fCurrentPanelID).first, !fCurrentPanelID, fCurrentPanelID == fPanelList.size()-1);
	else
		emit currentPanelChanged("", true, true);
}

void SwipePanel::emitPanelListChanged()
{
	if(receivers(SIGNAL(panelListChanged(QStringList))) || receivers(SIGNAL(panelListChanged(QStringList, int))))
		emit panelListChanged(panelList(), fSceneCount);

}


bool SwipePanel::event(QEvent *e)
{
	if(e->type() == QEvent::TouchBegin || e->type()==QEvent::TouchEnd || e->type()==QEvent::TouchUpdate){
		e->accept();
		return true;
	}
	return QWidget::event(e);
}

//---------------------------------------------------
//___________________________________________________
bool SwipeEventFilter::eventFilter(QObject *o, QEvent *event)
{
	if(event->type() == QEvent::TouchBegin){
		QTouchEvent* e = static_cast<QTouchEvent*>(event);
		if(e->touchPoints().size()!=1 || swipePossible){
			//More than one touch point can't be a swipe
			int x = e->touchPoints().at(0).pos().x();
			int y = e->touchPoints().at(0).pos().y();
			if( abs(x-startX) > 10 && abs(y-startY) > 10){
				swipePossible = false;
				return false;
			}
		}

		//initiate a swipe detection
		startX = e->touchPoints().at(0).pos().x();
		startY = e->touchPoints().at(0).pos().y();
		event->accept();
		time.start(maxT);
		swipePossible = true;
		return false;
	}else if(swipePossible){
		//Then if a swipe detection has been initiated

		if(event->type()==QEvent::TouchEnd){
			QTouchEvent* e = static_cast<QTouchEvent*>(event);
			int x = e->touchPoints().at(0).pos().x();
			int y = e->touchPoints().at(0).pos().y();
			if( abs(x-startX) > minX && abs(y-startY) < maxY){
				//Swipe accepted!

				time.stop();
				swipePossible = false;

				if(x>startX)
					emit swipeRight();
				else
					emit swipeLeft();

				QApplication::sendEvent(o, new QTouchEvent(QEvent::TouchCancel, e->device(), e->modifiers(), e->touchPointStates(), e->touchPoints()) );
				return true;
			}
			swipePossible = false;
		}else if(event->type()==QEvent::TouchUpdate){
			//If the swipe go behond the maxY limit it's invalidated
			QTouchEvent* e = static_cast<QTouchEvent*>(event);
			int y = e->touchPoints().at(0).pos().y();
			if(abs(y-startY) > maxY)
				swipePossible = false;

		}else if(event->type()==QEvent::TouchCancel)
			swipePossible = false;

	}

	return false;
}


}//end namespace
