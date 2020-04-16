

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

		
		let svg = doc.getElementsByTagName('svg');
		if (svg && svg.length) {
			let content = svg[0].innerHTML;
			obj.parentElement.removeChild (obj);
			return content;
		}
		return "";
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
