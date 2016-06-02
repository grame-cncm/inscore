
///<reference path="../inscore.ts"/>
///<reference path="../model/TILoader.ts"/>
///<reference path="../vhtmlview/VHtmlTools.ts"/>

function dropEvent(e: any) {
    dragOverEvent(e);
	let target = e.target;
	let targetScene: string
	let targetType: string = target.getAttribute("class");
	
	// take target scene
	if (targetType == "inscore-scene") { targetScene = e.target.getAttribute("name"); }
	
	else {
		while (targetType != "inscore-scene") {
			target = target.parentNode;
			targetType = target.getAttribute("class");
		 }
		targetScene = target.getAttribute("name"); 	 
	}	

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
				let properties = getFileProperties(fileName);
				let name 	= properties.name;
				let ext 	= properties.ext.toLocaleLowerCase();
				
				let file = <Blob>filelist[i]
				let reader: FileReader = new FileReader();				
				
				switch (ext) {
					case "txt": case "text": 
						reader.readAsText(file);
						reader.onloadend = _process(reader, targetScene, name, 'txt');
						break;
						
					case "svg":  
						reader.readAsText(file);
						reader.onloadend = _process(reader, targetScene, name, 'svg');
						break;
				
					case "html": case "htm": 
						reader.readAsText(file);
						reader.onloadend = _process(reader, targetScene, name, 'html');
						break;	
						
					case "gmn":  
						reader.readAsText(file);
						reader.onloadend = _process(reader, targetScene, name, 'gmn');
						break;
						
					case "jpg": case "jpeg": case "gif": case "png": case "bmp": case "tiff": 
						INScore.postMessage("/ITL/"+ targetScene + "/" + name, ["set", "img", fileName]);
						break;
						
					case "inscore":
						let loader = new TILoader;
						loader.load(filelist[i], INScore.getRoot());																	
						break;
						
					default:
						reader.readAsText(file);
						reader.onloadend = _process(reader, targetScene, name, 'txt');					
						break;
				}					
				// to do : xml, pianoroll, vidéo, faust		
			}
		}
	}
}	
	
function _process(reader : FileReader, targetScene: string, name: string, type: string) : TLoadEndHandler { 
	return () => {
		let data: string = reader.result;
		INScore.postMessage("/ITL/"+ targetScene + "/" + name, ["set", type, data]);
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
	return name	
}