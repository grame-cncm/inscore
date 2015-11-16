import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Rectangle {
    width: Screen.desktopAvailableWidth; height: Screen.desktopAvailableHeight;
    color: "black"

	function pixelRatio() {
		return Screen.logicalPixelDensity * 25.4 / 72.
	}
    
    Rectangle {
        id: rect
        width: 280 * pixelRatio(); height: 60 * pixelRatio(); anchors.centerIn: parent
        color: "lightgrey"
        antialiasing: true
		radius: 3;
     }
     
	Text { 
		text: "Initialization failed. 
Check your network connection!" ; 
		anchors.centerIn: parent
		color: "red"
		font.pointSize: 18
	}
	Button {
    	anchors.bottom: parent.bottom
    	anchors.bottomMargin: 20
        anchors.horizontalCenter : parent.horizontalCenter
	 	text: "Quit"
		onClicked: Qt.quit()
	}
}