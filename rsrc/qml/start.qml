import QtQuick 2.0
import QtQuick.Window 2.2

Rectangle {
//    width: Screen.desktopAvailableWidth; height: Screen.desktopAvailableHeight;
    width: 420; height: 600;
    color: "black"

    function timeChanged() {
        var r = i.opacity;
        if ((r < 0.75) || (r >= 1.)) 
        	i.dir = -i.dir;
        i.opacity = r + i.dir;
    }

	function pixelRatio() {
		return Screen.logicalPixelDensity * 25.4 / 72.
	}

	Image {
		id: i
		property real dir;
		dir : -0.005;
		width: parent.width/2
		fillMode: Image.PreserveAspectFit
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		source: "INScoreViewer.png"
	}	
}