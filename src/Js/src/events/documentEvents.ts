
///<reference path="../inscore.ts"/>
///<reference path="../model/TILoader.ts"/>
///<reference path="../vhtmlview/VHtmlTools.ts"/>

function dropEvent(e: any) {
    dragOverEvent(e);
	var target = e.target;
	var targetScene: string
	var targetType: string = target.getAttribute("class");
	
	if (targetType == "inscore-scene") { targetScene = e.target.getAttribute("name"); }
	
	else {
		while (targetType != "inscore-scene") {
			target = target.parentNode;
			targetType = target.getAttribute("class");
		 }
		targetScene = target.getAttribute("name"); 	 
	}	
	console.log(targetScene);

    let data = e.dataTransfer.getData("Text");
	if (data) {			// check if text has been dropped
		let loader = new TILoader;
		loader.process (data, INScore.getRoot());
	}

	else {				// check if files have been dropped
		let filelist = e.dataTransfer.files;
		if (!filelist) return;
		
		let filecount = filelist.length;
		if (filecount > 0) {
			for (let i = 0; i < filecount; i++ ) {
				let file: string = filelist[i].name;
				let properties = getFileProperties(file);
				let name 	= properties.name;
				let ext 	= properties.ext;
				
				if ( ext == "inscore" ) {
					let loader = new TILoader;
					loader.load(filelist[i], INScore.getRoot());	
				}
				
				else if ( ext == "png" || ext == "jpeg" ) {
					INScore.postMessage("/ITL/"+ targetScene + "/" + name, ["set", "img", file]);	
				}
				
				else {
					let file = <Blob>filelist[i]
					let reader: FileReader = new FileReader();
					reader.readAsText(file);
					reader.onloadend = _process(reader, targetScene);
				}
			}
		}
	}
}	
	
function _process(reader : FileReader, targetScene: string) : TLoadEndHandler { 
   		return () => {
       		let data: string = reader.result;
			INScore.postMessage("/ITL/"+ targetScene + "/" + name, ["set", "txt", data]);
   		}
}

function dragOverEvent(e: any) {
    e.stopPropagation();
    e.preventDefault();
}

function resizeDocument() { INScore.postMessage ("/ITL/*", ["redraw"]); }

function getFileProperties(file: string): { name: string, ext: string } {
	let ext 	= file.substring(file.lastIndexOf('.')+1, file.length);
	let name 	= file.substring(0, file.lastIndexOf('.'));
	name = buildCorrectName(name);
	return { name: name, ext: ext }	
}

function buildCorrectName(name: string): string {
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
	console.log(name);
	return name	
}

/*
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

function buildCorrectName(name: string): string {
	let myRegex = /^[a-zA-Z-_][-_a-zA-Z0-9]+$/.test(name);
	if (!myRegex) {
		let first: string = name.substring(0, 1);
		let myRegex = /^[a-zA-Z-_]$/.test(first);
		if (!myRegex) {
			name = name.substring(1, name.length)
		}
		for (let i =1; i < name.length; i++ ) {
		let myRegex = /^[-_a-zA-Z0-9]$/.test(name[i]);
		if (!myRegex) {
			name = name.replace(name[i], "")
		}	
		}			
	}	
	console.log(name);
	return name	
}
*/