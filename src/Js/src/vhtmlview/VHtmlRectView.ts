
///<reference path="VHtmlView.ts"/>

class VHtmlRectView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( document.createElement('div'), parent); 
    	this.getHtml().className = "inscore-rect";
    }    
}
