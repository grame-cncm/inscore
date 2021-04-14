
///<reference path="JSSVGBase.ts"/>

class JSRectView extends JSSvgBase {
    protected fRect: SVGRectElement;
    
    constructor(parent: JSObjectView) {
		super(parent);
        this.fRect = document.createElementNS('http://www.w3.org/2000/svg','rect'); 
        this.getElement().className = "inscore-rect";
    	this.fSVG.appendChild(this.fRect)
    }    
    clone (parent: JSObjectView) : JSObjectView { return new JSRectView(parent); }

    getSVGTarget() : SVGShape   { return this.fRect; }
	toString() : string		    { return "JSRectView"; }

	updateSVGDimensions(w: number, h: number) : void {
        this.fRect.style.width  = w + "px";
        this.fRect.style.height = h + "px";
	}
    getScale(scale: number) : number {  return scale; }
	getSyncRatio()	: number {  return 1; }

    updateSpecific(obj: INScoreObject)	: void { 
        let radius = obj.getRadius();
        this.fRect.setAttribute('rx', radius.x.toString());
        this.fRect.setAttribute('ry', radius.y.toString());
    }
}
