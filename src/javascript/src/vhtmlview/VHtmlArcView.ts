///<reference path="VHtmlSvg.ts"/>
///<reference path="../lib/TPoint.ts"/>
///<reference path="../model/IArc.ts"/>


class VHtmlArcView extends VHtmlSvg
{
    protected fArc   : SVGPathElement;

    constructor(parent: VHtmlView)
    {
        super(parent);
        this.fArc = document.createElementNS('http://www.w3.org/2000/svg','path');
        this.getHtml().className = "inscore-arc";
        this.fSVG.appendChild(this.fArc)
    }

    getSVGTarget() : SVGShape  { return this.fArc; }

    updateView( obj: IObject) : void
    {
    	super.updateView (obj);
		let size = this.getInnerSize(obj);
        this.updateCommonSVG (obj, size.w, size.h);

        const arc = <IArc>obj;
        let r1  = size.w / 2;
        let r2  = size.h / 2;
        let startAngle  = this.normalize(arc.getStart());
        let endAngle    = this.normalize(startAngle + this.clip(arc.getRange()));
        let startPoint  = this.getPoint(r1, r2, startAngle );
        let endPoint    = this.getPoint(r1, r2, endAngle);
        let path        = this.getPath(this.clip(arc.getRange()), startPoint, endPoint, r1, r2, arc.getClose() ? true : false);
		this.fArc.setAttribute('d', path);
    }

    // computes a point coordinates at a given angle
	getPoint(r1 : number, r2 : number, angle : number) : TPoint
    {
        angle = (angle * Math.PI/180);
		let x = r1 * (Math.cos(angle)  + 1);
		let y = r2 * (-Math.sin(angle) + 1);
        return new TPoint(x, y);
    }

    // gives the arc path string
    getPath (arcRange : number, start : TPoint, end : TPoint, rx : number, ry : number, close : boolean) : string
    {
        //values setting
        arcRange = this.clip(arcRange);
        let flag = this.direction(arcRange);
		let arcStr = start + " A " + rx + "," + ry + ", 0," + flag.sup + "," + flag.dir + " " + end;
		if ( close )
        	 return "M " + rx + "," + ry + ", L " + arcStr + " Z ";
        else return "M " + arcStr;
    }

    // normalize the angle between 180 and - 180°
    normalize(angle : number) : number
    {
        if (angle > 180)		return this.normalize(angle - 360);
        else if (angle < -180)	return this.normalize(angle + 360);
        return angle;
    }
    
    clip (range : number) : number
    {
        if (range >=  360) return  359;
        if (range <= -360) return -359;
        return range;
    }

    // computes the arc directions: up or down, clockwise or counter clockwise
    direction (arcRange : number) : { sup: number, dir: number }
    {
        let dir = arcRange > 0 ? 0 : 1;
        arcRange = Math.abs(arcRange);
        let sup = arcRange >=  180 ? 1 : 0;
        return { sup: sup, dir: dir };
    }
}