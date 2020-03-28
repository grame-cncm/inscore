
///<reference path="JSObjectView.ts"/>

interface SVGStyle {
    color: string;
    fill: string;
    fillOpacity: string;
    transform: string;
    stroke: string;
    strokeWidth: string;
	strokeDasharray: string;
	width: string;
	height: string;
}

interface SVGShape {
	setAttribute (a: string, v: string) : void;
	getBoundingClientRect() : DOMRect;
    style: SVGStyle;
}

abstract class JSSvgView extends JSObjectView {
	protected fSVG:SVGSVGElement;

    constructor(parent: JSObjectView) {
    	super (document.createElement('div'), parent);
		this.fSVG = document.createElementNS('http://www.w3.org/2000/svg','svg');
		this.fSVG.setAttribute('xmlns', "http://www.w3.org/2000/svg");
		this.fSVG.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
		this.fSVG.setAttribute('version', "1.1");
		// this.fSVG.style.paintOrder = "stroke";
		this.getElement().appendChild(this.fSVG);
	}
    abstract getSVGTarget() : SVGShape;
	abstract updateSVGDimensions(w: number, h: number) : void;

	updateDimensions(pos: OPosition) : void {
    	let w = this.relative2SceneWidth(pos.width);
		let h = this.relative2SceneHeight(pos.height);
		this.updateSVGDimensions (w, h);
		let strokewidth = pos.pen.penWidth * 2;
		this.fSVG.style.width  = (w + strokewidth) + "px";
		this.fSVG.style.height = (h + strokewidth) + "px";
	  }

    updateColor(color: OColor) : void {
		let target = this.getSVGTarget();
		target.style.fill = color.rgb;
		target.style.fillOpacity = color.alpha.toString();
	}

	updatePenControl(pen: OPen) : void {
		let elt = this.getSVGTarget();
		elt.style.strokeWidth = pen.penWidth.toString();
		elt.style.stroke = pen.penColor;
		elt.style.strokeDasharray = JSSvgView.penStyle2Dash(pen.penStyle);
		if (pen.brushStyle == TBrushStyle.kNoBrush)
			elt.style.fill = "none";
		else {
	        elt.style.fill = pen.color;
	        elt.style.fillOpacity = pen.alpha.toString();
		}
	}

	getTranslate(pos: OPosition) : number { return pos.pen.penWidth; }

	getPos(pos: OPosition) : Point {
		let strokewidth = this.getTranslate(pos);
		this.getSVGTarget().style.transform = strokewidth ? `translate(${strokewidth}px,${strokewidth}px)` : "";
		return super.getPos(pos);
	}

	// setNone () : void 				{ this.fSVG.setAttribute("filter", "blur(0px)");  }
	// setBlur (val: number) : void 	{ this.fSVG.setAttribute("filter", "blur(" + val + "px)"); }
	// setShadow (params: Array<number>) : void {
	// 	let color = new IColor( params.slice(2,6) );
	// 	this.fSVG.setAttribute("filter", "drop-shadow(" + color.getCSSRGBAString() + params[0] +"px " + params[1] +"px " + params[6] +"px)");
	// }

	static penStyle2Dash(style : number) : string
	{
		switch(style) {
			case INScoreModule.kDashStyle:	 	return "4, 4";
			case INScoreModule.kDotStyle:		return "2 2";
			case INScoreModule.kDashDotStyle: 	return "4 2";
			case INScoreModule.kDashDotDotStyle:	return "4 4 2";
			default : 	return "";
		}
	}
}
