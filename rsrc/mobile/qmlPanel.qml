import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Item {
    ColumnLayout{

        anchors.fill: parent

        Button{
            Layout.fillWidth: true
            text: "clear text"
            onClicked: textEdit.text = "";
        }

        Repeater{
            model: 5
            Slider{
                Layout.fillWidth: true
            }
        }

        Text{
            id: text
            text:" Ceci est un text pas trop long\n mais quand même..."
            Layout.fillWidth: true;
            Layout.fillHeight: true
        }
    }
}
