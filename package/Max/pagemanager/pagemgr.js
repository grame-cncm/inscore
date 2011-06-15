/*
    javascript code to manage intervals, rects, points
    and to generate mappings
*/

var kPageBaseName = "page";
var kPageBaseAddress = "/ITL/scene/" + kPageBaseName;
var kAllPages = kPageBaseAddress  + '[0-9]*';

var gPageCount 		= 0;   	 		// the current pages count
var gCurrentPage 	= 0;   	 		// the current page
var gPageFiles 		= new Array(); 
var gEditing		= false;

//-----------------------------------------------
function reset ()			
{ 
	gPageCount = 0;
	gCurrentPage = 0;
	gPageFiles = new Array();
    outlet (0, kAllPages, "del");
}

//-----------------------------------------------
function setPagePos(n)	
{ 
	kMaxPages = 20;
    outlet (0, "/ITL/scene/_pagepos", "date", n-1, kMaxPages);
    outlet (0, "/ITL/scene/_pagenum", "set", "txt", n);
}

//-----------------------------------------------
function nextPage()	
{ 
	setPage (gCurrentPage+1);
	setPagePos (gCurrentPage);
}

//-----------------------------------------------
function prevPage()	
{ 
	setPage (gCurrentPage-1); 
	setPagePos (gCurrentPage);
}

//-----------------------------------------------
function addPage(file)
{ 
	gPageFiles[gPageCount++] = file;
	n = kPageBaseAddress + gPageCount;
	setPage(gPageCount-1);
    outlet (0, n, "set", "file", file);
}

//-----------------------------------------------
function setPage (n) 
{
	if (gEditing) return; 
	if (gPageCount < 2) return; 
	if (n >= gPageCount) n = gPageCount-1;
	if (n < 1) n = 1;
    gCurrentPage = n;
    outlet (0, kAllPages, "show", 0);
    outlet (0, kPageBaseAddress + n, "xorigin", 1.01);
    outlet (0, kPageBaseAddress + (n+1), "xorigin", -1.01);
    outlet (0, kPageBaseAddress + n, "show", 1);
    outlet (0, kPageBaseAddress + (n+1), "show", 1);
}

//-----------------------------------------------
function mapPage (n)
{
    setPage (n);
	gEditing = true;
	outlet (0, kPageBaseAddress + n, "rename", "score");
	outlet (0, "/ITL/scene", "load", "watch.inscore");
}

//-----------------------------------------------
function stopMap ()
{
    setPage (n);
	gEditing = false;
	outlet (0, "/ITL/scene/score", "watch");
	outlet (0, "/ITL/scene/score", "rename", kPageBaseAddress + n);
}
