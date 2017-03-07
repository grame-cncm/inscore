
///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/ICurve.ts"/>
///<reference path="../lib/TPoint.ts"/>

class VHtmlCurveView extends VHtmlSvg {
    protected fCurve: 	SVGPathElement;
    protected fStart: 	TPoint;
    protected fEnd: 	TPoint;
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fCurve = document.createElementNS('http://www.w3.org/2000/svg','path'); 
        this.getHtml().className = "inscore-curve";
    	this.fSVG.appendChild(this.fCurve)
		this.fCurve.style.fill = "none";
    }

	getSVGTarget() : SVGShape  { return this.fCurve; }

	getSize (obj: IObject):  {w: number, h: number } {
        let size = this.fCurve.getBBox();        
		let strokeWidth = obj.fPenControl.getPenWidth();
		return { w: size.width + strokeWidth, h: size.height + strokeWidth};
	}

	updateColor (obj: IObject): void {
		let target = this.getSVGTarget();
		let modified = obj.fColor.modified() && obj.getBrushStyle() != "none";
		if (obj.brushModified() && (obj.getBrushStyle() === "none")) {
			target.style.fill = "none";
		}
		else if (modified || (obj.brushModified() && obj.getBrushStyle() == "solid")) {
			target.style.fill = obj.fColor.getRGBAString();
			target.style.fillOpacity = obj.fColor.getSVGA().toString();
		}
	}

	relative2SceneCurve	(curve: BezierCurve) : Array<number> {
		let p = curve.points();
		let a1 = this.relative2SceneWidth (p[0].getX());
		let a2 = this.relative2SceneWidth (p[0].getY());
		let b1 = this.relative2SceneWidth (p[1].getX());
		let b2 = this.relative2SceneWidth (p[1].getY());
		let c1 = this.relative2SceneWidth (p[2].getX());
		let c2 = this.relative2SceneWidth (p[2].getY());
		let d1 = this.relative2SceneWidth (p[3].getX());
		let d2 = this.relative2SceneWidth (p[3].getY());
		let miny = Math.min(a2, d2);
		let minx = miny; //Math.min(a1, d1);
		return [a1-minx, a2-miny, b1-minx, b2-miny, c1-minx, c2-miny, d1-minx, d2-miny ]
	}

	updateView	( obj: IObject) : void {
		let curve = <ICurve>obj;
		if (obj.isNewData()) {
			let points = curve.getPoints();
			for (let i = 0; i < points.length; i++) {
				let p = points[i].points();
				let ps = this.relative2SceneCurve (points[i]);
				this.fStart = new TPoint(ps[0], ps[1]);
				this.fEnd   = new TPoint(ps[6], ps[7]);
				let attributes = 'M' + this.fStart.getX() + ',' + this.fStart.getY() + ' ' + 'C' + ps[2] + ',' + ps[3] + ' ' + ps[4] + ',' + ps[5] + ' ' + this.fEnd.getX() + ',' + this.fEnd.getY();
				this.fCurve.setAttribute('d', attributes);
			}
			this.fCurve.style.transform = this.strokeTranslate(obj);
		}  
		super.updateView(obj);
	}

	innerTranslate  (obj: IObject): {x: number, y: number} {
		let t = super.innerTranslate (obj);
        let size = this.fCurve.getBBox();
		t.x += size.width - this.fEnd.getX();
		t.y += size.height - this.fEnd.getY();
		return t;
	}

	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        let h = this.scene2RelativeHeight(this.fSVG.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
    }	            
}