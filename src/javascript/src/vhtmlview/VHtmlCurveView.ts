
///<reference path="VHtmlSVG.ts"/>
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
    }

	getSVGTarget() : SVGShape  { return this.fCurve; }

	getSize (obj: IObject):  {w: number, h: number } {
        let size = this.fCurve.getBBox();        
		let strokeWidth = obj.fPenControl.getPenWidth();
		return { w: size.width + strokeWidth, h: size.height + strokeWidth};
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

	// method is overriden to fit the object in its bounding box
	innerTranslate  (obj: IObject): {x: number, y: number} {
		let t = super.innerTranslate (obj);
        let size = this.fCurve.getBBox();
        let startx = Math.min( this.fStart.getX(), this.fEnd.getX());
        let endx = Math.max( this.fStart.getX(), this.fEnd.getX());
        let starty = Math.min( this.fStart.getY(), this.fEnd.getY());
        let endy = Math.max( this.fStart.getY(), this.fEnd.getY());

		if ((startx > 0) && (endx > 0))			t.x += -startx;
		else if ((startx < 0) && (endx < 0))	t.x += -endx;
		else 									t.x += size.width - endx;
		if ((starty > 0) && (endy > 0))			t.y += -starty;
		else if ((starty < 0) && (endy < 0))	t.y += -endy;
		else 									t.y += size.height - endy;
		return t;
	}

	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        let h = this.scene2RelativeHeight(this.fSVG.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
    }	            
}