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

}//end namespace

