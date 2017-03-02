
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
		super.updateView(obj);

		let line = <ILine>obj;
		let p = line.getPoint();
		let strokeWidth = obj.fPenControl.getPenWidth();
		this.fLine.style.fill = obj.fColor.getRGBString();
		this.fLine.style.strokeWidth = obj.fPenControl.getPenWidth() + "px";

		let x = Math.abs(this.relative2SceneWidth (p.getX()));
		let y = Math.abs(this.relative2SceneHeight(p.getY()));

		this.fLine.setAttribute('x1', '0');
		this.fLine.setAttribute('y1', '0');
		this.fLine.setAttribute('x2', (x).toString());
		this.fLine.setAttribute('y2', (y).toString());
        this.fLine.style.transform = this.strokeTranslate(obj);
	}
}