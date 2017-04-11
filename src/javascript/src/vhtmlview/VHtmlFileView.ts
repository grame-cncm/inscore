///<reference path="VHtmlView.ts"/>
///<reference path="../model/IFile.ts"/>

interface HTMLElement{
    contentDocument : any;
    contentWindow   : any;
}

class VHtmlFilefView extends VHtmlView 
{
    constructor(parent: VHtmlView) {
        super(document.createElement('iframe'), parent); 
        this.getHtml().className = "inscore-file";
    }

    getExtension(path: string): string { return path.substr(path.lastIndexOf('.')) }

	updateView	(obj: IObject) : void {
        let file = <IFile>obj;
        this.getHtml().onload = () => {console.log("VHtmlFileView updateView : " + this.getTextContent())};
        this.getHtml().setAttribute("src", file.fFile);
        super.updateView(obj);
	}

    getTextContent(): string{
        let doc = this.getHtml();
        let content = doc.contentWindow || doc.contentDocument;
        if (content.document) content = content.document;
        let txt = content.getElementsByTagName("body")[0].innerHTML;
        return txt;
    }
}