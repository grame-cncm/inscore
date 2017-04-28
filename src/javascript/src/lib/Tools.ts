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
        receiver.onload = () => { 
            let doc = receiver.contentWindow || receiver.contentDocument;
            if (doc.document) doc = doc.document;
            content = doc.getElementsByTagName("body")[0].innerText;
            receiver.remove();
            if (content !== "") success(content);
            else error(content);
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
		let n = str.length+1;
		return '<?xml version="1.0"?>' +
				'<svg width="' + (n*10) + '" height="20"' +
				' xmlns="http://www.w3.org/2000/svg"  version="1.1">' +
				'<g font-family="courier" font-size="10" >' +
				'<text x="10" y="10">' +
				str +'</g></svg>';
	}
}