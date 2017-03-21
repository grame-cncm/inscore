import QtQuick 2.0
import Qt.labs.folderlistmodel 2.1

Rectangle {
	width: 200; height: 400
	Text { 
		id: folder
		x : 10
		text: "scripts" 
	}
	Rectangle {
		id: sep
		anchors.top: folder.bottom
		width: parent.width
		height: 3
		color: "#eeeeee"
	}
	
	ListView {
		anchors.top: sep.bottom
		anchors.bottom: parent.bottom
		x: 10;

		FolderListModel {
			id: folderModel
			nameFilters: ["*.inscore","*.ibundle"] 
			rootFolder : "file:///Users/fober/src/INScore/git/scripts"
			folder : "file:///Users/fober/src/INScore/git/"+folder.text
			showDirs : true
			showDirsFirst : true
			showDotAndDotDot : true;
			showFiles : true
		}

		Component{
			id: fileDelegate


			Text{ 
				anchors.left: itemIcon.right;
//				anchors.fill: parent;
				text: fileName 
				MouseArea {
					anchors.fill: parent;
		            onClicked: {
   		 	            if (fileIsDir) {
   		 	            	if (fileName === "..") {
   		 	            		folder.text = folder.text.slice(0, folder.text.lastIndexOf("/"));
   		 	            	}
   		 	            	else if (fileName != ".") {
   		 	            		folder.text = folder.text + "/" + fileName;
   		 	            	}
   		 	            }
    		        }
				}
			}
		}

		model: folderModel
		delegate: fileDelegate
	}
}