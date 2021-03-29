
///<reference path="JSSVGBase.ts"/>

class JSCurveView extends JSSvgBase {
    protected fCurve: 	SVGPathElement;
    // protected fStart: 	TPoint;
    // protected fEnd: 	TPoint;
    
    constructor(parent: JSObjectView) {
		super(parent);
        this.fCurve = document.createElementNS('http://www.w3.org/2000/svg','path'); 
        this.getElement().className = "inscore-curve";
    	this.fSVG.appendChild(this.fCurve)
    }
	clone (parent: JSObjectView) : JSObjectView { return new JSCurveView(parent); }

	toString() : string			{ return "JSCurveView"; }
	getSVGTarget() : SVGShape   { return this.fCurve; }
	updateSVGDimensions(w: number, h: number) : void {}

	updateSpecial ( obj: INScoreObject)	: boolean {		
		let curve = obj.getCurveInfos();
		let n = curve.size();
		for (let i=0; i < (n-7); i+=8) {
			let ps = this.relative2SceneCurve (curve.get(i), curve.get(i+1), curve.get(i+2), curve.get(i+3), curve.get(i+4), curve.get(i+5), curve.get(i+6), curve.get(i+7)); 
			this.fCurve.setAttribute('d', `M${ps[0]},${ps[1]} C${ps[2]},${ps[3]} ${ps[4]},${ps[5]} ${ps[6]},${ps[7]}`);

			// update object size
			let bb = this.fSVG.getBBox();
-			this.updateObjectSizeSync (obj, bb.width, bb.height);
		}
		return true;
	}

	relative2SceneCurve	(x1: number, y1: number, x2: number, y2: number, x3: number, y3: number, x4: number, y4: number) : Array<number> {
		let a1 = this.relative2SceneWidth (x1);
		let a2 = this.relative2SceneWidth (y1);
		let b1 = this.relative2SceneWidth (x2);
		let b2 = this.relative2SceneWidth (y2);
		let c1 = this.relative2SceneWidth (x3);
		let c2 = this.relative2SceneWidth (y3);
		let d1 = this.relative2SceneWidth (x4);
		let d2 = this.relative2SceneWidth (y4);
		let miny = Math.min(a2, d2);
		let minx = Math.min(a1, d1);
		return [a1-minx, a2-miny, b1-minx, b2-miny, c1-minx, c2-miny, d1-minx, d2-miny ]
	}
}