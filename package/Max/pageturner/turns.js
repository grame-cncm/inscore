/*
    javascript code to manage intervals, rects, points
    and to generate mappings
*/

var gTimePoints = new Array();    // time points array

reset ();

// reset the whole system
function reset ()
{
    gTimePoints = new Array();
}

// builds a point
function time (num, denum)
{
    var t = {};
    t.num = num;
    t.denum = denum;
    return t;
}

// stores a time position to the corresponding page index
function store (n, d, page)
{
    gTimePoints[page] = time (n , d);
}

function time2string(t) {
    return t.num + " " + t.denum;
}

function watchmsg(watcher, target, start, end, page)
{
	return watcher + " watch+ timeEnter " + time2string(start) + " " 
			+ time2string(end) + " " + target + " page " + page;
}

function generate()
{
	watcher= "/ITL/scene/_pageturner";
	target = "/ITL/scene/score";
	watch = watcher + " set \"txt\" \"page turner\"\n";
	watch += watcher + " show 0\n";
    var prev = time (0, 1);
    for (i=1; i < gTimePoints.length; i++) {
    	if (gTimePoints[i]) {
	    	var t = gTimePoints[i];
    		if (t.num > 0 ) {
    			watch += watchmsg(watcher,target, prev, t, i) + "\n";
    			prev = t;
    		}
    	}
    	else post("no point for page", i, "\n");
    }
    outlet (0, watch);
}
