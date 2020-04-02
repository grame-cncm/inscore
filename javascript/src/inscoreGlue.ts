///<reference path="inscore.ts"/>
///<reference path="libraries.ts"/>

class INScoreDiv {
	fDiv: 		HTMLElement;
	fVersion:	number;			// the inscore lang version supported by the div
	constructor(div: HTMLElement, version: number) {
    	this.fDiv = div;
		this.fVersion = version;
	}
}

//----------------------------------------------------------------------------
class INScoreGlue {
	private fInscore : INScore;
	private fTimeTask : number;
	private fDivs: Array<INScoreDiv>;
	private fLibraries : libraries;

    constructor() {
		this.fInscore = new INScore;
		this.fLibraries = new libraries;
    	this.fTimeTask = 0;
    	this.fInscore.initialise ().then (() => { this.start(); });
    }
	
    //------------------------------------------------------------------------
	// internals
	private getSceneAddress (div: HTMLElement) : string {
		let scene = div.id;
		return "/ITL/" + (scene ? scene : "scene");
	}

	private getInscoreDivs() : void {
		this.fDivs = new Array<INScoreDiv>();
		let divs = document.getElementsByClassName("inscore") as HTMLCollectionOf<HTMLElement>;
		for (let i=0; i<divs.length; i++)
			this.fDivs.push (new INScoreDiv(divs[i], 1));
		divs = document.getElementsByClassName("inscore2") as HTMLCollectionOf<HTMLElement>;
		for (let i=0; i<divs.length; i++)
			this.fDivs.push (new INScoreDiv(divs[i], 2));
	}
	
    //------------------------------------------------------------------------
	// initialization
    start () : void {
		this.fInscore.start();
		this.fLibraries.initialise().then (() => { this.initialise(); });
	}

	initialise () : void {
		this.getInscoreDivs();
		// this.fInscore.start();
		this.fTimeTask = window.setInterval( () => { this.fInscore.timeTask(); }, this.fInscore.getRate());
		for (let i=0; i< this.fDivs.length; i++)
			this.initDiv (this.fDivs[i].fDiv, this.fDivs[i].fVersion==2);
		this.watchResize();
	}
    
    //------------------------------------------------------------------------
	// librairies access
	guido() : GuidoEngine 		{ return this.fLibraries.guido(); }
    
    //------------------------------------------------------------------------
    // inscore div initialization
	initDiv (div: HTMLElement, v2: boolean) : void {
		// do not post the message otherwise content will be loaded before the scene is created
		this.fInscore.loadInscore (this.getSceneAddress(div) + " new;");	
		this.allowdrop (div);
		// this.watchResize (div);
		let content = div.innerText;
		div.innerText = "";
		if (content.length) {
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
		
    //------------------------------------------------------------------------
    // activate drag & drop on inscore divs
	watchResize () : void {
		window.addEventListener ("resize", (e: UIEvent) : void => { 
			for (let i=0; i< this.fDivs.length; i++) {
				this.fInscore.postMessageStr (this.getSceneAddress(this.fDivs[i].fDiv), "refresh");
			}
		});
    }    

}

var gGlue = new INScoreGlue;
