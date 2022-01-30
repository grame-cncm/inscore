
///<reference path="JSSVGBase.ts"/>

class JSSVGView extends JSSvgBase {

	constructor(parent: JSObjectView) {
		super(parent);
	}
	clone (parent: JSObjectView) : JSObjectView { return new JSSVGView(parent); }

	toString() : string		    { return "JSSVGView"; }

	getSVGTarget() : SVGShape   { return this.fSVG; }
	updateSVGDimensions(w: number, h: number) : void { 
		if (!this.fSVG.viewBox.baseVal) {
			// set viewBox dimensions 
			this.fSVG.setAttribute ("viewBox", 0 + " " + 0 + " " + w + " " + h);
		}
	}

	updatePenControl(pen: OPen) : void {	this.updateRegularPen (pen); }

	setSvg (obj: INScoreObject, content: string) : boolean {
		this.fSVG.innerHTML = content;
		let bb = this.fSVG.getBBox();
		this.updateObjectSize (obj, bb.width + bb.x, bb.height + bb.y);
		this.setID (obj);
		obj.ready();
		return true;
	}

	updateSpecial(obj: INScoreObject)	: boolean {
		return this.setSvg(obj, obj.getSVGInfos());
    }
}
