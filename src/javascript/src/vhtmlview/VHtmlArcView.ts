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
    fArcFlags  : Array<number> = [0,0];

    getArcs(start : Array<number>, rX : number, rY : number, arcFlags : Array<number>, end : Array<number>)
    {
        this.fStart     = start;
        this.fEnd       = end;
        this.fRX        = rX;
        this.fRY        = rY;
        this.fArcFlags  = arcFlags;
    }

    toArray (): Array<any> 	{ return ["M ",this.fStart, "A ", this.fRX, this.fRY, "0", this.fArcFlags , this.fEnd]; }
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
        // let arcs = getArcs (arc) => array {x1, y1, x2, y2, rx, ry, direction}
        // getArcs fait le découpage et utilise angleToXY (angle, w h) => x, y
        // pour chaque element du tableau
        // setArc (arcs[i]);
        // verifier: s'il le nbre d'arcs diminue, supprimer les derniers

        let arc = <IArc>obj;

        let scale = arc.fPosition.getScale();
        let w     = this.relative2SceneWidth (arc.fPosition.getWidth ()) * scale;
        let h     = this.relative2SceneHeight(arc.fPosition.getHeight()) * scale;
        this.updateSvgSize(w, h);

        this.fArc.setAttribute( 'width'  , w.toString());
        this.fArc.setAttribute( 'height' , h.toString());
        this.fArc.style.fill = obj.fColor.getRGBString();

        let r1  = arc.fPosition.getWidth () / 2;
        let r2  = arc.fPosition.getHeight() / 2;
        let startAngle  =  this.angleStandardization(arc.getStart());
        let endAngle    =  this.angleStandardization((arc.getStart() + arc.getRange()));
        let startPoint : Array<number> =  this.PointCalculator(r1, r2, startAngle );
        let endPoint   : Array<number> =  this.PointCalculator(r1, r2, endAngle   );
        let path = this.arcNumberCalculatorAndSetting(arc.getRange(), startAngle, startPoint, endPoint, r1, r2);
        this.fArc.setAttribute('b', path);
        // this.updatePos(obj);      vérifier son utilisation avec arcs multiples
    }

    //Coordinate setting with width, height and angle of the ellipse
    PointCalculator(r1 : number, r2 : number, angle : number)
    {
        let point : Array<number> = [0, 0];

        if(r1 > r2)
        {
            point[0] = (r1 * Math.cos(angle) + r1) / (r1 * 2);
            point[1] = (r2 * Math.cos(angle) + r2) / (r2 * 2);
        }else
        {
            point[0] = (r2 * Math.cos(angle) + r2) / (r2 * 2);
            point[1] = (r1 * Math.cos(angle) + r1) / (r1 * 2);
        }
        return point;
    }

    //Compute and set the arcs in fArcs
    arcNumberCalculatorAndSetting(arcRange : number, startAngle : number, start : Array<number>,
                                  end : Array<number>, rx : number, ry : number)
    {
        //values setting
        arcRange   = this.angleStandardization(arcRange);
        startAngle = this.angleStandardization(startAngle);
        arcRange   = Math.max(Math.min(arcRange, 360), -360);
        let endAngle = startAngle + arcRange;
        let flag : Array<number> = this.arcFlag(startAngle);
        let paths : Array<string>;

        if (((startAngle >  0 ) && (endAngle <   0)) || ((startAngle <   0 ) && (endAngle >   0 )) ||
            ((startAngle < 180) && (endAngle > 180)) || ((startAngle > -180) && (endAngle < -180)))
        {
            let arc2 : ArcParams;
            //arc2.getArcs();
            let path2 = arc2.toString();


            if (((startAngle <  0 ) && (endAngle > 180)) || ((startAngle >   0 ) && (endAngle < -180)) ||
                ((startAngle > 180) && (endAngle <  0 )) || ((startAngle < -180) && (endAngle >  0 )))
            {
                let arc3 : ArcParams;
                //arc3.getArcs();
                let path3 = arc3.toString();
            }
        }
        let arc : ArcParams;
        arc.getArcs(start,rx, ry, flag,end);
        let path = arc.toString();
        paths.push(path);


        //return paths;
        //path en return juste pour un test simple fragment
        return path;
    }

    //Check if angle value is between -360 and 360°
    angleStandardization(angle : number)
    {
        if(angle > 0)
        {
            while (angle >  180)
            {
               angle -= 360;
            }
        }else
            while (angle < -180)
            {
                angle += 360;
            }
        return angle;
    }

    //arcFlagSetting use it after angle standardization
    arcFlag(startAngle : number)
    {
        let flags : Array<number> = [0,0];

        if (startAngle > 0 )
        {
             flags = [0,1];
        }
        else flags = [0,0];

        return flags;
    }
}