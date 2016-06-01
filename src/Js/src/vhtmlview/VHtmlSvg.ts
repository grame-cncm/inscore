
///<reference path="../model/IObject.ts"/>
///<reference path="VHtmlView.ts"/>

class VHtmlSvg extends VHtmlView {
    protected fSVG: 	SVGSVGElement;
	protected fPixWidth: number;		// the element width in pixels
    protected fPixHeight: number;		// the element height in pixels
   
    constructor(parent: VHtmlView) {
    	super (document.createElement('div'), parent);
        this.fSVG = document.createElementNS('http://www.w3.org/2000/svg','svg');
        this.fSVG.setAttribute('xmlns', "http://www.w3.org/2000/svg");
        this.fSVG.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
        this.fSVG.setAttribute('version', "1.1");
    	this.getHtml().appendChild(this.fSVG);
	}
	
	updateSvgSize (w: number, h: number): void { 
    	let elt = this.getHtml();
		this.fPixWidth = w ? w : 1; 
		this.fPixHeight = h ? h : 1; 		
		elt.style.height = this.fPixHeight +"px";
        elt.style.width  = this.fPixWidth +"px";
		this.fSVG.style.height = this.fPixHeight +"px";
        this.fSVG.style.width  = this.fPixWidth +"px";
	}
}


        
       
