
///<reference path="VHtmlSVG.ts"/>
///<reference path="../model/IRect.ts"/>

class VHtmlRectView extends VHtmlSvg {
    protected fRect: SVGRectElement;
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fRect = document.createElementNS('http://www.w3.org/2000/svg','rect'); 
        this.getHtml().className = "inscore-rect";
    	this.fSVG.appendChild(this.fRect)
    }    

    getSVGTarget() : SVGShape  { return this.fRect; }

	updateView	( obj: IObject) : void {
		super.updateView(obj);
		let size = this.getInnerSize(obj);
        this.updateCommonSVG(obj, size.w, size.h);

        let rect = <IRect>obj;
        let radius = rect.getRadius();
        if (radius) {
	        this.fRect.setAttribute('rx', radius[0].toString());
	        this.fRect.setAttribute('ry', radius[1].toString());
	    }
    }
}