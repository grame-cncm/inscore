
///<reference path="../inscore.ts"/>
///<reference path="../model/TILoader.ts"/>
///<reference path="../vhtmlview/VHtmlTools.ts"/>

class dropLoader {
	protected fTarget 		: any;
	protected fTargetType	: string;
	protected fTargetScene	: string;

	protected fExtHandlers = new Array<string>();
	
	constructor (target: any) {
		this.fTarget 		= target;
		this.fTargetType 	= target.getAttribute("class");	
		
		this.setHandlers();	
	}
	
    setHandlers(): void {
        this.fExtHandlers["txt"] 		= "txt";
        this.fExtHandlers["text"] 		= "txt";
        this.fExtHandlers["svg"]		= "svg";
        this.fExtHandlers["html"] 		= "html";
		this.fExtHandlers["htm"] 		= "html";
		this.fExtHandlers["gmn"] 		= "gmn";
		this.fExtHandlers["jpg"] 		= "img";
		this.fExtHandlers["jpeg"] 		= "img";
		this.fExtHandlers["gif"] 		= "img";
		this.fExtHandlers["png"] 		= "img";
		this.fExtHandlers["bmp"] 		= "img";
		this.fExtHandlers["tiff"] 		= "img";
		this.fExtHandlers["inscore"] 	= "inscore";		
    }
		
	processLoader (e: any) {
		this.fTargetScene = this.targetScene();	

		// check if text has been dropped
		let data = e.dataTransfer.getData("Text");
		if (data) {			
			let loader = new TILoader;
			loader.process (data, INScore.getRoot());
		}

		// check if files have been dropped
		else {	
			let filelist = e.dataTransfer.files;
			if (!filelist) return;
			
			let filecount = filelist.length;
			if (filecount > 0) {
				for (let i = 0; i < filecount; i++ ) {
					let fileName: string = filelist[i].name;
 					let properties = this.getFileProperties(fileName);
					let name 	= properties.name;
					let ext 	= properties.ext.toLocaleLowerCase();
					
					let file = <Blob>filelist[i]
					let reader: FileReader = new FileReader();				
					
					if (this.fExtHandlers[ext] == "img") {
						INScore.postMessage("/ITL/"+ this.fTargetScene + "/" + name, ["set", "img", fileName]);
					}
					
					else if (this.fExtHandlers[ext] == "inscore") {
						let loader = new TILoader;
						loader.load(filelist[i], INScore.getRoot());							
					}
					
					else {
						reader.readAsText(file);
						if (! this.fExtHandlers[ext]) { this.fExtHandlers[ext] = "txt"; }
						reader.onloadend = this._processMsg(reader, this.fTargetScene, name, this.fExtHandlers[ext]);						
					}	
					// to do : xml, pianoroll, vidéo, faust		
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