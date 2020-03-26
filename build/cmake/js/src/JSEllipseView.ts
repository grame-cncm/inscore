
///<reference path="JSSVGView.ts"/>

class JSEllipseView extends JSSvgView {
    protected fEllipse: SVGEllipseElement;
    protected fPixWidth: number;		// the element width in pixels
    protected fPixHeight: number;		// the element height in pixels
    
    constructor(parent: JSObjectView) {
		super(parent);
        this.fEllipse = document.createElementNS('http://www.w3.org/2000/svg','ellipse'); 
        this.getElement().className = "inscore-ellipse";
        this.fSVG.appendChild(this.fEllipse);
    }    

    getSVGTarget() : SVGShape  { return this.fEllipse; }
	toString() : string		   { return "JSEllipseView"; }

    updateSVGDimensions(w: number, h: number) : void {
        let rx = w / 2;
        let ry = h / 2;
        this.fEllipse.setAttribute('cx', rx.toString());
        this.fEllipse.setAttribute('cy', ry.toString());
        this.fEllipse.setAttribute('rx', rx.toString());
        this.fEllipse.setAttribute('ry', ry.toString());
    }
}