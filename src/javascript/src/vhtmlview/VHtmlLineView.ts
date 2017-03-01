
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

	getStrokeWidth (obj: IObject): number 	{ return obj.fPenControl.getPenWidth() * obj.fPosition.getHeight();  }
	getStrokeHeight (obj: IObject): number 	{ return obj.fPenControl.getPenWidth() * obj.fPosition.getWidth();  }

	updateView	( obj: IObject) : void {
		let line = <ILine>obj;
		let scale = line.fPosition.getScale();
		let strokeWidth = obj.fPenControl.getPenWidth();
		this.fLine.style.stroke = obj.fColor.getRGBString();
		let p = line.getPoint();
		this.fLine.style.fill = obj.fColor.getRGBString();
		this.fLine.style.strokeWidth = strokeWidth + "px";

		let x = Math.abs(this.relative2SceneWidth (p.getX()) * scale);
		let y = Math.abs(this.relative2SceneHeight(p.getY()) * scale);
		let strokeOffset = strokeWidth / 2;
		let r = x + y;
		let strokeXOffset = 0; // r ? strokeOffset * y / r : strokeOffset;
		let strokeYOffset = 0; // r ? strokeOffset * x / r : strokeOffset;
		x += strokeXOffset;
		y += strokeYOffset;

		this.fLine.setAttribute('x1', strokeXOffset.toString());
		this.fLine.setAttribute('y1', strokeYOffset.toString());
		this.fLine.setAttribute('x2', (x).toString());
		this.fLine.setAttribute('y2', (y).toString());
		this.updateSvgSize (x + strokeWidth, y + strokeWidth);
//		this.fLine.style.transform = "translate(0,0)";

		console.log("VHtmlLineView updateView " + this.relative2SceneWidth(p.getX()) + ", " + this.relative2SceneHeight(p.getY()));
//		super.updateView(obj);
		this.updatePos(obj);
		this.updatePenControl(obj);
	}
/*
	translate (x: number, y: number): string {
		let dx = -(this.fPixWidth)  * (1 + obj.fPosition.getXOrigin());
		let dy = -(this.fPixHeight) * (1 + obj.fPosition.getYOrigin());
       return "translate(" + x +  "," + y + ")";
	}
*/
}