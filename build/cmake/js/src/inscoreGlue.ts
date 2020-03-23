///<reference path="inscore.ts"/>
 
//----------------------------------------------------------------------------
class INScoreGlue {
	private fInscore : INScore;
	private fTimeTask : number;

    constructor() {
    	this.fInscore = new INScore;
    	this.fTimeTask = 0;
    	this.fInscore.initialise ().then (() => { this.initialize(); });
    }
	
    //------------------------------------------------------------------------
    // initialization
    initialize () : void {
		this.fInscore.start();
		this.fTimeTask = window.setInterval( () => { this.fInscore.timeTask(); }, this.fInscore.getRate());
		let divs = document.getElementsByClassName("inscore") as HTMLCollectionOf<HTMLElement>;
// console.log("JS INScoreGlue::initialize inscore " + divs.length)
		for (let i=0; i<divs.length; i++)
			this.initDiv (divs[i], false);
		divs = document.getElementsByClassName("inscore2") as HTMLCollectionOf<HTMLElement>;
// console.log("JS INScoreGlue::initialize inscore2 " + divs.length)
		for (let i=0; i<divs.length; i++)
			this.initDiv (divs[i], true);
	}
    
    //------------------------------------------------------------------------
    // inscore div initialization
	initDiv (div: HTMLElement, v2: boolean) : void {
		let scene = div.id;
		if (!scene) scene = "scene";
		// this.fInscore.postMessageStr ("/ITL/"+scene, "new");	
		this.fInscore.loadInscore ("/ITL/"+scene + " new;");	
		this.allowdrop (div);
		let content = div.innerText;
		div.innerText = "";
		if (content.length) {
// console.log ("initDiv load: " + content);
			if (v2)
				this.fInscore.loadInscore2 (content);
			else
				this.fInscore.loadInscore (content);
		}
	}

    //------------------------------------------------------------------------
    // utilities
    getFileProperties(file: string) {
		let ext 	= file.substring(file.lastIndexOf('.')+1, file.length);
		let name 	= file.substring(0, file.lastIndexOf('.'));
// 		name = this.buildCorrectName(name);
		return { name: name, ext: ext }	
	}

    //------------------------------------------------------------------------
    // load an inscore file
	loadInscore(file: File, v2: boolean) : void {
		let reader = new FileReader();				
		reader.readAsText (file);
		if (v2)
			reader.onloadend = (event) => { this.fInscore.loadInscore2 (reader.result.toString())};
		else
			reader.onloadend = (event) => { this.fInscore.loadInscore (reader.result.toString())};
	}

    //------------------------------------------------------------------------
    // files drop support
	filedropped(e : DragEvent) : void {
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


	drop( e : DragEvent) : void {
		let data = e.dataTransfer.getData("Text");
		if (data)	this.fInscore.loadInscore(data, false);
		else 		this.filedropped (e);
		let div = <HTMLElement>e.target;
		div.style.border = div.getAttribute('savedborder');
	}
		
    //------------------------------------------------------------------------
    // activate drag & drop on inscore divs
	allowdrop (div : HTMLElement) : void {
		div.addEventListener ("dragenter", (event : DragEvent) : void => { div.setAttribute('savedborder', div.style.border);
																	div.style.border = "1px solid grey"; }, false);
		div.addEventListener ("dragleave", (event : DragEvent) : void => { div.style.border = div.getAttribute('savedborder'); }, false);
		div.addEventListener ("dragover",  (event : DragEvent) : void => { event.preventDefault(); }, false);
		div.addEventListener ("drop",      (event : DragEvent) : void=> { event.preventDefault(); this.drop ( event );} , false);
    }    
 }

var gGlue = new INScoreGlue;
