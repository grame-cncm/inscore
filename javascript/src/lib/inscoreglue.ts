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
abstract class INScoreGlue {
	private fInscore : INScore;
	private fTimeTask : number;
	private fSorterTask : number;
	private fDivs: Array<INScoreDiv>;
	private fExtHandlers: { [id: string] : string; } = {};

    constructor() {
		this.fInscore = new INScore;
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
        this.fExtHandlers["musicxml"]	= kMusicxmlType;
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

		this.fExtHandlers["inscore"] 		= kInscore;
		this.fExtHandlers["inscore2"] 		= kInscore2;
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
		inscorelibs.initialise().then (() => { this.initialise(); });
	}

	initialise () : void {
		this.getInscoreDivs();
		this.fTimeTask = window.setInterval( () => { this.fInscore.timeTask(); }, this.fInscore.getRate());
		this.fSorterTask = window.setInterval( () => { this.fInscore.sorterTask(); }, 1);
		for (let i=0; i< this.fDivs.length; i++) {
			this.initDiv (this.fDivs[i].fDiv, this.fDivs[i].fVersion==2);
			this.allowdrop (this.fDivs[i].fDiv);
		}
		this.watchResize();
	}
    
    //------------------------------------------------------------------------
    // inscore div initialization
	initDiv (div: HTMLElement, v2: boolean) : void {
		// do not post the message otherwise content will be loaded before the scene is created
		this.fInscore.loadInscore (this.getSceneAddress(div) + " new;");	
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
		let ext 	= file.substring(file.lastIndexOf('.')+1, file.length).toLocaleLowerCase();
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
	private fileName2InscoreName(name: string): string {
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
	private loadText (file: File, type:string, dest: string) : void {
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
			case kGuidoCodeType: 
			case kMusicxmlType:
			case kSvgType:
			case kHtmlType:
			case kTextType:
				this.loadText (file, type, dst);
				break;

			case kFaustType:
			case kVerovioType:
			case kImgType:
			case kVideoType:
				break;
		}
	}

    //------------------------------------------------------------------------
    // files drop support
	fileTypes( e: DragEvent) : Array<string> {
		let filelist = e.dataTransfer.files;
		if (!filelist) return null;

		let out = new Array<string>();
		let filecount = filelist.length;
console.log ("fileTypes : " +filecount);
		for (let i = 0; i < filecount; i++ ) {
			const properties = this.getFileProperties(filelist[i].name);
			out.push (this.fExtHandlers[properties.ext]);
		}
		return out;
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
			let type = this.fExtHandlers[properties.ext];
			switch (type) {
				case kInscore: 	this.loadInscore (file, false);
					break;
				case kInscore2: this.loadInscore (file, true);
					break;
				default:		this.loadFile (file, fileName, type, <HTMLElement>e.target);
					break;
			}
			// if (properties.ext == "inscore") 	   this.loadInscore (file, false);
			// else if (properties.ext == "inscore2") this.loadInscore (file, true);
			// else {
			// 	let type = this.fExtHandlers[properties.ext];
			// 	this.loadFile (file, fileName, type, <HTMLElement>e.target);
			// }
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
	abstract accept (event : DragEvent) : boolean;
	abstract dragEnter (event : DragEvent) : void;
	abstract dragLeave (event : DragEvent) : void;
	
	allowdrop (div : HTMLElement) : void {
		div.addEventListener ("dragenter", (event : DragEvent) : void => { if (this.accept(event)) this.dragEnter(event); }, true);
		div.addEventListener ("dragleave", (event : DragEvent) : void => { this.dragLeave(event); }, true);
		div.addEventListener ("dragover",  (event : DragEvent) : void => { event.preventDefault(); }, true);
		div.addEventListener ("drop",      (event : DragEvent) : void=> { event.preventDefault(); this.drop ( event );} , true);
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
