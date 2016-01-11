#ifndef HEADER_H
#define HEADER_H

#include <QQuickWidget>

namespace inscore{

class Header : public QQuickWidget
{
	Q_OBJECT
public:
	explicit Header(QWidget *parent = 0);

signals:
	void nextPanel();
	void previousPanel();
	void switchToPanel(QString name);
	void popupMenu();

public slots:
	void headerNameChanged(QString newTitle, bool isFirst, bool isLast);
	void panelNameListChanged(QStringList nameList);

protected:

	///Workaround a QQmlWidget bug where the qml item is resize with a wrong height
	///when showing the header without triggering a resizeEvent() (for exemple when exiting fullscreen mode)
	///This subclass of showEvent can be removed if the qt bug is fixed...
	void showEvent(QShowEvent *e);
};

}//end namespace

#endif // HEADER_H
