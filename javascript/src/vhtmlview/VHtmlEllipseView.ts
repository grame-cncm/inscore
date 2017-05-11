
///<reference path="VHtmlSVG.ts"/>
///<reference path="../model/IEllipse.ts"/>

class VHtmlEllipseView extends VHtmlSvg {
    protected fEllipse: SVGEllipseElement;
    protected fPixWidth: number;		// the element width in pixels
    protected fPixHeight: number;		// the element height in pixels
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fEllipse = document.createElementNS('http://www.w3.org/2000/svg','ellipse'); 
        this.getHtml().className = "inscore-ellipse";
    	this.fSVG.appendChild(this.fEllipse)
    }    

    getSVGTarget() : SVGShape  { return this.fEllipse; }

	updateView	( obj: IObject) : void {
		super.updateView (obj);
		let size = this.getInnerSize(obj);
        this.updateCommonSVG(obj, size.w, size.h);
		let rx = size.w/2;
		let ry = size.h/2;
        this.fEllipse.setAttribute('cx', rx.toString());
        this.fEllipse.setAttribute('cy', ry.toString());
        this.fEllipse.setAttribute('rx', rx.toString());
        this.fEllipse.setAttribute('ry', ry.toString());
	}
}