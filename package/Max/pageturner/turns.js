/*
    javascript code to generate page turn messages
    and tempo map qlist
*/

inlets = 1;
outlets = 2;

var gTimePoints = new Array();    	// time points array
var gTimePairs = new Array();    	// time pairs array (music time + abs time)
var gTPIndex = 0;

reset ();

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
function timepair (num, denum, abs)
{
    var t = {};
    t.num = num;
    t.denum = denum;
    t.music = 4*num/denum;		// music time expressed in quarter notes count
    t.abs = abs/100;			// absolute time expressed in seconds
    gTimePairs[gTPIndex++] = t;
}

// builds a time pair
function tempomap ()
{
    prevabs = prevmus = prevelapsed = 0;
    num = denum = 0;
    var tmap ="\n";
    for (i=0; i < gTimePairs.length; i++) {
	    var t = gTimePairs[i];
	    if (t.music >= 0) {
	    	elapsed = t.abs - prevabs;
			if (elapsed < 0)
				post ("warning: elapsed is ", elapsed, " with tabs=", t.abs, " prevabs=", prevabs,"\n");

	    	// the current tempo
	    	tempo = 60 * (t.music - prevmus) / elapsed;
	    	tmap += (prevelapsed*1000) + " _tempo " + tempo + ";\n";
	    	tmap += 0 + " _turnedit /ITL/scene/_* date " + num + " " + denum + ";\n";
			prevelapsed = elapsed;	
			prevabs = t.abs;
			prevmus = t.music;
			num = t.num;
			denum = t.denum;
    	}
    	else post ("warning: music date is", t.music,"\n");
    }
    outlet (1, tmap);
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

function watchmsg(watcher, target, start, end, page)
{
	return watcher + " watch+ \"timeEnter\" " + time2string(start) + " " 
			+ time2string(end) + " \"" + target + "\" \"page\" " + page;
}

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
