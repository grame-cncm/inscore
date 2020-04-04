
///<reference path="JSSVGBase.ts"/>

class JSPolygonView extends JSSvgBase {

    protected fPolygon: SVGPolygonElement;

    constructor(parent: JSObjectView) {
		super(parent);
        this.fPolygon = document.createElementNS('http://www.w3.org/2000/svg','polygon'); 
    	this.getElement().className = "inscore-polygon";
    	this.fSVG.appendChild(this.fPolygon)
    }

    toString() : string			{ return "JSPolygonView"; }
    getSVGTarget() : SVGShape   { return this.fPolygon; }

    updateSVGDimensions(w: number, h: number) : void {}

    updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
        let points = obj.getPolygonInfos();
        let minx = 0x1fffffff;
        let miny = 0x1fffffff;
        let n = points.size();
        for (let i = 0; i < n; i++) {
            minx = Math.min(minx, points.get(i++));
            miny = Math.min(miny, points.get(i));
        }
        let strPoints: string = '';
        for (let i = 0; i < n; i++) {
            let x = this.relative2SceneWidth( points.get(i++) - minx);
            let y = this.relative2SceneWidth( points.get(i) - miny);
            strPoints += x + ',' + y + ' ';
        }          
        this.fPolygon.setAttribute('points', strPoints);        
        return true;
    }        
}