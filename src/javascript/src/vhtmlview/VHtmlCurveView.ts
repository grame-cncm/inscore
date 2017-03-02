
///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/ICurve.ts"/>

class VHtmlCurveView extends VHtmlSvg {
    protected fCurve: SVGPathElement;
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fCurve = document.createElementNS('http://www.w3.org/2000/svg','path'); 
        this.getHtml().className = "inscore-curve";
    	this.fSVG.appendChild(this.fCurve) 
    } 

	getSize (obj: IObject):  {w: number, h: number } {
        let size = this.fCurve.getBBox();        
		return { w: size.width, h: size.height };
	}

	relative2SceneCurve	(curve: BezierCurve) : Array<number> {
		let p = curve.points();
		let a1 = this.relative2SceneX (p[0].getX());
		let a2 = this.relative2SceneY (p[0].getY());
		let b1 = this.relative2SceneX (p[1].getX());
		let b2 = this.relative2SceneY (p[1].getY());
		let c1 = this.relative2SceneX (p[2].getX());
		let c2 = this.relative2SceneY (p[2].getY());
		let d1 = this.relative2SceneX (p[3].getX());
		let d2 = this.relative2SceneY (p[3].getY());
		let minx = Math.min(a1, d1);
		let miny = Math.min(a2, d2);
		return [a1-minx, a2-miny, b1-minx, b2-miny, c1-minx, c2-miny, d1-minx, d2-miny ]
	}

	updateView	( obj: IObject) : void {
		let curve = <ICurve>obj;
		if (obj.isNewData()) {
			let points = curve.getPoints();
			let minx = 0x1fffffff;
			let miny = 0x1fffffff;
			for (let i = 0; i < points.length; i++) {
				let p = points[i].points()
				minx = Math.min(minx, p[i].getX());
				miny = Math.min(miny, p[i].getY());
			}

			for (let i = 0; i < points.length; i++) {
				let p = points[i].points();
				let ps = this.relative2SceneCurve (points[i]);
				let attributes = 'M' + ps[0] + ',' + ps[1] + ' ' + 'C' + ps[2] + ',' + ps[3] + ' ' + ps[4] + ',' + ps[5] + ' ' + ps[6] + ',' + ps[7];
				this.fCurve.setAttribute('d', attributes);
			}
			this.fCurve.style.fillOpacity = "0";
		}  
		super.updateView(obj);
	}

	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        let h = this.scene2RelativeHeight(this.fSVG.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
    }	            
}