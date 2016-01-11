#include "Header.h"
#include <QtQuick>
#include <QtQml>
#include <QtCore>

namespace inscore {


Header::Header(QWidget *parent) : QQuickWidget(parent)
{
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	setSource(QUrl("qrc:///qml/header.qml"));

	connect(rootObject(), SIGNAL(nextPanel()), this, SIGNAL(nextPanel()));
	connect(rootObject(), SIGNAL(previousPanel()), this, SIGNAL(previousPanel()));
	connect(rootObject(), SIGNAL(switchToPanel(QString)), this, SIGNAL(switchToPanel(QString)));
	connect(rootObject(), SIGNAL(popupMenu()), this, SIGNAL(popupMenu()));

	QStringList l;
	rootObject()->setProperty("titles", QVariant::fromValue(l));
}

void Header::headerNameChanged(QString newTitle, bool isFirst, bool isLast)
{
	rootObject()->setProperty("title", newTitle);
	rootObject()->setProperty("isFirst", isFirst);
	rootObject()->setProperty("isLast", isLast);
}

void Header::panelNameListChanged(QStringList nameList)
{
	rootObject()->setProperty("titles", QVariant::fromValue(nameList));
}

void Header::showEvent(QShowEvent *e)
{
	QQuickWidget::showEvent(e);

	///Workaround a QQmlWidget bug where the qml item is resize with a wrong height
	///when showing the header without triggering a resizeEvent() (for exemple when exiting fullscreen mode)
	///This subclass of showEvent can be removed if the qt bug is fixed...
	if(isVisible()){
		QTimer::singleShot(10, [this](){
			int h = height();
			setFixedHeight(h+1);
			setFixedHeight(h);
		});
	}
}

}//end namespace

