import QtQuick 2.0
import "global.js" as Size

// --------------- HEADER  ----------------
Rectangle{
    id: root
    property string version: ""
    signal clicked;

	anchors.left: parent.left
	anchors.right: parent.right
	anchors.top: parent.top
    height: Size.toPixel(Size.headerPointHeight)
	color: "#ffffff"

	Image{
		id: headerLogo
		source: "qrc:///INScoreViewer.png"
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.left: parent.left
		anchors.margins: 5
		width: height
	}

	Text{
		id: labelINScore
		text: "INScore"
		font.family: "Verdana"
		color: "#464646"
		anchors.left: headerLogo.right
        anchors.leftMargin: Size.toPixel(3)
		anchors.top: parent.top
        anchors.topMargin: Size.headerPointHeight/5
		font.weight: Font.Bold
        font.pixelSize: Size.toPixel(Size.headerPointHeight/2);
	}
	Text{
		text: "Version " + version
		color: labelINScore.color
		anchors.left: labelINScore.left
		anchors.top: labelINScore.bottom
        font.pixelSize:  Size.toPixel(Size.headerPointHeight/4);
	}

    MouseArea{
        anchors.fill: parent
        onClicked: {
            root.clicked();
        }
    }
}
