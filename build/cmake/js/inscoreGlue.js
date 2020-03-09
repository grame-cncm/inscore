
"use strict";

//------------------------------------------------------------------------
// a glue to decode strings received from c++
// got it from https://dev.to/azure/passing-strings-from-c-to-javascript-in-web-assembly-1p01

function getScene (id) 		 { return document.getElementById(id); }
function getSceneWidth (id)  { return document.getElementById(id).clientWidth; }
function getSceneHeight (id) { return document.getElementById(id).clientHeight; }
function getSceneX (id) 	 { return document.getElementById(id).getBoundingClientRect().left; }
function getSceneY (id) 	 { return document.getElementById(id).getBoundingClientRect().top; }
function getDocWidth (id) 	 { return document.body.clientWidth; }
function getDocHeight (id) 	 { return document.body.clientHeight; }

function updateCommon (scene, id, x, y, w, h) 	 { 
	let elt = document.getElementById(scene).getElementById(id);
	elt.style.width = w + "px";
	elt.style.height = h + "px";
	elt.style.left = x + "px";
	elt.style.top = y + "px";
}

function newDiv (parent, id, name) { 
	let elt = document.getElementById(parent);
	elt.setAttribute = name;
}


//----------------------------------------------------------------------------
// INScore interface
//----------------------------------------------------------------------------
class INScoreGlue {

    constructor(inscore) {
    	this.fInscore = new INScore;
    	this.fTimeTask = 0;
    	this.fInscore.initialize ().then (() => { this.initialize(); });
    }
	
    //------------------------------------------------------------------------
    // initialization
    initialize () {
		this.fInscore.start(0,0,0);
		this.fTimeTask = setInterval( () => { this.fInscore.timeTask(); }, this.fInscore.getRate());
		let divs = document.getElementsByClassName("inscore");
// console.log("JS INScoreGlue::initialize inscore " + divs.length)
		for (let i=0; i<divs.length; i++)
			this.initDiv (divs[i], false);
		divs = document.getElementsByClassName("inscore2");
// console.log("JS INScoreGlue::initialize inscore2 " + divs.length)
		for (let i=0; i<divs.length; i++)
			this.initDiv (divs[i], true);
// 		console.log("JS INScoreGlue::initialize doc size " + document.body.clientWidth + " " + document.body.clientHeight )
	}
    
    //------------------------------------------------------------------------
    // inscore div initialization
	initDiv (div, v2) {
		const scene = div.id;
		if (!scene) scene = "scene";
		this.fInscore.postMessageStr ("/ITL/"+scene, "new");	
		this.allowdrop (div);
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
    // load an inscore file
	loadInscore(file, v2) {
		let reader = new FileReader();				
		reader.readAsText (file);
		if (v2)
			reader.onloadend = (event) => { this.fInscore.loadInscore2(reader.result)};
		else
			reader.onloadend = (event) => { this.fInscore.loadInscore(reader.result)};
	}

    //------------------------------------------------------------------------
    // files drop support
	filedropped(e) {
		let filelist = e.dataTransfer.files;
		if (!filelist) return;
	
		let filecount = filelist.length;
		for (let i = 0; i < filecount; i++ ) {
			const file 	= filelist[i]
			const fileName = filelist[i].name;
			const properties = this.getFileProperties(fileName);
			const name 	= properties.name;
			const ext 	= properties.ext.toLocaleLowerCase();
			if (ext == "inscore") 		this.loadInscore (file, false);
			else if (ext == "inscore2") this.loadInscore (file, true);
			else {
				console.log ("not an inscore file " + name);
			}
		}
	}


	drop( e ) {
		let data = e.dataTransfer.getData("Text");
		if (data)	this.fInscore.loadInscore(data, false);
		else 		this.filedropped (e);
		e.target.style.border = e.target.getAttribute('savedborder');
	}
		
    //------------------------------------------------------------------------
    // activate drag & drop on inscore divs
	allowdrop (div) {
		div.addEventListener ("dragenter", (event) => { div.setAttribute('savedborder', div.style.border);
														div.style.border = "1px solid grey"; }, false);
		div.addEventListener ("dragleave", (event) => { div.style.border = div.getAttribute('savedborder'); }, false);
		div.addEventListener ("dragover",  (event) => { event.preventDefault(); }, false);
		div.addEventListener ("drop",      (event) => { event.preventDefault(); this.drop ( event );} , false);
    }    
 }

var gGlue = new INScoreGlue;


