import QtQuick 2.0
import QtQuick.Controls 1.4
import "global.js" as Size;

Item {
    id: root;
    function clear(){
        protocolCombeBox.currentIndex = 0;
        urlField.text = "";
    }

    function accept(){
        if(urlField.text!=""){
            inscore.postMessage("/ITL", "load", (protocolCombeBox.currentText + urlField.text).replace(" ", ""))
            inscore.postMessage("/ITL/scene", "foreground");
            console.log(urlField.text,  (protocolCombeBox.currentText + urlField.text).replace(" ", ""));
            urlField.text = false;
            contextObject.hideMenu();
            root.clear();
        }
    }

    height: urlField.height;

    Row{
        id: urlLauncher
        anchors.fill: parent;

        ComboBox{
            id: protocolCombeBox;
            model: ["http://", "https://", ""];
            width: Size.toPixel(12);
        }

        TextField{
            id: urlField
            placeholderText: "URL address";
            width: parent.width - protocolCombeBox.width - urlLoad.width - Size.toPixel(2);

            onAccepted: root.accept();

            menu: Menu{
                MenuItem{
                    text: "Paste"
                    onTriggered: urlField.paste();
                }
                MenuItem{
                    text: "Copy"
                    visible: urlField.selectedText.length>0;
                    onTriggered: urlField.copy();
                }
                MenuItem{
                    text: "Cut"
                    visible: urlField.selectedText.length>0;
                    onTriggered: urlField.cut();
                }
            }

        }

        Item{width: Size.toPixel(1); height: parent.height}

        Rectangle{
            id: urlLoad
            width: height
            height: parent.height;
            Image{
                opacity: 0.5;
                width: height
                height: parent.height*0.8;
                anchors.centerIn: parent;


                source: "qrc:///images/go.png"
                fillMode: Image.PreserveAspectFit

                SimpleTouchArea{
                    anchors.fill: parent;
                    onClicked: root.accept();
                    onPressed: urlField.state = "pressed";
                    onReleased: urlField.state = ""
                    onCanceled: urlField.state = ""
                }
                states: [
                    State {
                        name: "pressed"
                        PropertyChanges {target: urlField; opacity: 0.8;}
                    }
                ]
            }
        }
    }
}
