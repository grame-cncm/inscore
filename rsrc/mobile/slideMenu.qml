import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
//import "./"

Item {
    id: root

	function menuwidth(w, h) {
		return ((w > h) ? h : w) / 2;
	}
	
    property string version: ""
    signal switchToPanel(string name)

    width: menuwidth(Screen.desktopAvailableWidth, Screen.desktopAvailableHeight);
	height: Screen.desktopAvailableHeight;

    Rectangle{
        id: slidePanel

        anchors.fill: parent
        color: "white"

        // --------------- HEADER  ----------------
		SlideMenuHeader {
			version: root.version
			id : header
		}

        // ------------  MENU  --------------------

        Rectangle{
            id: menuPanel

            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right


            Rectangle{
                id: headerShadow
                height: 40

                gradient: Gradient {
                    GradientStop {position: 0.00; color: "#66363636"}
                    GradientStop {position: 0.33; color: "#33363636"}
                    GradientStop {position: 1.00; color: "#00363636"}
                }

                anchors.top:parent.top
                anchors.left: parent.left
                anchors.right: parent.right
            }

            ScrollView{
                horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                anchors.fill: parent

                Column{
                    spacing: 2
                    width: menuPanel.width

                    Item{height: 20; width:parent.width}

                    SectionSeparator{
                        title: "Scenes"
                        visible: contextObject.sceneList.length
                    }
                    Repeater{
                        model: contextObject.sceneList
                        SlideMenuItem{
                            text: modelData
                            onClicked: { 
                            	contextObject.hideMenu();
                            	inscore.postMessage(modelData, "foreground");
                            }
                            first: !index
                        }
                    }

                    SectionSeparator{
                        title: "Tools"
                        visible: contextObject.panelList.length
                    }
                    Repeater{
                        model: contextObject.panelList
                        SlideMenuItem{
                            text: modelData
                            onClicked: root.switchToPanel(modelData)
                            first: !index
                        }
                    }
                    SlideMenuItem{
                    	property bool log: false;
						text: "Show log"
						onClicked: {
							log = !log;
							if (log) 	text = "Hide log"
							else 		text = "Show log"
							inscore.postMessage("/ITL/log", "show", log)
						}
						first: false
                    }
                    SlideMenuItem{
						text: "Quit"
						onClicked: inscore.postMessage("/ITL", "quit")
						first: false
                    }

                    move: Transition {
						NumberAnimation { properties: "x,y"; duration: 300 }
                    }
                }
            }
        }
    }
}
