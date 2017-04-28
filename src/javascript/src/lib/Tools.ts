///<reference path="TTypes.ts"/>

// Need those interfaces for readFile method
// Document.document and Window.getElementsByTagName recognized by browsers, but not in typescript
interface Document 	{ document : Document; }
interface Window 	{ getElementsByTagName(tag: string): any; }

class Tools {
    
    static regexp (str: string): boolean
    {
        let n = str.length;
        for (let i = 0; i < n; i++) {
        	let c = str[i];
            if ((c == '*') || (c == '?') || (c == '[') || (c == '{'))
                return true;
        }
        return false;
    }

    // Read file content
    // Actually error does not catch anything
    static readFile(src: string, success: TReadHandler, error: TReadHandler): void {
        let content: string = "";
        let receiver = document.createElement("iframe");
        receiver.style.display = "none";
        receiver.onerror = function() { console.log ('error: failed to load ' + src) } ;
        receiver.onabort = function() { console.log ('abort: failed to load ' + src) } ;
        receiver.onload = () => { 
            let doc = receiver.contentWindow || receiver.contentDocument;
            let title = doc.document.title;
            if (doc.document) doc = doc.document;
            content = doc.getElementsByTagName("body")[0].innerText;
            receiver.remove();
            if ((title === "404 Not Found") || (content.indexOf ("Not Found") == 0))
            	error(content);
            else success(content);
        }
        receiver.src = src;
        document.body.appendChild (receiver);
    }

    // Handling a set file message
    static setFile(msg: IMessage, success: TReadHandler, error: TReadHandler): string { 
        let n = msg.size();
        if (n == 3) {
        	let file = msg.paramStr(2);
        	if (file.correct) {
                Tools.readFile(file.value, success, error);
	            return file.value;
        	}
        }
        return null;
    }

	static string2svg (str: string) : string {
		let n = str.length;
		let header = '<svg  width="'+ n*6 + '" height="14" ';
		return header + 'xmlns="http://www.w3.org/2000/svg"  version="1.1"> <g  font-family="courier" font-size="10"><text x="0" y="10">' + str +'</text></g></svg>';
	}

	static error2svg() : string  {
		return '<svg width="68" height="68" xmlns="http://www.w3.org/2000/svg"><g>' +
			'<rect rx="5" height="64" width="64" y="2" x="2" stroke-width="4" stroke="#000" fill="#e00"/>' +
			'<rect rx="4" height="14" width="34" y="26" x="17" stroke-width="0" fill="#fff"/></g></svg>';

//		return '<svg width="128" height="128" xmlns="http://www.w3.org/2000/svg"><g>' +
			'<rect rx="5" height="124" width="124" y="2" x="2" stroke-width="4" stroke="#000" fill="#e00"/>' +
			'<rect rx="5" height="24" width="64" y="52" x="32" stroke-width="0" fill="#fff"/></g></svg>';
	}
}