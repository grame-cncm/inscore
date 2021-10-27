import QtQuick 2.2

Item {
    id: root;
    signal pressed(real x, real y);
    signal released(real x, real y);
    signal canceled;
    signal mouseMove(real x, real y);
    signal clicked;
    MultiPointTouchArea{
        anchors.fill: parent;
        maximumTouchPoints: 1;
        minimumTouchPoints: 1;
        mouseEnabled: true;
        touchPoints: [
            TouchPoint { id: pos }
        ]
        
        property bool pressing: false;

        Timer{
            id: unPress;
            repeat: false;
            interval: 1000
            onTriggered: {
                if(parent.pressing){
                    root.canceled();
                    parent.pressing = false;
                }
            }

        }

        onPressed: {
            pressing = true;
            root.pressed(pos.x, pos.y);
            unPress.restart();
        }
        onReleased: {
            root.released(pos.x, pos.y);
            if(pressing)
                root.clicked();
            pressing = false;
        }
        onUpdated:{
                root.mouseMove(pos.x, pos.y);
                unPress.restart();
        }

        onCanceled: {
            root.canceled();
            pressing = false;
        }
    }
}
