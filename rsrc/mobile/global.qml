import QtQuick 2.2
import QtQuick.Window 2.15

QtObject {
    property real pixelDensity :   Screen.pixelDensity;
    property real  diag        :   Math.sqrt( (Screen.height*Screen.height) + (Screen.width*Screen.width))/pixelDensity;
}
