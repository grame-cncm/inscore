///<reference path="../model/IPolygon.ts"/>
///<reference path="../lib/TPoint.ts"/>
///<reference path="VHtmlSvg.ts"/>

class VHtmlPolygonView extends VHtmlSvg {

    protected fPolygon: SVGPolygonElement;

    constructor(parent: VHtmlView) {
		super(parent);
        this.fPolygon = document.createElementNS('http://www.w3.org/2000/svg','polygon'); 
    	this.getHtml().className = "inscore-polygon";
    	this.fSVG.appendChild(this.fPolygon)
    }

    getSVGTarget() : SVGShape  { return this.fPolygon; }

	getSize (obj: IObject):  {w: number, h: number } {
        let strokeWidth = obj.fPenControl.getPenWidth();
        let size = this.fPolygon.getBBox();
		return { w: size.width + strokeWidth, h: size.height + strokeWidth};
	}

    updateView	( obj: IObject) : void {
        let polygon = <IPolygon>obj;       
        if (obj.isNewData()) {
		    let points = polygon.getPoints();
            let minx = 0x1fffffff;
            let miny = 0x1fffffff;
            for (let i = 0; i < points.length; i++) {
            	minx = Math.min(minx, points[i].getX());
            	miny = Math.min(miny, points[i].getY());
			}
            let strPoints: string = '';
            for (let i = 0; i < points.length; i++) {
                let x = this.relative2SceneWidth( points[i].getX() - minx);
                let y = this.relative2SceneWidth( points[i].getY() - miny);
                strPoints += x + ',' + y + ' ';
            }          
            this.fPolygon.setAttribute('points', strPoints);
        }
        this.fPolygon.setAttribute('fill', obj.fColor.getRGBString());
        super.updateView(obj);
        let size = this.getInnerSize(obj);
        this.updateCommonSVG (obj, size.w, size.h); 
    }        

	updateObjectSize ( obj: IObject) : void {
        let elt = this.getHtml();
        let w = this.scene2RelativeWidth(elt.clientWidth);
        let h = this.scene2RelativeHeight(elt.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
    }	
}