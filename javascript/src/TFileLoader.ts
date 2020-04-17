

class TFileLoader {

	private static getContent(obj: HTMLObjectElement) : string	{ 

		let doc = obj.contentDocument;
		if (! doc) return "";

		let pre = doc.getElementsByTagName('pre');
		if (pre && pre.length) {
			let content = pre[0].innerText;
			obj.parentElement.removeChild (obj);
			return content;
		}

		let html = doc.getElementsByTagName('html');
		if (html && html.length) {
			let content = html[0].innerHTML;
			obj.parentElement.removeChild (obj);
			return content;
		}

		let svg = doc.getElementsByTagName('svg');
		if (svg && svg.length) {
			let content = svg[0].innerHTML;
			obj.parentElement.removeChild (obj);
			return content;
		}

		let xml = doc.getElementsByTagName('score-partwise');
		if (xml && xml.length) {
			let content = xml[0].innerHTML;
			obj.parentElement.removeChild (obj);
			return content;
		}
		return "";
	}

	static load(div: HTMLElement, file: string) : Promise<string>	{ 
		let type = "text/plain";
		let ext = file.substring(file.lastIndexOf('.')+1, file.length);
		if (ext == "html") type = "text/html";
		let obj = document.createElement('object');
		obj.type = type;
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
