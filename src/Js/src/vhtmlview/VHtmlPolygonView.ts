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
            obj.newData(false);
		    let points = polygon.getPoints();
            let strPoints: string = '';
            for (let i = 0; i < points.length; i++) {
                let x = this.relative2SceneX( points[i].getX() );
                let y = this.relative2SceneY( points[i].getY() );
                if (!x) x = 1;
                if (!y) y = 1;    
                strPoints += x + ',' + y + ' ';
            }          
            this.fPolygon.setAttribute('points', strPoints);
            
            let polygonSize = this.fPolygon.getBBox();        
            this.updateSvgSize (polygonSize.width, polygonSize.height);            
            this.updateSvgPos(polygonSize.x, polygonSize.y);                          

            if ( !this.getOrigin(polygonSize) ) {
                let x = this.scene2RelativeWidth(polygonSize.width)
                x = Math.floor(this.relative2SceneY(- x/2)*1000)/1000;
                let y = this.scene2RelativeHeight(polygonSize.height)
                y = Math.floor(this.relative2SceneX(- y/2)*1000/1000); 

                let strPoints2: string = '';
                for (let i = 0; i < points.length; i++) {
                    let x = this.relative2SceneX( points[i].getX()) - polygonSize.x;
                    let y = this.relative2SceneY( points[i].getY()) - polygonSize.y;
                    if (!x) x = 1;
                    if (!y) y = 1;    
                    strPoints2 += x + ',' + y + ' ';
                }
                this.fPolygon.setAttribute('points', strPoints2);
                
                let elt = this.getHtml();
                elt.setAttribute('position', 'absolute');
                elt.style.top = y + 'px';
                elt.style.left = x + 'px';
                elt.style.width = polygonSize.width + 'px';
                elt.style.height = polygonSize.height + 'px';
            }  
            this.updateObjectSize (obj);      
	    } 

        this.fPolygon.style.fill = obj.fColor.getRGBString();  
        this.updatePos(polygon); 
    }        

    // cette fonction permet de déterminer si le polygon est centré au milieu de la scene
    // si ce n'est pas le cas, on détermine son cadran pour le translater correctement  
    getOrigin (polygon: SVGRect): boolean {
        let xOrigin = Math.floor(this.scene2RelativeX(polygon.x + polygon.width/2)*100) /100;
        let yOrigin = Math.floor(this.scene2RelativeY(polygon.y + polygon.height/2)*100) /100;
        
        if (xOrigin == 0 && yOrigin == 0) { return true; } // l'objet est centré        
        else { return false; }
    }
     

	updateObjectSize ( obj: IObject) : void {
        let elt = this.getHtml();
        let w = this.scene2RelativeWidth(elt.clientWidth);
        let h = this.scene2RelativeHeight(elt.clientHeight);
        let x = this.scene2RelativeX(elt.clientLeft) + w/2;
        let y = this.scene2RelativeY(elt.clientTop) + h/2;
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		obj.fPosition.setXPos (x);
		obj.fPosition.setYPos (y);
        console.log('w ' + elt.clientWidth + ' h ' + elt.clientHeight + ' x ' + elt.clientLeft + ' y ' + elt.clientTop)
        console.log(x + ' ' + y)
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

/*
    updatePos (obj: IObject): void {
		let pos 	= obj.getPosition();
		let size 	= obj.getSize();
		let scale 	= this.getScale(obj);
		let z		= obj.fPosition.getZOrder();
        let w  		= this.relative2SceneWidth (size.w) * scale;
        let h 		= this.relative2SceneHeight (size.h) * scale;
        let left  	= this.relative2SceneX (pos.x) - w/2.0;
        let top 	= this.relative2SceneY (pos.y) - h/2.0;

    	let elt = this.getHtml();
        elt.style.width  = w +"px";
        elt.style.height = h +"px";
        elt.style.left 	=  left + "px";
        elt.style.top 	=  top + "px";
        elt.style.zIndex = z.toString();
		elt.style.transform  = this.getTransform(obj);
        elt.style.visibility  = obj.fPosition.getVisible() ? "inherit" : "hidden";
        this.setPos( top, left, w, h);
	}
*/    
}








/*
                switch (origin.cadran) {
                    case 0: case 1: case 2: case 3:
                        this.fSVG.setAttribute('style', 'position: absolute; ' + 
                                                        'top:' + x + 'px; ' + 'left:' + y + 'px; ' + 
                                                        'width: ' + polygonSize.width + 'px; ' + 'height: ' + polygonSize.height + 'px;');                        
                        break;*/
/*
                    case 1:
                        this.fSVG.setAttribute('style', 'position: absolute; ' + 
                                                        'top:' + polygonSize.height/2 + 'px; ' + 'left:' + polygonSize.width/2 + 'px; ' + 
                                                        'width: ' + polygonSize.width + 'px; ' + 'height: ' + polygonSize.height + 'px;');                        
                        break;

                    case 2:
                        this.fSVG.setAttribute('style', 'position: absolute; ' + 
                                                        'top:' + polygonSize.height/2 + 'px; ' + 'left:' + polygonSize.width/2 + 'px; ' + 
                                                        'width: ' + polygonSize.width + 'px; ' + 'height: ' + polygonSize.height + 'px;');                        
                        break;

                    case 3:
                        this.fSVG.setAttribute('style', 'position: absolute; ' + 
                                                        'top:' + polygonSize.height/2 + 'px; ' + 'left:' + polygonSize.width/2 + 'px; ' + 
                                                        'width: ' + polygonSize.width + 'px; ' + 'height: ' + polygonSize.height + 'px;');                        
                        break;

                    default:
                        break;
                }
            }

*/

/*            
            strPoints = '';
            for (let i = 0; i < points.length; i++) {
                let x = this.relative2SceneX( points[i].getX()) +  (polygonSize.width/2);
                let y = this.relative2SceneY( points[i].getY())+  (polygonSize.height/2);
                if (!x) x = 1;
                if (!y) y = 1;    
                strPoints += x + ',' + y + ' ';
            }       

            this.fPolygon.setAttribute('points', strPoints);
            polygonSize = this.fPolygon.getBBox();
*/           
            //this.updateSvgPos (polygonSize.x, polygonSize.y);  
            //this.updateSvgSize (polygonSize.width, polygonSize.height);

            /*
            //this.updateSvgPos (polygonSize.x, polygonSize.y);  
            //this.updateSvgSize (polygonSize.width, polygonSize.height);
            
            for (let i = 0; i < points.length; i++) {
                let x = this.relative2SceneX( points[i].getX()) - polygonSize.x;
                let y = this.relative2SceneY( points[i].getY()) - polygonSize.y;
                if (!x) x = 1;
                if (!y) y = 1;    
                strPoints += x + ',' + y + ' ';
            }
     */       
            //this.fPolygon.setAttribute('points', strPoints);
            //this.updateObjectSize (obj);
            //this.fPolygon.style.fill = obj.fColor.getRGBString()