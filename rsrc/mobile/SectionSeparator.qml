import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Item {

    property alias title: label.text

    anchors.left: parent.left
    anchors.right: parent.right
    height: Screen.pixelDensity * 7

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
        font.pixelSize: Screen.pixelDensity* 4
        font.letterSpacing: Screen.pixelDensity/2
        font.capitalization: Font.SmallCaps
        font.bold: true;
        color: "#474646"
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -font.pixelSize/6

        anchors.left: line1.right
        anchors.leftMargin: text!=""? 2 : 0
    }

    Rectangle{
        height: 1;
        color: "#474545"
        opacity: 0.5
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: label.right;
        anchors.leftMargin: label.text!=""? 2 : 0
        anchors.right: parent.right;
        anchors.rightMargin: 4
    }
}
