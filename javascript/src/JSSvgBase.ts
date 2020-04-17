
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
	clientWidth: number;
	clientHeight: number;
}

abstract class JSSvgBase extends JSObjectView {
	protected fSVG:SVGSVGElement;

    constructor(parent: JSObjectView) {
    	super (document.createElement('div'), parent);
		this.fSVG = document.createElementNS('http://www.w3.org/2000/svg','svg');
		this.fSVG.setAttribute('xmlns', "http://www.w3.org/2000/svg");
		this.fSVG.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
		this.fSVG.setAttribute('version', "1.1");
		this.getElement().appendChild(this.fSVG);
	}

	abstract getSVGTarget() : SVGShape;
	abstract updateSVGDimensions(w: number, h: number) : void;

	updateDimensions(pos: OPosition) : void {
		let w = Math.max(1, this.relative2SceneWidth(pos.width));
		let h = Math.max(1, this.relative2SceneHeight(pos.height));
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

	getTranslate(pos: OPosition) : Point { 
		let bb = this.fSVG.getBBox();
		return { x: pos.pen.penWidth, y: pos.pen.penWidth }; 
	}

	getPos(pos: OPosition) : Point {
		let tr = this.getTranslate(pos);
		this.getSVGTarget().style.transform = (tr.x || tr.y) ? `translate(${tr.x}px,${tr.y}px)` : "";
		return super.getPos(pos);
	}

	removeEffect(elt: HTMLElement): void 			{ this.fSVG.setAttribute("filter", "blur(0px)"); }
	setBlur(elt: HTMLElement, val: number): void 	{ this.fSVG.setAttribute("filter", `blur(${val}px)`); }
	setShadow(elt: HTMLElement, val: OShadow): void {
		this.fSVG.setAttribute("filter", `drop-shadow(${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px)`);
	}

	static penStyle2Dash(style : number) : string
	{
		switch(style) { 
			case TPenStyle.kDash:	 	return "5,5";
			case TPenStyle.kDot:		return "2,2";
			case TPenStyle.kDashDot: 	return "5,2,2,2";
			case TPenStyle.kDashDotDot:	return "5,2,2,2,2,2";
			default : 	return "";
		}
	}
}
