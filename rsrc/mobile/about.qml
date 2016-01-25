import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Item {
    id: root
	
    property string version: ""
    property string qtversion: ""
    property string guidoversion: ""
    property string src: "../"
    property string ip: ""
//    property string src: "qrc:///"
    property int vsize: 14

    width: Screen.desktopAvailableWidth
	height: Screen.desktopAvailableHeight

    Rectangle{
        anchors.fill: parent
        color: "snow"

            Image{
                id: icon
                source: root.src + "INScoreViewer.png"
                anchors.horizontalCenter: parent.horizontalCenter
        		y: parent.height/2 - height
        		sourceSize.width: 240
            }
			DropShadow {
				anchors.fill: icon
				horizontalOffset: 5
				verticalOffset: 5
				radius: 16.0
				samples: 16
				color: "#80000000"
				source: icon
			}
            Text{
            	id: versions
                text: "INScore v." + root.version
                + "\nUsing Qt v." + root.qtversion 
                + "\nUsing Guido Engine v." + root.guidoversion
                +  "\nIP: " + ip
                color: "#464646"
                anchors.left: icon.left
                anchors.leftMargin: 18
                anchors.top: icon.bottom
                anchors.topMargin: 10
                font.pointSize: root.vsize
            }
            Text{
            	id: desc
                text: "An environment for the design of\nlive augmented music scores"
                color: "indigo"
                anchors.horizontalCenter: icon.horizontalCenter
                anchors.top: versions.bottom
                horizontalAlignment: Text.AlignHCenter
                anchors.topMargin: 20
                font.pointSize: 20
            }
			DropShadow {
				anchors.fill: desc
				horizontalOffset: 3
				verticalOffset: 3
				radius: 8.0
				samples: 16
				color: "#80000000"
				source: desc
			}
            Image{
                source: root.src + "grame.png"
                anchors.horizontalCenter: icon.horizontalCenter
                anchors.top: desc.bottom
                anchors.topMargin: 20
        		sourceSize.width: 150
            }
    }
}
