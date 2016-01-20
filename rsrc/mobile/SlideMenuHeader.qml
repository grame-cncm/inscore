import QtQuick 2.0

// --------------- HEADER  ----------------
Rectangle{
    id: root
    property string version: ""
    signal clicked;

	anchors.left: parent.left
	anchors.right: parent.right
	anchors.top: parent.top
	height: 54
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
		anchors.leftMargin: 40
		anchors.top: parent.top
		anchors.topMargin: 4
		font.weight: Font.Bold
		font.pointSize: 18
	}
	Text{
		text: "Version " + version
		color: labelINScore.color
		anchors.left: labelINScore.left
		anchors.top: labelINScore.bottom
		font.pointSize: 10
	}

    MouseArea{
        anchors.fill: parent
        onClicked: {
            root.clicked();
        }
    }
}
