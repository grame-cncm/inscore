
///<reference path="JSSVGBase.ts"/>

class JSLineView extends JSSvgBase {

    protected fLine: SVGLineElement;

	constructor(parent: JSObjectView) {
		super(parent);
        this.fLine = document.createElementNS('http://www.w3.org/2000/svg','line'); 
        this.getElement().className = "inscore-line";
    	this.fSVG.appendChild(this.fLine)
    }    
	clone (parent: JSObjectView) : JSObjectView { return new JSLineView(parent); }

    getSVGTarget() : SVGShape  { return this.fLine; }
	toString() : string		   { return "JSLineView"; }

	updateSVGDimensions(w: number, h: number) : void { }

	getRatio()	: number { 
		let div = this.getElement();
		return Math.max (Math.min(div.clientWidth, div.clientHeight) / Math.min(div.parentElement.clientWidth, div.parentElement.clientHeight), 0.022); 
	}

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
		let line = obj.getLineInfos();
		let x1 = this.relative2SceneWidth (line.x1);
		let y1 = this.relative2SceneHeight (line.y1);
		let x2 = this.relative2SceneWidth (line.x2);
		let y2 = this.relative2SceneHeight (line.y2);

		this.fLine.setAttribute('x1', x1.toString());
		this.fLine.setAttribute('x2', x2.toString());
		this.fLine.setAttribute('y1', y1.toString());
		this.fLine.setAttribute('y2', y2.toString());
		return true;
	}

	updatePenControl(pen: OPen) : void {
		let elt = this.getSVGTarget();
		elt.style.strokeWidth = pen.penWidth.toString();
		elt.style.stroke = pen.penColor;
		elt.style.strokeDasharray = JSSvgBase.penStyle2Dash(pen.penStyle);
		if (pen.brushStyle == TBrushStyle.kNoBrush)
			elt.style.fill = "none";
		else {
	        elt.style.fill = pen.color;
	        elt.style.fillOpacity = pen.alpha.toString();
		}
	}

}
