
///<reference path="../inscore.ts"/>
///<reference path="../model/TILoader.ts"/>
///<reference path="../vhtmlview/VHtmlTools.ts"/>

function dropEvent(e: any) {
    dragOverEvent(e);

    let filelist =  e.dataTransfer.files;
    if (!filelist) { return; }  
  
    let filecount = filelist.length;
    if (filecount > 0) {                
        for (let i=0; i < filecount; i++) {
            let loader = new TILoader;
            loader.load(filelist[i], INScore.getRoot());      
        } 
    } 
}

function dragOverEvent(e: any) {
    e.stopPropagation();
    e.preventDefault();
}

function resizeDocument() {
	let size = TWindow.getSize();
	console.log("resizeDocument " + size.w + " " + size.h);
}

