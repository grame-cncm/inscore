
///<reference path="../inscore.ts"/>
///<reference path="../model/Constants.ts"/>
///<reference path="../vhtmlview/VHtmlTools.ts"/>

class dropLoader {
	protected fTarget 		: any;
	protected fTargetType	: string;
	protected fTargetScene	: string;

	protected fExtHandlers: { [id: string] : string; } = {};
	
	constructor (target: any) {
		this.fTarget 		= target;
		this.fTargetType 	= target.getAttribute("class");	
		
		this.buildObjectExtensions();	
	}
	
    buildObjectExtensions(): void {
        this.fExtHandlers["txt"] 		= kTextType;
        this.fExtHandlers["text"] 		= kTextType;
        this.fExtHandlers["mei"]		= kVerovioType;
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
		
	processLoader (e: any) {
		this.fTargetScene = this.targetScene();	

		// check if text has been dropped
		let data = e.dataTransfer.getData("Text");
		if (data) { 
			INScore.load(data); 
		}

		// check if files have been dropped
		else {	
			let filelist = e.dataTransfer.files;
			if (!filelist) return;
			
			let filecount = filelist.length;
			for (let i = 0; i < filecount; i++ ) {
				let file 	= <Blob>filelist[i]
				let fileName: string = filelist[i].name;
				let properties = this.getFileProperties(fileName);
				let name 	= properties.name;
				let ext 	= properties.ext.toLocaleLowerCase();
/*
console.log("relative path: " + filelist[i].webkitRelativePath);
console.log("doc url: " + document.URL);
*/				
				if (ext == kInscoreFile) { INScore.load (file); }
/*
				else {
					let type = this.fExtHandlers[ext];
					if (!type) type = kTextType;
					INScore.postMessage("/ITL/"+ this.fTargetScene + "/" + name, ["set", type, fileName]);
					console.log ("post /ITL/"+ this.fTargetScene + "/" + name + "set "+ type + " " + fileName);
				}
*/
				else if ((this.fExtHandlers[ext] == kImgType) 
						|| (this.fExtHandlers[ext] == kVideoType) 
						|| (this.fExtHandlers[ext] == kFaustType)) {
					INScore.postMessage("/ITL/"+ this.fTargetScene + "/" + name, ["set", this.fExtHandlers[ext], fileName]);
				}
				
				else {
					let reader: FileReader = new FileReader();				
					reader.readAsText(file);
					if (! this.fExtHandlers[ext]) { this.fExtHandlers[ext] = kTextType; }
					reader.onloadend = this._processMsg(reader, this.fTargetScene, name, this.fExtHandlers[ext]);						
				}	
			}
		}
	}

	// take target scene
	targetScene() {
		let targetScene	: string; 
		let targetType = this.fTargetType
		let target = this.fTarget;
		if (targetType == "inscore-scene") { targetScene = this.fTarget.getAttribute("name"); }
		
		else {
			while (targetType != "inscore-scene") {
				target = target.parentNode;
				targetType = target.getAttribute("class");
			}
			targetScene = target.getAttribute("name"); 	 
		}
		
		return targetScene;
	}


	// take the name and the extension of the dropped file
	getFileProperties(file: string): { name: string, ext: string } {
		let ext 	= file.substring(file.lastIndexOf('.')+1, file.length);
		let name 	= file.substring(0, file.lastIndexOf('.'));
		name = this.buildCorrectName(name);
		return { name: name, ext: ext }	
	}

	// build a receivable name for an INScore object
	buildCorrectName(name: string): string {
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
	
	_processMsg(reader : FileReader, targetScene: string, name: string, type: string) : TLoadEndHandler { 
		return () => {
			let data: string = reader.result;
			INScore.postMessage("/ITL/"+ targetScene + "/" + name, ["set", type, data]);
		}
	}	
	
}


// Event functions
//--------------------------------
function inscore_dropEvent(e: any) {
    inscore_dragOverEvent(e);
	let loader = new dropLoader(e.target);
	loader.processLoader(e);
}


function inscore_dragOverEvent(e: any) {
    e.stopPropagation();
    e.preventDefault();
}

function inscore_resizeDocument() { INScore.postMessage ("/ITL/*", ["redraw"]); }