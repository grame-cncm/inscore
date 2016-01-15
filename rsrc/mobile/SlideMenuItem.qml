import QtQuick 2.0
import QtQuick.Window 2.0

Item {
    id: root
//    height: Screen.pixelDensity * 7;
    height: 40;
    anchors.left: parent.left
    anchors.right: parent.right

    property alias text: label.text
    property bool first: false;
    signal clicked;

    Rectangle{
        id: separator
        visible: false;
//        visible: !first;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        height: 1
        color: "#999999"
    }

    Rectangle{
        id: button
        color: "white"
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: first?parent.top:separator.bottom;
        anchors.topMargin: first?0:2;
        anchors.bottom: parent.bottom;

        Text{
            id: label
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: Screen.pixelDensity*7;
            color: "#3a3a3a"
//            font.pixelSize:  Screen.pixelDensity * 4;
            font.pointSize:  14;
            font.capitalization: Font.SmallCaps
            text: "";
        }
        MouseArea{
            anchors.fill: parent;
            onPressed: {
                button.state = "pressed"
            }
            onCanceled: {
                button.state = ""
            }

            onReleased: {
                button.state = ""
            }
            onClicked: {
                root.clicked();
            }
        }

        states: [
            State{
                name: "pressed"
                PropertyChanges { target: button; color: "#c0c0c0" }
            }
        ]
    }
}
