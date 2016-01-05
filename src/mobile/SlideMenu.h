#ifndef SLIDEMENU_H
#define SLIDEMENU_H

#include <QtQuickWidgets>
#include <QtWidgets>

#define WIDTH 0.8
namespace inscore {


class SlideMenu : public QFrame
{
	Q_OBJECT

	Q_PROPERTY(float opacity READ opacity WRITE setOpacity)
	Q_PROPERTY(QVariant sceneList READ sceneList NOTIFY sceneListChanged)
	Q_PROPERTY(QVariant panelList READ panelList NOTIFY panelListChanged)

	QParallelAnimationGroup fAnimIn, fAnimOut;
	QPropertyAnimation* posOut;
	float fOpacity;

	QQuickWidget* fMenu;
	QStringList fSceneList, fPanelList;

public:
	explicit SlideMenu(QWidget *parent = 0);

	QStringList sceneList() const;
	QStringList panelList() const;

signals:
	void sceneListChanged();
	void panelListChanged();
	void switchToPanel(QString panelName);

public slots:
	void popupMenu();
	void hideMenu();

	float opacity(){return fOpacity;}
	void setOpacity(float alpha);

	void panelListChanged(QStringList panelList, int sceneCount);

protected:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *);

	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *){}
	void mouseMoveEvent(QMouseEvent *){}

	void resizeEvent(QResizeEvent *);
};

}//end namespace
#endif // SLIDEMENU_H
