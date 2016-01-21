import QtQuick 2.0
import QtQuick.Window 2.0
import "global.js" as Size


Item {
    id: root
    height:  Size.toPixel(5.8)//Screen.pixelDensity * 5;
//    height: 40;
    anchors.left: parent.left
    anchors.right: parent.right

    property alias text: label.text
    property alias icon: iconImage.source
    property bool first: false;
    signal clicked;

    Rectangle{
        id: separator
//        visible: false;
        visible: !first;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        height: 1
        color: "#eeeeee"
    }

    Rectangle{
        id: button
        color: "white"
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: first?parent.top:separator.bottom;
        anchors.topMargin: first?0:2;
        anchors.bottom: parent.bottom;

        Image{
            id: iconImage
            anchors.left: parent.left;
            anchors.leftMargin: root.height*0.9;
            anchors.verticalCenter: parent.verticalCenter

            width:  root.height*0.7;
            height: root.height*0.7;

            source: ""
            visible: source!="";
        }

        Text{
            id: label
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: root.height*1.8;
            color: "#3a3a3a"
//            font.pointSize:  14;
            font.pixelSize: root.height*0.5;
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
