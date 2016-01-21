.pragma library

var headerPointHeight = 6;


////////////////////////////
//          Scale         //
////////////////////////////

var globalComponent = Qt.createComponent("global.qml");
var QtGlobal = globalComponent.createObject(null);
var scale = QtGlobal.pixelDensity;

//For large display enlarge the scale
var diag = QtGlobal.diag;
var diagThreshold = 90;
var enlargeFactor = 1;
scale = scale +(Math.max(0,Math.log(diag/diagThreshold)*enlargeFactor));
headerPointHeight = headerPointHeight + (Math.max(0,Math.log(diag/50)));

// 1 point >= 1 mm
function toPixel(point) {
    return point*scale;
}
