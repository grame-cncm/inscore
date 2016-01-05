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
};

}//end namespace

#endif // HEADER_H
