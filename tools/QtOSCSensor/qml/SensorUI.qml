import QtQml 2.2
import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Rectangle {
	property real scale;
	
    width: Screen.desktopAvailableWidth; height: Screen.desktopAvailableHeight;
    color: "black"
	
	function pixelRatio() {
		return Screen.logicalPixelDensity * 25.4 / 72.
	}
	
	Row {
		id: header
		spacing: 10 * pixelRatio()
		x : 40 * pixelRatio()
		y: 40 * pixelRatio()
		Text {
			text: "Dest"
			color: "white"
		}
		TextInput {
			id: ip
			text: "192.168.1.21"
			font.pointSize: 14
			color: "white"
			selectByMouse : true
			mouseSelectionMode: TextInput.SelectWords
			selectedTextColor: "red"
			onEditingFinished: {
				if (length == 0) text = "192.168.1.21";
				focus: false;
				sensors.port (text);
			}
		}
		Text {
			text: "Port"
			color: "white"
		}

		TextInput {
			id: port
			text: "7001"
			font.pointSize: 14
			color: "white"
			selectByMouse : true
			mouseSelectionMode: TextInput.SelectWords
			selectedTextColor: "red"
			onEditingFinished: {
				if (length == 0) text = "7001";
				focus: false;
				sensors.destination (text);
			}
		}

	}    

    Component {
        id: sensorDelegate
        Item {
            width: parent.width; height: 45 * pixelRatio();
            Row {
                id: row1
        		spacing: 18 * pixelRatio()
               	Rectangle { 
                	id: r;
		            property bool on;
		            property bool available;
		            on : false;
		            available: true;
                	width: 30 * pixelRatio(); height: width; radius: 4 * pixelRatio();
                	color: "white"
                	border.color: "red";
					MouseArea {
						anchors.fill: parent
						onClicked: {
							if (r.available) {
								r.on = !r.on;
								if (r.on) { r.color = "green" } else { r.color = "white" };
								sensors.activate (number, r.on );
							}
               			}
                	}
               }
                Text { 
                	id: label
                	text: name ; 
                	anchors.verticalCenter: parent.verticalCenter 
					color: "white"
 					font.pointSize: 14
 					
               }
               Component.onCompleted: {
               		if (!sensors.available(number)) {
               			label.color="grey";
               			r.color="grey";
               			r.available = false;
               		}
               }
            }
        }
    }

    ListView {
    	id: list
        anchors.topMargin: 80 * pixelRatio()
        anchors.bottomMargin: 80 * pixelRatio()
        anchors.leftMargin: 40 * pixelRatio()
        anchors.fill: parent
        model: SensorsList {}
        delegate: sensorDelegate
        focus: true
    }

	 Button {
    	anchors.top: list.bottom
        anchors.horizontalCenter : parent.horizontalCenter
	 	text: "Quit"
		onClicked: Qt.quit()
	 }
}
