import QtQuick 2.0
import QtQuick.Window 2.0

QtObject {
    property real pixelDensity :   Screen.pixelDensity;
    property real  diag        :   Math.sqrt( (Screen.height*Screen.height) + (Screen.width*Screen.width))/pixelDensity;
}
