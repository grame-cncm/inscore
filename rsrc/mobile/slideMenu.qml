import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window
import Qt.labs.folderlistmodel
import "global.js" as Size;

Item {
    id: root
	
    property string version: ""
    property string initialRootPath: inscore.rootPath();
    signal switchToPanel(string name)

    width: 400
    height: 1000

    Rectangle{
        id: slidePanel

        anchors.fill: parent
        color: "white"

        // --------------- HEADER  ----------------
		SlideMenuHeader {
			version: root.version
			id : header
            onClicked: {
                if(root.state == "exploreMenu")
                    root.state = "mainMenu";
                else
                    contextObject.hideMenu();
            }
		}

        // ------------  MENU  --------------------

        Rectangle{
            id: menuPanel
            color: "#00000000"

            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right


            // --------  EXPLORE MENU -------------

            Rectangle{
                id: exploreMenu
                anchors.fill: parent;

                property bool exploreRecent: false;

                ExploreView{
                    id: exploreView;
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
//                    anchors.bottom: urlField.top;
                    anchors.topMargin: Size.toPixel(1)
                    onFileClicked: {
                        inscore.postMessage("/ITL", "rootPath", file.slice(0, file.lastIndexOf("/")));
                        inscore.postMessage("/ITL/scene", "foreground");
                        inscore.postMessage("/ITL", "load", file.slice(file.lastIndexOf("/")+1));

                        if(!exploreMenu.exploreRecent)
                            contextObject.addDownloadedFile(file);
                    }
                    fileDeletable: exploreMenu.exploreRecent
                    onFileDeleted: {
                        if(exploreMenu.exploreRecent)
                            contextObject.deleteDownloadedFile(file);
                    }
                }

//                UrlBar{
//                    id: urlField
//                    visible: false;
//                    anchors.left: parent.left;
//                    anchors.right: parent.right;
//                    anchors.bottom: parent.bottom;
//                }

                //Shadow:
                Image{
                    id: exploreMenu_shadow
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    width: Size.toPixel(1.5)
                    source: "shadow.png"
                    fillMode: Image.TileVertically
                    mirror: true;
                    smooth: true;
                    opacity: 0.6;
                }
            }


            // --------  MAIN MENU ----------------
            Item{
                id: mainMenu
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width + mainMenu_shadow.width
                x: 0
                Image{
                    //shadow
                    id: mainMenu_shadow
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    width: Size.toPixel(1.5)
                    source: "shadow.png"
                    fillMode: Image.TileVertically
                    opacity: 0.6;
                }

                Rectangle{
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.right: mainMenu_shadow.left;
                    clip: true;
                    Flickable{
                        anchors.fill: parent
                        contentHeight: menuColumn.height;
                        Column{
                            id: menuColumn
                            width: menuPanel.width

                            move: Transition {
                                NumberAnimation { properties: "x,y"; duration: 300 }
                            }

                            Item{height: Size.toPixel(2); width:parent.width}

                            ////////////////////////////////////
                            //       Main menu definition     //
                            ////////////////////////////////////

                            // -- SCENES --
                            SectionSeparator{
                                title: "Scenes"
                                visible: contextObject.sceneList.length
                            }
                            Repeater{
                                model: contextObject.sceneList
                                SlideMenuItem{
                                    text: modelData
                                    onClicked: {
                                        inscore.postMessage(modelData, "foreground");
                                    }
                                    onClose: {
                                        if(modelData=="/ITL/log")
                                            inscore.postMessage(modelData, "show", 0);
                                        else
                                            inscore.postMessage(modelData, "del");
                                    }

                                    first: !index
                                    closable: true
                                    anchors.right: menuColumn.right
                                    anchors.left:  menuColumn.left
                                }
                            }

                            // -- LOAD --
                            SectionSeparator{
                                title: "Load Script"
                            }

                            SlideMenuItem{
                                text: "Exemples"
                                first: true
                                onClicked: {
                                    root.state = "exploreMenu";
                                    exploreView.setRootPath("Exemples", "qrc:///scripts");
                                    exploreMenu.exploreRecent = false;
                                }
                            }
                            SlideMenuItem{
                                text: "Files"
                                onClicked: {
                                    root.state = "exploreMenu";
                                    exploreView.setRootPath("HOME", "file://"+initialRootPath);
                                    exploreMenu.exploreRecent = false;
                                }
                            }
                            SlideMenuItem{
                                text: "Recent"
                                onClicked: {
                                    root.state = "exploreMenu";
                                    exploreView.setRootPath("Recently loaded", "file://"+downloadPath);
//                                    urlField.clear();
                                    exploreMenu.exploreRecent = true;
                                }
                            }

                            // -- TOOLS --
                            SectionSeparator{
                                title: "Tools"
                            }
                            Repeater{
                                model: contextObject.panelList
                                SlideMenuItem{
                                    text: modelData
                                    onClicked: root.switchToPanel(modelData)
                                    first: !index

                                }
                            }
                            SlideMenuItem{
                                property bool log: contextObject.sceneList.indexOf("/ITL/log")!==-1;
                                text: log?"Hide log":"Show log";
                                onClicked: {
                                    inscore.postMessage("/ITL/log", "show", !log)
                                }
                            }
                            SlideMenuItem{
                                text: "Quit"
                                onClicked: inscore.postMessage("/ITL", "quit")
                            }
                        }
                    }
                }
            }

            Rectangle{
                id: headerShadow
                height: Size.toPixel(7)//40
                opacity: 0.9;
                gradient: Gradient {
                    GradientStop {position: 0.00; color: "#66363636"}
                    GradientStop {position: 0.33; color: "#33363636"}
                    GradientStop {position: 1.00; color: "#00363636"}
                }

                anchors.top:parent.top
                anchors.left: parent.left
                anchors.right: parent.right
            }

        }
    }

    state: "mainMenu"

    states: [
        State {
            name: "exploreMenu"
            PropertyChanges { target: mainMenu; x: -menuPanel.width;}
        },
        State {
            name: "mainMenu"
            PropertyChanges { target: mainMenu; x: 0;}
        }
    ]
    transitions: [
        Transition {
            to: "exploreMenu"
            NumberAnimation{ target: mainMenu; easing.type: Easing.InCubic; properties: "x"; duration: 750; }
        },
        Transition {
            to: "mainMenu"
            NumberAnimation{ target: mainMenu; easing.type: Easing.OutCubic; properties: "x"; duration: 750; }
        }
    ]

    Component.onCompleted: {
        contextObject.back.connect(backButton);
    }

    function backButton(){
        if(state=="exploreMenu")
            state = "mainMenu";
        else
            contextObject.hideMenu();
    }

//    focus: true;
//    Keys.onReleased: {
//        if (event.key == Qt.Key_Back) {
//            if(state=="exploreMenu")
//                state = "mainMenu";
//            else
//                contextObject.hideMenu();
//            console.log("Back key catched");
//            event.accepted = true
//        }
//    }
}
