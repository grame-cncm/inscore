
///<reference path="../model/ILine.ts"/>
///<reference path="../lib/TPoint.ts"/>
///<reference path="VHtmlSvg.ts"/>

class VHtmlLineView extends VHtmlSvg {

    protected fLine: SVGLineElement;
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fLine = document.createElementNS('http://www.w3.org/2000/svg','line'); 
    	this.getHtml().className = "inscore-line";
    	this.fSVG.appendChild(this.fLine)
    }    

	updateView	( obj: IObject) : void {
		let line = <ILine>obj;
		let p = line.getPoint();
		let x = this.relative2SceneWidth( p.getX() );
		let y = this.relative2SceneHeight( p.getY() );
		if (!x) x = 1;
		if (!y) y = 1;
		
    	this.updateSvgSize (x, y);
        this.fLine.setAttribute('width', Math.abs(x).toString());
        this.fLine.setAttribute('height', Math.abs(y).toString());
				
		if ( x < 0 || y < 0 ) {
			this.fLine.setAttribute('x1', this.fSVG.style.width);
			this.fLine.setAttribute('y1', '0');	
			this.fLine.setAttribute('x2', '0');
        	this.fLine.setAttribute('y2', this.fSVG.style.height);
		}
		
		else {
			this.fLine.setAttribute('x1', '0');
			this.fLine.setAttribute('y1', '0');
			this.fLine.setAttribute('x2', x.toString());
			this.fLine.setAttribute('y2', y.toString());
		}
		
        this.fLine.style.stroke = obj.fColor.getRGBString();
		this.updatePos(obj);
	}
	
	getTransform (obj: IObject): string {
		let hw = this.fPixWidth/2;
		let hh = this.fPixHeight/2;
		let dx = -(this.fPixWidth/2)  * (1 + obj.fPosition.getXOrigin());
		let dy = -(this.fPixHeight/2) * (1 + obj.fPosition.getYOrigin());	
        return super.getTransform(obj) + ` translate(${dx}px, ${dy}px)`;
	}
	
	updateSvgSize (w: number, h: number): void { 
    	w = Math.abs(w);
		h = Math.abs(h);
		let elt = this.getHtml();
		this.fPixWidth = w ? w : 1; 
		this.fPixHeight = h ? h : 1; 		
		elt.style.height = this.fPixHeight +"px";
        elt.style.width  = this.fPixWidth +"px";
		this.fSVG.style.height = this.fPixHeight +"px";
        this.fSVG.style.width  = this.fPixWidth +"px";
	}		
}