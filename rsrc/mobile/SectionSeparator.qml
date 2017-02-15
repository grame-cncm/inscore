import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Item {

    property alias title: label.text
    property int textMargin: 6

    anchors.left: parent.left
    anchors.right: parent.right
    height: Screen.pixelDensity * 4
//    height: Screen.pixelDensity * 5

    Rectangle{
        id: line1
        height: 1;
        color: "#474646"
        opacity: 0.5
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: parent.left
        anchors.leftMargin: 4
        width: 50
    }

    Text{
        id: label
        text: ""
        verticalAlignment: Text.AlignVCenter
        font.letterSpacing: 1
        font.pointSize: 15
//        font.pointSize: 16
//        font.letterSpacing: Screen.pixelDensity/2
        font.capitalization: Font.SmallCaps
        font.bold: true;
        color: "#474646"
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -font.pixelSize/6

        anchors.left: line1.right
        anchors.leftMargin: text!=""? textMargin : 0
    }

    Rectangle{
        height: 1;
        color: "#474545"
        opacity: 0.5
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: label.right;
        anchors.leftMargin: label.text!=""? textMargin : 0
        anchors.right: parent.right;
        anchors.rightMargin: 4
    }
}
