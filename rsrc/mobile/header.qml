import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import "global.js" as Size

Item{
    id: root;

    property alias title: panelNameLabel.text
    property bool isLast: true
    property bool isFirst: true

    signal popupMenu();

	width: Screen.desktopAvailableWidth;
    height: Size.toPixel(Size.headerPointHeight)

    Rectangle{
        id: background
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: separator.top
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#f8f4f0"
            }

            GradientStop {
                position: 1
                color: "#cfcecc"
            }
        }
    }

    Rectangle{
        id: separator
        height: 2;
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#adadb2"
    }

    Text {
        id: panelNameLabel
        anchors.centerIn: parent;
        color: "#424039"
        text: ""
        font.family: "Courier"
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 18
//        font.pixelSize: root.height * 0.6
    }

    Image{
        id: menu
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        anchors.leftMargin: Size.toPixel(2)
        width: height
        source: "qrc:///images/menuIco.png"
        smooth: true;
        opacity: 0.6;
    }

    SimpleTouchArea{
        anchors.fill: parent
        onClicked: root.popupMenu()
        onPressed: menu.opacity = 0.8;
        onReleased: menu.opacity = 0.6;
        onCanceled: menu.opacity = 0.6;
    }
}
