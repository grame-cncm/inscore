import QtQuick 2.0

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

        property bool pressing: false;

        onPressed: {
            pressing = true;
            root.pressed(touchPoints[0].x,touchPoints[0].y);
        }
        onReleased: {
            root.released(touchPoints[0].x,touchPoints[0].y);
            if(pressing)
                root.clicked();
            pressing = false;
        }
        onUpdated: {
            if(touchPoints.length)
                root.mouseMove(touchPoints[0].x,touchPoints[0].y);
        }
        onCanceled: {
            root.canceled();
        }
    }
}
