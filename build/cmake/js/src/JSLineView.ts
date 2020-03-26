
///<reference path="JSSVGView.ts"/>

class JSLineView extends JSSvgView {

    protected fLine: SVGLineElement;

	constructor(parent: JSObjectView) {
		super(parent);
        this.fLine = document.createElementNS('http://www.w3.org/2000/svg','line'); 
        this.getElement().className = "inscore-line";
    	this.fSVG.appendChild(this.fLine)
    }    

    getSVGTarget() : SVGShape  { return this.fLine; }
	toString() : string		   { return "JSLineView"; }

	updateSVGDimensions(w: number, h: number) : void {}

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
		let line = obj.getLineInfos();
		let x = this.relative2SceneWidth (line.x);
		let y = this.relative2SceneWidth (line.y);
		let x0 = 0;
		let y0 = 0;

		if ((x < 0) && (y < 0)) {
			x = -x;
			y = -y;
		} else if (x < 0) {
			y0 = y;
			x = -x;
			y = 0;
		}
		else if (y < 0) {
			y0 = -y;
			y = 0;
		}
		this.fLine.setAttribute('x1', x0.toString());
		this.fLine.setAttribute('x2', x.toString());
		this.fLine.setAttribute('y1', y0.toString());
		this.fLine.setAttribute('y2', y.toString());
		return super.updateSpecial (obj, objid );
	}
}