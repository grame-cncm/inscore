
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

    getSVGTarget() : SVGShape  { return this.fLine; }

	updateColor (obj: IObject): void {
		if (obj.fPenControl.fPenColor.modified()) {
			this.fLine.style.stroke = obj.fPenControl.getPenColor().getRGBString();
	        this.fLine.style.strokeOpacity = obj.fPenControl.getPenColor().getSVGA().toString();
	    }
	}

	updateView	( obj: IObject) : void {
		super.updateView(obj);

		let line = <ILine>obj;
		let p = line.getPoint();
		let x = this.relative2SceneWidth (p.getX());
		let y = this.relative2SceneWidth (p.getY());
		let x0 = 0;
		let y0 = 0;

		if ((x < 0) && (y < 0)) {
			x = -x;
			y = -y;
		} else if (x < 0) {
			y0 = y;
			x = -x;
			y = 0;
		}
		else if (y < 0) {
			y0 = -y;
			y = 0;
		}

		this.fLine.setAttribute('x1', x0.toString());
		this.fLine.setAttribute('x2', x.toString());
		this.fLine.setAttribute('y1', y0.toString());
		this.fLine.setAttribute('y2', y.toString());
        this.fLine.style.transform = this.strokeTranslate(obj);
	}
}