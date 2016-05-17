
///<reference path="VHtmlView.ts"/>

class VHtmlSvg extends VHtmlView {
    protected fSVG: 	SVGSVGElement;
    
    constructor(parent: VHtmlView) {
    	super (document.createElement('div'), parent);
        this.fSVG = document.createElementNS('http://www.w3.org/2000/svg','svg');
        this.fSVG.setAttribute('xmlns', "http://www.w3.org/2000/svg");
        this.fSVG.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
        this.fSVG.setAttribute('version', "1.1");
    	this.getHtml().appendChild(this.fSVG);
	}
}


        
       
