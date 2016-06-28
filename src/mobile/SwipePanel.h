/*

  INScore Project

  Copyright (C) 2015  Grame

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

#ifndef CENTRALPANEL_H
#define CENTRALPANEL_H

#include <QWidget>
#include <QtQuickWidgets>

namespace inscore {

class SwipeEventFilter;

/*!
 * \brief This class handle a QtWidgets version of the qml swipable components
 * Panels can be both QWidget or QML files
 */
class SwipePanel : public QWidget
{	
	Q_OBJECT

	QList< QPair<QString, QWidget*> > fPanelList;
	int fSceneCount;
	QParallelAnimationGroup fAnim;
	SwipeEventFilter* fSwipeFilter;

	int fCurrentPanelID;
	int fFullScreenPanel;
	int fNextPanelID;

public:
	explicit SwipePanel(QWidget *parent = 0);

	/*!
	 * \brief addPanel Add a panel to the list
	 * \param name name of the panel
	 * \param panel the panel widget, the central panel own this object
	 */
	void addPanel(QString name, QWidget* panel, bool asScene=false);

	/*!
	 * \brief addScene Overload addPanel to add scenes before other panels
	 * \param name scene name
	 * \param panel scene view
	 */
	void addScene(QString name, QWidget* panel);

	/*!
	 * \brief Overload addPanel to handle qmlFiles
	 * \param name the panel name
	 * \param qmlFile the qml file to view
	 * \warning the qml root object need to inherit QtQuick item and no resize instruction should be given to it
	 * (resizing is automatically handle by the panel)
	 */
	void addQmlPanel(QString name, QUrl qmlFile);

	/*!
	 * \brief setPanel switch to a panel without animation
	 * \param name panel name
	 * \return true if the panel exists, false if not
	 */
	bool setPanel(QString name);

	/*!
	 * \brief setFullScreen Raise a panel to full screen
	 * \param name of the panel
	 * \param fullscreen weither the panel should be fullscreen or not
	 */
	void setFullScreen(QString name, bool fullscreen);

	/*!
	 * \brief removePanel from the list
	 * \param name of the widget to delete
	 * \param deleteWidget choose weither the panel widget should be deleted (true by default)
	 */
	bool removePanel(QString name, bool deleteWidget = true);

	/*!
	 * \brief removePanel from the list (the panel widget is deleted)
	 * \param name of the widget to delete
	 */
	bool removePanel(std::string name, bool deleteWidget = true) {return removePanel(QString::fromStdString(name), deleteWidget);}

	/*!
	 * \brief isFirstPanel
	 * \return True if the current panel is the first
	 */
	bool isFirstPanel();

	/*!
	 * \brief isLastPanel
	 * \return True if the current panel is the last
	 */
	bool isLastPanel();

	/*!
	 * \brief panelList
	 * \return the names of all the panels
	 */
	QStringList panelList();

	/*!
	 * \brief sceneList
	 * \return the names of all the scenes
	 */
	QStringList sceneList();

	/*!
	 * \brief currentName
	 * \return the name of the current panel
	 */
	inline QString currentName() {return fPanelList.at(fCurrentPanelID).first;}

	bool event(QEvent *);

	SwipeEventFilter* swipeEventFilter() {return fSwipeFilter;}

signals:
	/*!
	 * \brief panelListChanged is emitted when panels are added or removed from the panel list
	 * \param the names of all the panels
	 * \param the numbre of Inscore scene at the beginning of the panel list
	 */
	void panelListChanged(QStringList newPanelList, int sceneCount);

	/*!
	 * \brief sceneListChanged is emitted when scenes are added or removed from the panel list
	 * \param the names of all the scenes
	 */
	void sceneListChanged(QStringList newSceneList);

	/*!
	 * \brief currentPanelChanged is emitted when the current panel changes or if its position (first or last) does
	 * \param newPanelName the current panel name
	 * \param isFirst is the current panel the first in the list
	 * \param isLast is the current panel the last in the list
	 */
	void currentPanelChanged(QString newPanelName, bool isFirst, bool isLast);

public slots:

	/*!
	 * \brief slide to the next panel
	 * \return true the animation is possible, false otherwise
	 */
	bool swipeRight();

	/*!
	 * \brief slide to the previous panel
	 * \return true the animation is possible, false otherwise
	 */
	bool swipeLeft();

	/*!
	 * \brief slide to a specific panel
	 * \param name the name of the destination panel
	 * \return true if the panel exist, false otherwise
	 */
	bool switchToPanel(QString name);

	/*!
	 * \brief slide to a specific panel
	 * \param name the name of the destination panel
	 * \return true if the panel exist, false otherwise
	 */
	bool switchToPanel(std::string name) {return switchToPanel(QString::fromStdString(name));}

private slots:
	void animationEnded();

protected:
	virtual void resizeEvent(QResizeEvent *e);

private:
	inline void resizeWidgetToPanel(QWidget* w);
	int panelID( QString name);

	bool switchToPanel(int panelID);
	void setPanel(int panelID);
	void animateSlide( bool fromLeft);
	inline void emitCurrentPanelChanged();
	inline void emitPanelListChanged();

	inline QWidget* currentWidget() {return fCurrentPanelID!=-1?fPanelList.at(fCurrentPanelID).second:0;}
};


class SwipeEventFilter: public QObject{
Q_OBJECT

	int startX, startY;
	bool swipePossible=false;
	QTimer time;

public:
	int minX=350, maxY=250, maxT=500;

	SwipeEventFilter(QObject* parent=0): QObject(parent){connect(&time, &QTimer::timeout, [this]{swipePossible=false; time.setSingleShot(true);} );}
	bool eventFilter(QObject *o, QEvent *e);

signals:
	void swipeLeft();
	void swipeRight();
};

}//end namespace

#endif // CENTRALPANEL_H
