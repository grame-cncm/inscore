import QtQuick 2.3
import QtQuick.Controls 1.4

Item{
    id: root;

    property string title: "Header"
    property var titles;
    property bool isLast: true
    property bool isFirst: true

    signal nextPanel();
    signal previousPanel();
    signal switchToPanel(string newPanelName);
    signal popupMenu();

    Rectangle{
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ddc7c7"
            }

            GradientStop {
                position: 1
                color: "#ae9f9f"
            }
        }
    }

    Text {
        id: panelNameLabel
        anchors.centerIn: parent;
        color: "#520000"
        text: root.title
        font.family: "Courier"
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: root.height*.7

        MouseArea{
            anchors.fill: parent
            onClicked: panelList.popup()
        }
    }

    Image{
        id: menu
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        width: height
        source: "qrc:///INScoreViewer.png"

        MouseArea{
            anchors.fill: parent
            onClicked: root.popupMenu()
        }
    }


//    Text{
//        id: previous
//        anchors.left: parent.left;
//        anchors.verticalCenter: parent.verticalCenter;

//        text: " < ";
//        color: "#520000"
//        font.pixelSize: root.height*.7
//        horizontalAlignment: Text.AlignLeft;
//        verticalAlignment: Text.AlignVCenter;

//        visible: !root.isFirst;
//        MouseArea{
//            anchors.fill: parent;
//            onClicked: root.previousPanel();
//        }
//    }

//    Text{
//        id: next
//        anchors.right: parent.right;
//        anchors.verticalCenter: parent.verticalCenter;

//        text: " > ";
//        color: "#520000"
//        font.pixelSize: root.height*.7
//        horizontalAlignment: Text.AlignRight;
//        verticalAlignment: Text.AlignVCenter;

//        visible: !root.isLast;

//        MouseArea{
//            anchors.fill: parent;
//            onClicked: root.nextPanel();
//        }
//    }

}
