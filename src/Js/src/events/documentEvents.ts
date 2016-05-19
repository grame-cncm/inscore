
///<reference path="../inscore.ts"/>
///<reference path="../model/TILoader.ts"/>
///<reference path="../vhtmlview/VHtmlTools.ts"/>

function dropEvent(e: any) {
    dragOverEvent(e);

    let data = e.dataTransfer.getData("Text");
	if (data) {			// check if text has been dropped
		let loader = new TILoader;
		loader.process (data, INScore.getRoot());
	}
	else {				// check if files have been dropped
	    let filelist =  e.dataTransfer.files;
    	if (!filelist) return; 

		let filecount = filelist.length;
		if (filecount > 0) {                
			for (let i=0; i < filecount; i++) {
				let loader = new TILoader;
				loader.load(filelist[i], INScore.getRoot());      
			} 
		} 
    }
}

function dragOverEvent(e: any) {
    e.stopPropagation();
    e.preventDefault();
}

function resizeDocument() { INScore.postMessage ("/ITL/*", ["redraw"]); }

