
///<reference path="JSSVGBase.ts"/>

class JSArcView extends JSSvgBase
{
    protected fArc   : SVGPathElement;

    constructor(parent: JSObjectView) {
        super(parent);
        this.fArc = document.createElementNS('http://www.w3.org/2000/svg','path');
        this.getElement().className = "inscore-arc";
        this.fSVG.appendChild(this.fArc);
    }
    clone (parent: JSObjectView) : JSObjectView { return new JSArcView(parent); }

	toString() : string			{ return "JSArcView"; }
    getSVGTarget() : SVGShape   { return this.fArc; }

    updateSVGDimensions(w: number, h: number) : void {}

    updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
        let arc = obj.getArcInfos();
        let r1 = this.relative2SceneWidth (arc.width) / 2;
        let r2 = this.relative2SceneHeight (arc.height) / 2;
        if (!r1 || !r2) return false;
        let startAngle  = JSArcView.normalize(arc.start);
        let range       = JSArcView.clip(arc.range);
        let endAngle    = JSArcView.normalize(startAngle + range);
        let startPoint  = JSArcView.getPoint(r1, r2, startAngle );
        let endPoint    = JSArcView.getPoint(r1, r2, endAngle);
        let path        = JSArcView.getPath(range, startPoint, endPoint, r1, r2, arc.closed);
        this.fArc.setAttribute('d', path);
        return true;
    }

    // computes a point coordinates at a given angle
	static getPoint(r1 : number, r2 : number, angle : number) : Point {
        angle = (angle * Math.PI/180);
		let x = r1 * (Math.cos(angle)  + 1);
		let y = r2 * (-Math.sin(angle) + 1);
        return {x, y};
    }

    // gives the arc path string
    static getPath (arcRange : number, start : Point, end : Point, rx : number, ry : number, close : boolean) : string {
        let flag = JSArcView.direction(arcRange);
		let arcStr = start.x + "," + start.y + " A " + rx + "," + ry + ", 0," + flag.sup + "," + flag.dir + " " + end.x + "," + end.y;
		if ( close )
        	 return "M " + rx + "," + ry + " L " + arcStr + " Z ";
        else return "M " + arcStr;
    }

    // normalize the angle between 180 and - 180°
    static normalize(angle : number) : number {
        if (angle > 180)		return this.normalize(angle - 360);
        else if (angle < -180)	return this.normalize(angle + 360);
        return angle;
    }
    
    static clip (range : number) : number {
        if (range >=  360) return  359;
        if (range <= -360) return -359;
        return range;
    }

    // computes the arc directions: up or down, clockwise or counter clockwise
    static direction (arcRange : number) : { sup: number, dir: number } {
        let dir = arcRange > 0 ? 0 : 1;
        arcRange = Math.abs(arcRange);
        let sup = arcRange >=  180 ? 1 : 0;
        return { sup: sup, dir: dir };
    }
}