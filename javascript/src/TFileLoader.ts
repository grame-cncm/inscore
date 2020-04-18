

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

		let element = doc.documentElement;
		switch (doc.contentType) {
			case "text/plain": 		return element.innerText; break;
			case "text/html": 		return element.innerHTML; break;
			case "image/svg+xml": 	return element.innerHTML; break;
			case "text/xml": 		return TFileLoader.getMusicXML(element); break;
			default:
				console.error ("Unsupported content type " + doc.contentType);
		}
		return null;
	}

	static load(div: HTMLElement, file: string) : Promise<string>	{ 
		let obj = document.createElement('object');
		obj.type = "text/plain";
		obj.data = file;
		obj.style.visibility = "hidden";
		div.appendChild (obj);
		return new Promise(function (resolve, failure) {
			obj.addEventListener("error", () => { console.error ("can't open file " + file); });
			obj.addEventListener("load", () => {
				let content = TFileLoader.getContent (obj);
				resolve(content);
			});
		});
	}
}
