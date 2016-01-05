import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import "./"

Item {
    id: root

    property string version: ""
    signal switchToPanel(string name)

    width: 720
    height: 1280


    Rectangle{
        id: slidePanel

        anchors.fill: parent

        color: "white"

        // --------------- HEADER  ----------------
        Rectangle{
            id: header
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: Math.min(root.height, root.width)/6

            color: "#ffffff"

            Image{
                id: headerLogo
                source: "qrc:///INScoreViewer.png"
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: height
            }

            Text{
                id: labelINScore
                text: "INScore"
                font.family: "Verdana"
                color: "#464646"
                anchors.left: headerLogo.right
                anchors.leftMargin: 40
                font.pixelSize: parent.height*.6
            }
            Text{
                text: "Version " + root.version
                color: labelINScore.color
                anchors.left: labelINScore.left
                anchors.top: labelINScore.bottom
                font.pixelSize: labelINScore.font.pixelSize*.3
            }
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
                            onClicked: root.switchToPanel(modelData)
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

                    move: Transition {
                              NumberAnimation { properties: "x,y"; duration: 1000 }
                    }
                }
            }

        }
    }

}
