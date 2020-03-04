
"use strict";

//----------------------------------------------------------------------------
// INScore interface
//----------------------------------------------------------------------------
class INScoreGlue {
    constructor(inscore) {
    	this.fInscore = inscore;
    }
    
    //------------------------------------------------------------------------
    // initialization
    initialize () {
		let divs = document.getElementsByClassName("inscore");
		for (let i=0; i<divs.length; i++) {
			this.allowdrop (divs[i]);
		}
	}

    //------------------------------------------------------------------------
    // utilities
    getFileProperties(file) {
		let ext 	= file.substring(file.lastIndexOf('.')+1, file.length);
		let name 	= file.substring(0, file.lastIndexOf('.'));
// 		name = this.buildCorrectName(name);
		return { name: name, ext: ext }	
	}

    //------------------------------------------------------------------------
    // files drop support
	filedropped(e) {
		let filelist = e.dataTransfer.files;
		if (!filelist) return;
	
		let filecount = filelist.length;
		for (let i = 0; i < filecount; i++ ) {
			let file 	= filelist[i]
			let fileName = filelist[i].name;
			let properties = this.getFileProperties(fileName);
			let name 	= properties.name;
			let ext 	= properties.ext.toLocaleLowerCase();
			if (ext == "inscore") {
				let reader = new FileReader();				
				reader.readAsText (file);
				console.log ("file " + name + " dropped : ");
				reader.onloadend = function(event) { console.log ("file content: " + reader.result); };						
			}
			else {
				console.log ("not an inscore file " + name);
			}
		}
	}


	drop( e) {
		let data = e.dataTransfer.getData("Text");
		if (data)
			console.log ("text dropped : " + data);
		else this.filedropped (e);
		e.target.style.border = "none";
	}
		
    //------------------------------------------------------------------------
    // activate drag & drop on inscore divs
	allowdrop (div) {
		div.addEventListener ("dragenter", (event) => { div.style.border = "1px solid grey"; }, false);
		div.addEventListener ("dragleave", (event) => { div.style.border = "none"; }, false);
		div.addEventListener ("dragover",  (event) => { event.preventDefault(); }, false);
		div.addEventListener ("drop",      (event) => { event.preventDefault(); this.drop ( event );} , false);
    }    
 }
