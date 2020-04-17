
///<reference path="TFileLoader.ts"/>

interface FileDataPending { () : void }

class TFileBased {

	fContent = "";

	getData (file: string, div: HTMLElement, pending: FileDataPending)	: boolean {
		if (this.fContent) return true;
		TFileLoader.load (div, file).then ((text: string) => { 
            this.fContent = text;
            pending();
		});
		return false;
	}

	get() : string {
		let content = this.fContent;
		this.fContent = "";
		return content;
	}

}
