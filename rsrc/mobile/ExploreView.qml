import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import Qt.labs.folderlistmodel 2.1

Item {
    id: root;
    anchors.fill: parent;

    property ListModel path: ListModel{}

    function setRootPath(rootName, rootPath){
        path.clear();
        folderView.currentView.visible = false;

        root.openPath(rootName, rootPath);
    }

    function openPath(folderName, folderPath){

        open(folderName, folderModelFromPath(folderPath));
    }

    function folderModelFromPath(path){
        return Qt.createQmlObject('import Qt.labs.folderlistmodel 2.1; FolderListModel{folder: "'+path+'"; nameFilters: ["*.inscore","*.inscorezip"];}', root);
    }


    function open(folderName, folderModel){
        path.append({"name": folderName, "model":folderModel});
        if(folderView.currentView.visible){
            folderView.hiddenView.model = folderModel;
            folderView.state = "open";
        }else{
            folderView.currentView.model = folderModel;
            folderView.currentView.visible = true;
        }
    }

    function back(){
        if(path.count>1){
            path.remove(path.count-1);
            folderView.hiddenView.model = path.get(path.count-1).model;
            folderView.state = "back";
        }
    }
    function repeatBack(repeat){
        if(path.count-repeat>0 && repeat>0){
            folderView.hiddenView.model = path.get(path.count-repeat-1).model;
            while(repeat !== 0){
                path.remove(path.count-1);
                repeat = repeat-1;
            }
            folderView.state = "back";
        }

    }


    ListView{
        id: pathView
        orientation: Qt.Horizontal
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 5*Screen.pixelDensity;
        model: path;

        header: Item{height: 1; width: 5*Screen.pixelDensity;}
        delegate: pathView_delegate

        Component{ id: pathView_delegate
            Rectangle{
                height: pathView.height;
                width: pathView_delegate_text.width;
                Text{
                    id: pathView_delegate_text
                    text: " "+ name + (index+1==path.count?"":" /")
                    verticalAlignment:   Text.AlignVCenter;
                    color: "#3a3a3a"
                    font.pixelSize:  4*Screen.pixelDensity;
                    font.bold: true;
                    font.capitalization: Font.SmallCaps
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        root.repeatBack(path.count-index-1);
                    }
                }
            }
        }
    }

    Rectangle{
        id: separator;
        anchors.top: pathView.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        Layout.fillWidth: true;
        height: 1
        color: "#eeeeee"
    }

    Rectangle{
        id: folderView
        anchors.top: separator.bottom;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        clip: true;

        property ListView currentView: list1
        property ListView hiddenView: list2

        ListView{
            id: list1
            width: parent.width;
            height: parent.height;
            visible: false;
            x: 0;
            delegate: SlideMenuItem{
                text: fileName;
                first: !index;
                onClicked: {
                    if(fileIsDir)
                        root.openPath(fileName, fileURL);
                    else{
                        inscore.postMessage("/ITL", "load", filePath);
                         console.log("open ",filePath);
                    }
                }
            }
        }
        ListView{
            id: list2;
            width: parent.width;
            height: parent.height;
            visible: false;
            x: 0;
            delegate: SlideMenuItem{
                text: fileName;
                first: !index;
                onClicked: {
                    if(fileIsDir)
                        root.openPath(fileName, fileURL);
                    else{
                        inscore.postMessage("/ITL", "load", filePath);
                        console.log("open ",filePath);
                    }
                }
            }
        }

        states: [
            State {
                name: "back"
                PropertyChanges {target: folderView; currentView.x:currentView.width; }
                PropertyChanges {target: folderView; hiddenView.x:0; }
            },
            State {
                name: "open"
                PropertyChanges {target: folderView; currentView.x:-currentView.width; }
                PropertyChanges {target: folderView; hiddenView.x:0; }
            }
        ]

        transitions:[
            Transition{
                to: "back";
                SequentialAnimation{
                    PropertyAction {target: folderView; property: "hiddenView.x"; value:-folderView.currentView.width;}
                    PropertyAction {target: folderView; property: "hiddenView.visible"; value: true;}
                    ParallelAnimation{
                        PropertyAnimation{
                            targets: folderView
                            properties: "currentView.x";
                            duration: 500;
                            easing.type: Easing.InOutQuad;
                        }
                        PropertyAnimation{
                            targets: folderView
                            properties: "hiddenView.x";
                            duration: 500;
                            easing.type: Easing.InOutQuad;
                        }
                    }
                    PropertyAction{target: folderView; property: "currentView.visible"; value: false;}
                    //Switch view
                    PropertyAction{target: folderView; property: "currentView"; value: folderView.currentView==list1?list2:list1;}
                    PropertyAction{target: folderView; property: "hiddenView";  value: folderView.hiddenView ==list1?list2:list1;}
                    PropertyAction{target: folderView; property: "state"; value: "";}
                }
            },
            Transition{
                to: "open";
                SequentialAnimation{
                    PropertyAction {target: folderView; property: "hiddenView.x"; value:folderView.currentView.width;}
                    PropertyAction {target: folderView; property: "hiddenView.visible"; value: true;}
                    ParallelAnimation{
                        PropertyAnimation{
                            targets: folderView
                            properties: "currentView.x";
                            duration: 500;
                            easing.type: Easing.InOutQuad;
                        }
                        PropertyAnimation{
                            targets: folderView
                            properties: "hiddenView.x";
                            duration: 500;
                            easing.type: Easing.InOutQuad;
                        }
                    }
                    PropertyAction{target: folderView; property: "currentView.visible"; value: false;}
                    //Switch view
                    PropertyAction{target: folderView; property: "currentView"; value: folderView.currentView==list1?list2:list1;}
                    PropertyAction{target: folderView; property: "hiddenView";  value: folderView.hiddenView ==list1?list2:list1;}
                    PropertyAction{target: folderView; property: "state"; value: "";}
                }
            }

        ]

    }

}
