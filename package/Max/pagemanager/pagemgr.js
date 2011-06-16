/*
    javascript code to manage intervals, rects, points
    and to generate mappings
*/

inlets = 1;
outlets = 2;

var kPageBaseName 		= "page";
var kPageBaseAddress 	= "/ITL/scene/" + kPageBaseName;
var kCursorAddress 		= "/ITL/scene/_cursor";
var kPageRectAddress 	= "/ITL/scene/_pagerect";
var kPagePosAddress 	= "/ITL/scene/_pagepos";
var kPageNumAddress 	= "/ITL/scene/_pagenum";
var kAllPages 			= kPageBaseAddress  + '[0-9]*';

var gPageCount 		= 0;   	// the current pages count
var gScoreDuration 	= 0;	// actually the pages count

//-----------------------------------------------
function reset ()			
{ 
	gPageCount = 0;
	gScoreDuration = 0;
	outlet (0, kAllPages, "del");
    outlet (0, kCursorAddress, "watch");
    outlet (0, kCursorAddress, "watch", "timeEnter", -1000, 1, 0, 1, kCursorAddress, "date", 0, 1);
    outlet (0, kCursorAddress, "watch", "timeEnter",  0, 1, 1, 1, kCursorAddress, "date", 0, 1);
    outlet (0, kPageRectAddress, "duration", 0, 1);
    outlet (0, kPagePosAddress, "date", 0, 1);
    outlet (0, kPageNumAddress, "set", "txt", 0);
    outlet (1, gPageCount);
}

//-----------------------------------------------
function cursorwatch (n) 
{
	pagei = kPageBaseAddress + n;
	pagej = kPageBaseAddress + (n+1);
	
    outlet (0, kCursorAddress, "watch", "timeEnter", n-1, 1, n, 1, kAllPages, "show", 0);
    outlet (0, kCursorAddress, "watch+", "timeEnter", n-1, 1, n, 1, pagei, "xorigin", 1.);
    outlet (0, kCursorAddress, "watch+", "timeEnter", n-1, 1, n, 1, pagej, "xorigin", -1.);
    outlet (0, kCursorAddress, "watch+", "timeEnter", n-1, 1, n, 1, pagei, "show", 1);
    outlet (0, kCursorAddress, "watch+", "timeEnter", n-1, 1, n, 1, pagej, "show", 1);

    outlet (0, kCursorAddress, "watch+", "timeEnter", n-1, 1, n, 1, kPagePosAddress, "date", n-1, 1);
    outlet (0, kCursorAddress, "watch+", "timeEnter", n-1, 1, n, 1, kPageNumAddress, "set", "txt", n);

    outlet (0, kCursorAddress, "watch", "timeEnter",  n, 1, n+1, 1, kCursorAddress, "date", n-1, 1);
}

//-----------------------------------------------
function addPage(file)
{ 
	gPageCount++;
	gScoreDuration++
	address = kPageBaseAddress + gPageCount;
    outlet (0, address, "set", "file", file);
    outlet (0, address, "duration", 1, 1);
    outlet (0, kPageRectAddress, "duration", (gScoreDuration-2)*32 + 1, 32);
    if (gPageCount > 1) {
		cursorwatch (gPageCount-1);
    	outlet (0, kCursorAddress, "date", gPageCount-2, 1);
    }
    outlet (1, gPageCount);
}
