/*
    javascript code to generate page turn messages
    and tempo map qlist
*/

inlets = 1;
outlets = 2;

var gTimePoints = new Array();    	// time points array
var gTimePairs = new Array();    	// time pairs array (music time + abs time)
var gTPIndex = 0;

// reset the whole system
function reset ()
{
    gTimePoints = new Array();
}

function temporeset ()
{
    gTimePairs = new Array();
    gTPIndex = 0;
}

function time2string(t) {
    return t.num + " " + t.denum;
}

// builds a time pair
function maketime (num, denum, abs)
{
    var t = {};
    t.num = num;
    t.denum = denum;
    t.music = 4*num/denum;		// music time expressed in quarter notes count
    t.abs = abs/100;			// absolute time expressed in seconds
    return t;
}

function timepair (num, denum, abs)
{
    var t = maketime (num, denum, abs);
    if (t.music < 0)
    	post ("warning: click is outside map\n");
    else 
    	gTimePairs[gTPIndex++] = t;
}

// ---------------------------------------------
function tempomap ()
{
    previous = maketime(0,1,0);
    prevelapsed = 0;
    for (i=0; i < gTimePairs.length; i++) {
	    var t = gTimePairs[i];
	    elapsed = t.abs - previous.abs;
		if (elapsed < 0) {
			post ("error at index", i, ": elapsed is", elapsed, "at time=", t.abs, "while previous time=", previous.abs,"\n");
			break;
		}
	    // the current tempo
	    tempo = 60 * (t.music - previous.music) / elapsed;
	    outlet (1, Math.round(prevelapsed*1000) + " _tempo " + tempo);
	    outlet (1, 0 + " _turnedit /ITL/scene/_* date " + previous.num + " " + previous.denum);
		prevelapsed = elapsed;	
		previous = t;
    }
}

// ---------------------------------------------
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

function watchmsg(watcher, target, start, end, page)
{
	return watcher + " watch+ \"timeEnter\" " + time2string(start) + " " 
			+ time2string(end) + " \"" + target + "\" \"page\" " + page;
}

// ---------------------------------------------
function generate()
{
	watcher= "/ITL/scene/_pageturner";
	target = "/ITL/scene/score";
	watch = watcher + " set \"txt\" \"page turner\"";
	watch += "\n" + watcher + " watch";
	watch += "\n" + watcher + " show 0";
    var prev = time (0, 1);
    for (i=1; i < gTimePoints.length; i++) {
    	if (gTimePoints[i]) {
	    	var t = gTimePoints[i];
    		if (t.num > 0 ) {
    			watch += "\n" + watchmsg(watcher,target, prev, t, i);
    			prev = t;
    		}
    	}
    	else post("no point for page", i, "\n");
    }
    outlet (0, watch);
}
