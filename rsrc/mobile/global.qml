import QtQuick
import QtQuick.Window

QtObject {
    property real pixelDensity :   Screen.pixelDensity;
    property real  diag        :   Math.sqrt( (Screen.height*Screen.height) + (Screen.width*Screen.width))/pixelDensity;
}
