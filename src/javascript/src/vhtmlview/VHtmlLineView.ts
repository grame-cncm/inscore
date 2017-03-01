
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
		let scale = line.fPosition.getScale();
		let strokeWidth = obj.fPenControl.getPenWidth();
		this.fLine.style.stroke = obj.fColor.getRGBString();
		let p = line.getPoint();
		let x = (this.relative2SceneWidth (p.getX()) * scale) + strokeWidth/2;
		let y = (this.relative2SceneHeight(p.getY()) * scale) + strokeWidth/2;
		this.fLine.style.fill = obj.fColor.getRGBString();
		this.fLine.style.strokeWidth = strokeWidth + "px";

		if ( x < 0)
		{
			this.fLine.setAttribute('x1', (x).toString());
			this.fLine.setAttribute('y1', (y).toString());
			this.fLine.setAttribute('x2', (strokeWidth/2).toString());
            this.fLine.setAttribute('y2', (strokeWidth/2).toString());
			// this.fLine.setAttribute('x1', (strokeWidth/2).toString());
			// this.fLine.setAttribute('y1', (strokeWidth/2).toString());
			// this.fLine.setAttribute('x2', (x).toString());
			// this.fLine.setAttribute('y2', (y).toString());
        	//trouver une solution pour repartir sur un affichage comme lors du 1e 1/4 de cerlce
			this.fLine.style.transform = this.translate(line);
			this.updateSvgSize(Math.abs(x) + strokeWidth/2, Math.abs(y) + strokeWidth/2);
			console.log("VHtmlLine updateView x < 0 ??? : " + x )
		}
		else
		{
			this.fLine.setAttribute('x1', (strokeWidth/2).toString());
			this.fLine.setAttribute('y1', (strokeWidth/2).toString());
			this.fLine.setAttribute('x2', (x).toString());
			this.fLine.setAttribute('y2', (y).toString());
			this.updateSvgSize (x + strokeWidth/2 ,y + strokeWidth/2);
			this.fLine.style.transform = "translate(0,0)";
		}
		console.log("VHtmlLineView updateView " + this.relative2SceneWidth(p.getX()) + ", " + this.relative2SceneHeight(p.getY()))
		this.updatePos(obj);
	}

	translate (obj: IObject): string {
		let dx = -(this.fPixWidth)  * (1 + obj.fPosition.getXOrigin());
		let dy = -(this.fPixHeight) * (1 + obj.fPosition.getYOrigin());
       return "translate(" + dx +  "," + dy + ")";
	}
/*
	updateSvgSize (w: number, h: number): void {
    	w = Math.abs(w);
		h = Math.abs(h);
		let elt = this.getHtml();
		this.fPixWidth = w ? w : 1;
		this.fPixHeight = h ? h : 1; 		
		elt.style.height = this.fPixHeight + "px";
        elt.style.width  = this.fPixWidth  + "px";
		this.fSVG.style.height = this.fPixHeight + "px";
        this.fSVG.style.width  = this.fPixWidth  + "px";
	}*/
}