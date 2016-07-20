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
    
    updateView	( obj: IObject) : void {        
        let polygon = <IPolygon>obj;
        
        if (obj.isNewData()) {
		    let points = polygon.getPoints();
            let strPoints: string = '';
            for (let i = 0; i < points.length; i++) {
                let x = this.relative2SceneX( points[i].getX() );
                let y = this.relative2SceneY( points[i].getY() );
                if (!x) x = 1;
                if (!y) y = 1;    
                strPoints += x + ',' + y + ' ';
            }
             
            console.log(strPoints)
            this.fPolygon.setAttribute('points', strPoints);

            let polygonSize = this.fPolygon.getBBox();
            this.updateSvgPos (polygonSize.x, polygonSize.y);  
            this.updateSvgSize (polygonSize.width, polygonSize.height);
            
            for (let i = 0; i < points.length; i++) {
                let x = this.relative2SceneX( points[i].getX()) - polygonSize.x;
                let y = this.relative2SceneY( points[i].getY()) - polygonSize.y;
                if (!x) x = 1;
                if (!y) y = 1;    
                strPoints += x + ',' + y + ' ';
            }
            
            this.fPolygon.setAttribute('points', strPoints);
            this.updateObjectSize (obj);
            this.fPolygon.style.fill = obj.fColor.getRGBString();   
        }
	}         
       
	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        let h = this.scene2RelativeHeight(this.fSVG.clientHeight);
        let x = this.scene2RelativeHeight(this.fSVG.clientLeft);
        let y = this.scene2RelativeHeight(this.fSVG.clientTop);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		obj.fPosition.setXPos (x);
		obj.fPosition.setYPos (y);
    }	
    	
	getTransform (obj: IObject): string {
		let hw = this.fPixWidth/2;
		let hh = this.fPixHeight/2;
		let dx = -(this.fPixWidth/2)  * (1 + obj.fPosition.getXOrigin());
		let dy = -(this.fPixHeight/2) * (1 + obj.fPosition.getYOrigin());	
        return super.getTransform(obj) + ` translate(${dx}px, ${dy}px)`;
	}
    
	updateSvgPos (x: number, y: number): void { 
    	let elt = this.getHtml();		
		elt.style.left = x +"px";
        elt.style.top  = y +"px";
		this.fSVG.style.left = x +"px";
        this.fSVG.style.top  = y +"px";
	}    
}