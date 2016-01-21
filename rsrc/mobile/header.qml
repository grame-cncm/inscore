import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import "global.js" as Size

Item{
    id: root;

    property string title: ""
    property bool isLast: true
    property bool isFirst: true

    signal popupMenu();

	width: Screen.desktopAvailableWidth;
    height: Size.toPixel(Size.headerPointHeight)

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
        font.pixelSize: root.height * 0.6
    }

    Image{
        id: menu
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        width: height
        source: "qrc:///INScoreViewer.png"
    }

    MouseArea{
        anchors.fill: parent
        onClicked: root.popupMenu()
    }
}
