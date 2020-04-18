
///<reference path="TFileLoader.ts"/>

interface FileDataPending { () : void }

class TFileBased {

	fContent = "";

	getData (file: string, div: HTMLElement, pending: FileDataPending)	: boolean {
		if (this.fContent == null) return true;	// error while loading file, don't try again
		if (this.fContent.length)  return true;	// done - content is available
		TFileLoader.load (div, file).then ((text: string) => { 
            this.fContent = text;
			pending();
		});
		return false;
	}

	get() : string {
		let content = "";
		if (this.fContent) {
			content = this.fContent;
			this.fContent = "";
		} 
		return content;
	}

}
