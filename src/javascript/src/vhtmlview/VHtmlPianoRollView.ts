
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlGMNView.ts"/>

class VHtmlPianoRollView extends VHtmlGMNView {
    
    constructor(parent: VHtmlView) {
        super(parent); 
        this.getHtml().className = "inscore-pianoroll";
    }        
	updateObjectSize ( obj: IObject) : void {}  // do nothing, the size is user defined
}