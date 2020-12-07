
///<reference path="JSSVGBase.ts"/>

class JSSVGView extends JSSvgBase {

	constructor(parent: JSObjectView) {
		super(parent);
		this.getElement().className = "inscore-svg";
	}
	clone (parent: JSObjectView) : JSObjectView { return new JSSVGView(parent); }

	toString() : string		    { return "JSSVGView"; }

	getSVGTarget() : SVGShape   { return this.fSVG; }
	updateSVGDimensions(w: number, h: number) : void { }
	updatePenControl(pen: OPen) : void {	this.updateRegularPen (pen); }

	setSvg (obj: INScoreObject, content: string) : boolean {
		this.fSVG.innerHTML = content;
		let bb = this.fSVG.getBBox();
		this.updateObjectSizeSync (obj, bb.width + bb.x, bb.height + bb.y);
		obj.ready();
		return true;
	}

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		return this.setSvg(obj, obj.getSVGInfos());
    }
}
