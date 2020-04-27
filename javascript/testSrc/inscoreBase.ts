
///<reference path="../src/lib/inscore.d.ts"/>
///<reference path="constants.ts"/>

class INScoreDiv {
	fDiv: 		HTMLElement;
	fVersion:	number;			// the inscore lang version supported by the div
	constructor(div: HTMLElement, version: number) {
    	this.fDiv = div;
		this.fVersion = version;
	}
}

interface IGlue {
	start():Promise<any>;
}
declare var gGlue: IGlue;

//----------------------------------------------------------------------------
class INScoreBase {
	private fDivs: Array<INScoreDiv>;
	private fExtHandlers: { [id: string] : string; } = {};

    constructor() {
		this.makeExtTable();
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

	getSceneAddress (div: HTMLElement) : string {
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
    // async initialise():Promise<any> { 
    //     var module = INScoreModule();
    //     return new Promise( (success: any, failure: any) => {
    //         module['onRuntimeInitialized'] = () => {
    //             this.moduleInit (module);
    //             success ( this ); 
    //             }
    //     });
	// }
	
	async start () : Promise<any> {
		return new Promise( (success: any, failure: any) => {
			gGlue.start().then (() => { this.initialise(); success(this) });
		});
	}

	initialise () : void {
		this.getInscoreDivs();
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
		inscore.loadInscore (this.getSceneAddress(div) + " new;", false);	
		let content = div.innerText;
		div.innerText = "";
		if (content.length) {
			if (v2)
				inscore.loadInscore2 (content);
			else
				inscore.loadInscore (content, false);
		}
	}

    //------------------------------------------------------------------------
    // utilities
    getFileProperties(file: string) : { name: string, ext: string } {
		let ext 	= file.substring(file.lastIndexOf('.')+1, file.length).toLocaleLowerCase();
		let name 	= file.substring(0, file.lastIndexOf('.'));
		return { name: name, ext: ext }	
	}


    //------------------------------------------------------------------------
    // load an inscore file - called when an inscore file is dropped
	loadFromFile (content: string, v2: boolean, name: string) : void {
		if (v2)
			inscore.loadInscore2 (content);
		else
			inscore.loadInscore (content, true);
	}
    //------------------------------------------------------------------------
    // load an inscore script - called when text is dropped
	loadFromText (content: string, v2: boolean) : void {
		inscore.loadInscore (content, true);
	}

    //------------------------------------------------------------------------
    // load an inscore file
	loadInscore(file: File, v2: boolean) : void {
		let reader = new FileReader();				
		reader.readAsText (file);
		reader.onloadend = (event) => { this.loadFromFile (reader.result.toString(), v2, file.name)};
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
	private loadTextFile (file: File, type:string, dest: string) : void {
		let reader = new FileReader();				
		reader.readAsText (file);
		reader.onloadend = (event) => {
			let msg = inscore.newMessageM ("set");
			inscore.msgAddStr (msg, type);
			inscore.msgAddStr (msg, reader.result.toString());
			inscore.postMessage (dest, msg);
		};
	}

	//------------------------------------------------------------------------
    // load an arbitrary file
	private loadFile (file: File, fileName: string, type:string, div: HTMLElement) : void {
		let dst = this.getSceneAddress(div) + "/" + this.fileName2InscoreName (fileName);
		switch (type) {
			case kGuidoCodeType: 
			case kMusicxmlType:
			case kSvgType:
			case kHtmlType:
			case kTextType:
				this.loadTextFile (file, type, dst);
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
		}
	}

	drop( e : DragEvent) : void {
		let data = e.dataTransfer.getData("Text");
		if (data)	this.loadFromText (data, true);
		// if (data)	inscore.loadInscore(data, false);
		else 		this.filedropped (e);
		let div = <HTMLElement>e.target;
		div.style.border = div.getAttribute('savedborder');
	}
		
    //------------------------------------------------------------------------
    // activate drag & drop on inscore divs
	accept (event : DragEvent) : boolean	{ return true; }
	dragEnter (event : DragEvent) : void	{}
	dragLeave (event : DragEvent) : void	{}
	
	allowdrop (div : HTMLElement) : void {
		div.addEventListener ("dragenter", (event : DragEvent) : void => { if (this.accept(event)) this.dragEnter(event); }, true);
		div.addEventListener ("dragleave", (event : DragEvent) : void => { this.dragLeave(event); }, true);
		div.addEventListener ("dragover",  (event : DragEvent) : void => { event.preventDefault(); }, true);
		div.addEventListener ("drop",      (event : DragEvent) : void => { this.dragLeave(event); this.drop ( event );} , true);
    }
		
    //------------------------------------------------------------------------
    // activate drag & drop on inscore divs
	private watchResize () : void {
		window.addEventListener ("resize", (e: UIEvent) : void => { 
			for (let i=0; i< this.fDivs.length; i++) {
				inscore.postMessageStr (this.getSceneAddress(this.fDivs[i].fDiv), "refresh");
			}
		});
    }
}
