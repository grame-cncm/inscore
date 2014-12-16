/*
    javascript code to manage intervals, rects, points
    and to generate mappings
*/

var gPoints 	= new Array();    // points and associated time intervals
var gRects 		= new Array();    // user defined rects
var gSavedRects = new Array();    // user defined rects
var gCurrent = {};            // the current rect
var gIndex=0;                 // the current index in rects or in points
var gFixed=0;
var gSegmentLengthNum=1;
var gSegmentLengthDeNum=1;

reset ();
//post("MapBuilder JS Start\n");

// reset the whole system
function fixed (state)   	{ gFixed = state; }
function slnum (n)   		{ gSegmentLengthNum = n; }
function sldenum (n)   		{ gSegmentLengthDeNum = n; }

// reset the whole system
function reset ()
{
    gIndex = 0;
    gPoints = new Array();
    gRects = new Array();
    gSavedRects = new Array();
}

// builds a point
function point (x, y)
{
    var p = {};
    p.x = x;
    p.y = y;
    return p;
}

// builds an interval
function interval (a, b)
{
    var itval = {};
    itval.start = a;
    itval.end = b;
    itval.empty = (a == b);
    return itval;
}

// builds a rect as a pair of intervals
function contains (r, p)
{
    var etolerance = 5;
    if ((p.x < r.xinterval.start) || (p.x > (r.xinterval.end + etolerance)))
        return false;
    if ((p.y >= r.yinterval.start) && (p.y <= r.yinterval.end))
    	return true;
    return false;
}

// builds a rect as a pair of intervals
function rect (x1, x2, y1, y2)
{
    var r = {};
    r.xinterval = interval (x1, x2);
    r.yinterval = interval (y1, y2);
    r.empty = r.xinterval.empty || r.yinterval.empty;
    return r;
}

function rectStore (x1, x2, y1, y2) { gCurrent = rect(x1, x2, y1, y2); }

// saves the current rect
function accept ()
{
    gRects[gIndex] = gCurrent;
    gIndex++;
    rectStore (0,0,0,0);
}

function reject ()
{ 
	rectStore (0,0,0,0); 
	if (gIndex > 0) {
		gIndex--;
		gRects[gIndex] = gCurrent;
	}
}

// stores a point and a time interval
function store (x, y, start, end)
{
    var o = {};
    o.point = point(x, y);
    o.time = interval(start,end);
    gPoints[gIndex] = o;
    gIndex++;
}

// starts collecting points and time intervals
function play ()
{
//   	post ("starts collecting points", gRects.length, "rects available\n");
    gIndex = 0;
    gPoints = new Array();
}

find.local = 1;
function find(p)
{
    for (var i=0; i < gRects.length; i++) {
    	var r = gRects[i];
       	if (contains (r, p)) {
            r = rect(r.xinterval.start, p.x, r.yinterval.start, r.yinterval.end);
            gRects[i].xinterval.start = p.x;
			return r;
        }
    }
    return rect (0,0,0,0);
}

copy.local = 1;
function copy(src, dest)
{
    for (var i=0; i < src.length; i++) {
    	var r = src[i];
    	dest[i] = rect(r.xinterval.start, r.xinterval.end, r.yinterval.start, r.yinterval.end);
    }
}

function interval2string(itvl) {
    return "[" + itvl.start + ", " + itvl.end + "[";
}

function segment2string(seg) {
    return "( " + interval2string(seg.xinterval) + " " + interval2string(seg.yinterval) + " )";
}

function time2string(t, div) {
    return "( [" + t.start + "/" + div + ", " + t.end + "/" + div  + "[ )";
}

function relation2string(relation, timediv) {
    return segment2string(relation.segment) + " " + time2string(relation.time, timediv);
}

function fixedtime(i)
{
	return interval(gSegmentLengthNum*i, gSegmentLengthNum*(i+1));
}

function generate(timediv)
{
//    post ("generate:", gPoints.length, "points and", gRects.length, "rects\n");
    var i; var map = "";
    rect (0,0,0,0);
//    post ("save rects:", gRects.length, "\n");
    copy(gRects, gSavedRects);
    for (i=0; i < gPoints.length; i++) {
        var p = gPoints[i].point;
        var segment = find( p );
        if (segment.empty)
            post ("WARNING ! point", p.x, p.y, "not in a rect\n");
        else {
            var relation = {};
            relation.segment = segment;
            if (gFixed) {
            	relation.time = fixedtime(i);
	            map += relation2string(relation, gSegmentLengthDeNum) + "\n";
            }
            else {
            	relation.time = gPoints[i].time;
	            map += relation2string(relation, timediv) + "\n";
            }
        }
    }
//    post ("restore rects:", gRects.length, "\n");
    copy(gSavedRects, gRects);
    outlet (0, map);
}
