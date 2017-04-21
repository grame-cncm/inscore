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
    // Actually error doesn't catch anything
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
}