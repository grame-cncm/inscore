import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import Qt.labs.folderlistmodel 2.1
import "global.js" as Size

Item {
    id: root;
    anchors.fill: parent;

    property ListModel path: ListModel{}
    property bool isQrcPath: false

    signal fileClicked(string file);

    function setRootPath(rootName, rootPath){
        path.clear();
        folderView.currentView.visible = false;

        root.openPath(rootName, rootPath);

        var regexp = /^qrc:/
        isQrcPath = regexp.test(rootPath);
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
            folderView.hiddenView.modelList = folderModel;
            folderView.state = "open";
        }else{
            folderView.currentView.modelList = folderModel;
            folderView.currentView.visible = true;
        }
    }

    function back(){
        if(path.count>1){
            path.remove(path.count-1);
            folderView.hiddenView.modelList = path.get(path.count-1).model;
            folderView.state = "back";
        }
    }
    function repeatBack(repeat){
        if(path.count-repeat>0 && repeat>0){
            folderView.hiddenView.modelList = path.get(path.count-repeat-1).model;
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
        height: Size.toPixel(4);
        model: path;
        spacing: 0;

        header: Item{height: 1; width: Size.toPixel(4);}
        footer: Item{height: 1; width: Size.toPixel(4);}
        delegate: pathView_delegate

        Component{ id: pathView_delegate
            Rectangle{
                height: pathView.height;
                width: pathView_delegate_text.width;
                Text{
                    id: pathView_delegate_text
                    text: name + (index+1==path.count?"":" / ")
                    verticalAlignment:   Text.AlignVCenter;
                    color: "#3a3a3a"
                    font.pixelSize:  pathView.height*3/4;
                    font.bold: true;
                    font.capitalization: Font.SmallCaps
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        root.repeatBack(path.count-index-1);
                    }
                }

                Component.onCompleted: pathView.positionViewAtEnd();
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

        property Item currentView: list1
        property Item hiddenView: list2
        property bool animBack: false;

        Component{
            id: folderViewComponent
            Rectangle{
                width:  folderView.width;
                height: folderView.height;

            Flickable{
                id: folderView_scrollView
                anchors.fill: parent;
                contentHeight: folderView_Layout.height
                Column{
                    id: folderView_Layout
                    width: parent.width

                    SlideMenuItem{
                        text: ".."
                        icon: "qrc:///images/folderUp.png"
                        visible: path.count>0 && modelList !== path.get(0).model;
                        onClicked: root.back();
                        first: true;
                        clickable: enabled;
                    }

                    Repeater{
                        //Folders
                        model: modelList;
                        SlideMenuItem{
                            text: fileName;
                            visible: fileIsDir
                            icon: "qrc:///images/folder.png";
                            first: true;
                            onClicked: root.openPath(fileName, fileURL);
                            anchors.left: folderView_Layout.left
                            anchors.right: folderView_Layout.right
                            clickable: enabled;
                        }
                    }
                    Repeater{
                        //Files
                        model: modelList;
                        SlideMenuItem{
                            text: fileName;
                            visible: !fileIsDir;
                            icon: "qrc:///INScoreViewer.png";
                            onClicked: {
                                if(isQrcPath)
                                    root.fileClicked("qrc"+filePath);
                                else
                                    root.fileClicked(filePath);
                            }
                            first: true;
                            clickable: enabled;
                            anchors.left: folderView_Layout.left
                            anchors.right: folderView_Layout.right
                        }
                    }


                }

            }
            }
        }

        Loader{
            id: list1;
            property FolderListModel modelList;
            property bool enable;
            sourceComponent: folderViewComponent;
            x: 0;
            visible:false;
        }
        Loader{
            id: list2;
            property FolderListModel modelList;
            property bool enable;
            sourceComponent: folderViewComponent;
            x: 0;
            visible:false;
        }

        function prepareAnimation(){
            hiddenView.visible = true;
            hiddenView.x = folderView.hiddenView.width * (animBack?-1:1);
            currentView.enabled = false;
        }

        function endAnimation(){
            currentView.visible = false;
            //switchView
            if(currentView === list1){
                currentView = list2;
                hiddenView  = list1;
            }else{
                currentView = list1;
                hiddenView  = list2;
            }
            folderView.state = "";
            currentView.enabled = true;
        }

        states: [
            State {
                name: "back"
                PropertyChanges {target: folderView; currentView.x:currentView.width; }
                PropertyChanges {target: folderView; hiddenView.x:0; }
                PropertyChanges {target: folderView; animBack: true; }
            },
            State {
                name: "open"
                PropertyChanges {target: folderView; currentView.x:-currentView.width; }
                PropertyChanges {target: folderView; hiddenView.x:0; }
                PropertyChanges {target: folderView; animBack: false; }
            }
        ]

        transitions:[
            Transition{
                id: transition
                from: "";
                SequentialAnimation{
                    PropertyAction{target: folderView; property: "animBack";}
                    ScriptAction{script: folderView.prepareAnimation();}
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
                    //Switch view
                    ScriptAction{script: folderView.endAnimation();}
                }
            }

        ]

    }

}
