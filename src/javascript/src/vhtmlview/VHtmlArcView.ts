///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/IArc.ts"/>

//Set arcs parameters
class ArcParams
{
    //Params to create the SVG path
    fStart     : Array<number> = [0,0];
    fEnd       : Array<number> = [0,0];
    fRX        : number;
    fRY        : number;
    fLine      : Array<number>;
    fArcFlags  : Array<number> = [0,0];
    fClose     : number;

    getArcs(start : Array<number>, line : Array<number>, rX : number, rY : number, arcFlags : Array<number>, end : Array<number>, close : number)
    {
        this.fStart     = start;
        this.fEnd       = end;
        this.fRX        = rX;
        this.fRY        = rY;
        this.fLine      = line;
        this.fArcFlags  = arcFlags;
        this.fClose     = close;
    }

    toArray (): Array<any> 	{
        if ( this.fClose == 0)
        {
              return ["M " + this.fStart + "A " + this.fRX, this.fRY, "0", this.fArcFlags , this.fEnd];
        }else return ["M " + this.fLine," L " + this.fStart + "A " + this.fRX, this.fRY, "0", this.fArcFlags , this.fEnd + " Z "]; }
    toString(): string 	    { return this.toArray().toString(); }
}

class VHtmlArcView extends VHtmlSvg
{
    protected fArcs  : Array<SVGPathElement> = new Array<SVGPathElement>();
    protected fArc   : SVGPathElement;

    constructor(parent: VHtmlView)
    {
        super(parent);
        this.fArc = document.createElementNS('http://www.w3.org/2000/svg','path');
        this.getHtml().className = "inscore-arc";
        this.fSVG.appendChild(this.fArc)
    }

    updateView( obj: IObject) : void
    {
        let arc = <IArc>obj;
        let scale = arc.fPosition.getScale();
        let w     = this.relative2SceneWidth (arc.fPosition.getWidth ()) * scale;
        let h     = this.relative2SceneHeight(arc.fPosition.getHeight()) * scale;
        this.updateSvgSize(w, h);

        this.fArc.setAttribute( 'width'  , w.toString());
        this.fArc.setAttribute( 'height' , h.toString());
        this.fArc.style.stroke = obj.fColor.getRGBString();
        this.fArc.style.strokeWidth = obj.fPenControl.fPenWidth.toString();

        let r1  = w / 2;
        let r2  = h / 2;

        arc.setRange(this.rangeSetting(arc.getRange() + arc.getDRange()));
        arc.setStart(arc.getStart() + arc.getDStart());
        let startAngle  =  this.angleStandardization(arc.getStart());
        let endAngle    =  this.angleStandardization(startAngle + arc.getRange());
        let startPoint  : Array<number> =  this.PointCalculator(r1, r2, startAngle );
        let endPoint    : Array<number> =  this.PointCalculator(r1, r2, endAngle   );
        let line : Array<number> = [r1, r2];
        let close       : number        =  arc.getClose();
        let path        : string =  this.arcSettings(arc.getRange(), startPoint, line, endPoint, r1, r2, close);
        this.fArc.setAttribute('d', path);
        let penColor = arc.getPenColor();
        if (arc.getPenColor() != []) this.fArc.setAttribute('fill', 'rgb(' + penColor.toString() + ')');
        this.fArc.setAttribute('stroke-width', arc.getPenWidth().toString());
        let penStyle = arc.getPenStyle();
        if (penStyle != "") this.fArc.setAttribute('style', arc.getPenStyle());
        this.fArc.setAttribute('fill-opacity', (arc.getPenAlpha()/255).toString());

        super.updateView (obj);
    }

    //Coordinate setting with width/2, height/2 and angle of the ellipse
PointCalculator(r1 : number, r2 : number, angle : number) : Array<number>
    {
        angle = (angle * Math.PI/180);
        let point : Array<number> = [0, 0];

            point[0] = r1 * (Math.cos(angle)  + 1);
            point[1] = r2 * (-Math.sin(angle) + 1);

        return point;
    }

    //Compute and set the arcs in fArcs
    arcSettings(arcRange : number, start : Array<number>, line : Array<number>,
                end : Array<number>, rx : number, ry : number, close : number)
    {
        //values setting
        arcRange     = Math.max(Math.min(arcRange, 359), -359);
        let flag  : Array<number> = this.direction(arcRange);
        let path  : string;
        let paths : Array<string> = new Array<string>();
        let arc   : ArcParams = new ArcParams();
        arc.getArcs(start, line, rx, ry, flag, end, close);
        path = arc.toString();
        paths.push(path);

        return path;
    }

    //return angle between 180 and - 180°
    angleStandardization(angle : number) : number
    {
        if (angle > 180)
            return this.angleStandardization(angle - 360);
        else if (angle < -180)
            return this.angleStandardization(angle + 360);
        return angle;
    }
    
    rangeSetting(range : number) : number
    {
        if (range >=  360) return  359;
        if (range <= -360) return -359;
        return range;
    }

    //arcFlagSetting use it after angle standardization
    direction (arcRange : number) : Array<number>
    {
        //tests
        let direction : Array<number> = [0,0];
        arcRange >=  180 ? direction[0] = 1 : direction[0] = 0;
        arcRange <= -180 ? direction[0] = 1 : direction[0] = 0;
        arcRange >     0 ? direction[1] = 0 : direction[1] = 1;
        return direction;
    }
}