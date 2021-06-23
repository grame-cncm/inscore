

class TFileLoader {

	private static getMusicXML(element : any) : string	{ 
		if (element.nodeName == "score-partwise") {
			let content = '<!DOCTYPE score-partwise PUBLIC "-//Recordare//DTD MusicXML 3.1 Partwise//EN" "http://www.musicxml.org/dtds/partwise.dtd">\n';
			let version = element.getAttributeNode('version');
			content += version ? '<score-partwise version="' + version.textContent +'">' : '<score-partwise>';
			content += element.innerHTML;
			content += '</score-partwise>';
			return content;
		}
		console.error ("unsupported MusicXML type " + element.nodeName);
		return null;
	}

	private static getContent(obj: HTMLObjectElement) : string	{ 
		let doc = obj.contentDocument;
		if (! doc) return null;
		
		let content = "";
		let element = doc.documentElement;
		switch (doc.contentType) {
			case "text/plain": 		content = element.innerText; break;
			case "text/html": 		content = element.innerHTML; break;
			case "image/svg+xml": 	content = element.innerHTML; break;
			case "text/xml": 		content = TFileLoader.getMusicXML(element); break;
			default:
				console.log ("Unsupported content type " + doc.contentType);
				content = null;
		}
		obj.parentElement.removeChild (obj);
		return content;
	}

	static load (div: HTMLElement, file: string, mime="text/plain") : Promise <string | null>	{ 
		let obj = document.createElement('object');
		obj.type = mime;
		obj.data = file;
		obj.style.visibility = "hidden";
		div.appendChild (obj);
		return new Promise( function (resolve, failure) {
			obj.addEventListener("error", () => { console.log ("can't open file " + file); failure(null); });
			obj.addEventListener("load",  () => { 
				let content = TFileLoader.getContent (obj); 
				if (content) resolve(content); 
				else failure (null);
			});
		});
	}
}
