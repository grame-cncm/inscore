///<reference path="inscore.ts"/>
///<reference path="libraries.ts"/>
///<reference path="constants.ts"/>

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
	private fExtHandlers: { [id: string] : string; } = {};

    constructor() {
		this.fInscore = new INScore;
		this.fLibraries = new libraries;
		this.fTimeTask = 0;
		this.makeExtTable();
		this.fInscore.initialise ().then (() => { this.start(); });
    }
	
    //------------------------------------------------------------------------
	// internals
    private makeExtTable(): void {
        this.fExtHandlers["txt"] 		= kTextType;
        this.fExtHandlers["text"] 		= kTextType;
        this.fExtHandlers["mei"]		= kVerovioType;
        this.fExtHandlers["xml"]		= kMusicxmlType;
        this.fExtHandlers["svg"]		= kSvgType;
        this.fExtHandlers["html"] 		= kHtmlType;
		this.fExtHandlers["htm"] 		= kHtmlType;
		this.fExtHandlers["gmn"] 		= kGuidoCodeType;
		this.fExtHandlers["dsp"] 		= kFaustType;
		this.fExtHandlers["jpg"] 		= kImgType;
		this.fExtHandlers["jpeg"] 		= kImgType;
		this.fExtHandlers["gif"] 		= kImgType;
		this.fExtHandlers["png"] 		= kImgType;
		this.fExtHandlers["bmp"] 		= kImgType;
		this.fExtHandlers["tiff"] 		= kImgType;
		this.fExtHandlers["wmv"] 		= kVideoType;
		this.fExtHandlers["avi"] 		= kVideoType;
		this.fExtHandlers["mpg"] 		= kVideoType;
		this.fExtHandlers["mpeg"] 		= kVideoType;
		this.fExtHandlers["mp4"] 		= kVideoType;
		this.fExtHandlers["m4v"] 		= kVideoType;
		this.fExtHandlers["mov"] 		= kVideoType;
		this.fExtHandlers["vob"] 		= kVideoType;		
    }

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
	// inscore access
    inscore() : INScore			{ return this.fInscore; }

	//------------------------------------------------------------------------
	// librairies access
	guido()  : GuidoEngine 		{ return this.fLibraries.guido(); }
	guidoversion() : number 	{ return this.guido() ? this.guido().getFloatVersion() : 0; }
	xmllib() : libmusicxml 		{ return this.fLibraries.xmllib(); }
	xmllibversion() : number 	{ return this.xmllib() ? this.xmllib().libVersion() : 0; }
    
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
	// build a receivable name for an INScore object
	fileName2InscoreName(name: string): string {
		let myRegex = /^[a-zA-Z-_][-_a-zA-Z0-9]+$/.test(name);
		if (!myRegex) {
			let first: string = name[0];
			let myRegex = /^[0-9]$/.test(first);
			if (myRegex) {
				name = '_' + name;
			}
			for (let i =1; i < name.length; i++ ) {
				let myRegex = /^[-_a-zA-Z0-9]$/.test(name[i]);
				if (!myRegex) {
					name = name.replace(name[i], "_");
				}	
			}			
		}	
		return name	
	}

	//------------------------------------------------------------------------
    // load an arbitrary file
	loadText (file: File, type:string, dest: string) : void {
		let reader = new FileReader();				
		reader.readAsText (file);
		reader.onloadend = (event) => {
			let msg = this.fInscore.newMessageM ("set");
			this.fInscore.msgAddStr (msg, type);
			this.fInscore.msgAddStr (msg, reader.result.toString());
			this.fInscore.postMessage (dest, msg);
		};
	}

	//------------------------------------------------------------------------
    // load an arbitrary file
	loadFile (file: File, fileName: string, type:string, div: HTMLElement) : void {
		let dst = this.getSceneAddress(div) + "/" + this.fileName2InscoreName (fileName);
		switch (type) {
			case kFaustType:
				break;
			case kGuidoCodeType: 
			case kMusicxmlType:
			case kSvgType:
			case kHtmlType:
			case kTextType:
			case kVerovioType:
				this.loadText (file, type, dst);
				break;

			case kImgType:
				break;
			case kVideoType:		
				break;
		}
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
				let type = this.fExtHandlers[ext];
				this.loadFile (file, fileName, type, <HTMLElement>e.target);
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
