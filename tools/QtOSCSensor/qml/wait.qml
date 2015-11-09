import QtQuick 2.0
import QtQuick.Window 2.2

Rectangle {
    width: Screen.desktopAvailableWidth; height: Screen.desktopAvailableHeight;
    color: "black"

    function timeChanged() {
        var r = rect.rotation;
        rect.rotation = r+1;
    }

	function pixelRatio() {
		return Screen.logicalPixelDensity * 25.4 / 72.
	}
    
    Rectangle {
        id: rect
        width: 150 * pixelRatio(); height: width; anchors.centerIn: parent
        color: "red"
        antialiasing: true
		gradient: Gradient {
			GradientStop { position: 0.0; color: "lightblue" }
			GradientStop { position: 0.2; color: "blue" }
			GradientStop { position: 0.5; color: "orange" }
			GradientStop { position: 0.8; color: "blue" }
			GradientStop { position: 1.0; color: "lightblue" }
		}
		radius: width/2
     }
     
	Text { 
		text: "Wait while loading" ; 
		anchors.centerIn: parent
		color: "lightgrey"
		font.pointSize: 16
	}

    Timer {
        interval: 6; running: true; repeat: true;
        onTriggered: timeChanged()
    }
}