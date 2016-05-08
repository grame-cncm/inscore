
///<reference path="SvgFactory.ts"/>
///<reference path="VHtmlView.ts"/>

class VHtmlRectView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( document.createElement('div'), parent); 
    	let div = this.getDiv();
        div.className = "inscore-rect";
    }    
}
