
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

	updateDimensions(pos: OPosition) : void {
		let elt = this.getSVGTarget();
		let r = elt.getBoundingClientRect();
		this.fSVG.style.width  = (r.right - r.left) + "px";
		this.fSVG.style.height = (r.bottom - r.top) + "px";
		// this.fSVG.style.width  = this.relative2SceneWidth(pos.width) + "px";
		// this.fSVG.style.height = this.relative2SceneHeight(pos.height) + "px";
	}

    updateColor(color: OColor) : void {
		let target = this.getSVGTarget();
		target.style.fill = color.rgb;
		target.style.fillOpacity = color.alpha.toString();
	}

	updatePenControl(brush: OBrush) : void {
		let elt = this.getSVGTarget();
		elt.style.strokeWidth = brush.penWidth.toString();
		elt.style.stroke = brush.penColor;
		elt.style.strokeDasharray = JSSvgView.penStyle2Dash(brush.penStyle);
	}
	
	// getInnerSize (obj: IObject):  {w: number, h: number } {
	// 	let strokeWidth = obj.fPenControl.getPenWidth();
    //     let w   	 = this.fWidth - strokeWidth;
    //     let h 		 = this.fHeight - strokeWidth;
	// 	return { w: (w ? w : 1), h: (h ? h : 1) };
	// }

	// updateView	( obj: IObject) : void {
	// 	super.updateView(obj);
	// 	this.fSVG.style.width = this.fWidth + "px";
    //     this.fSVG.style.height = this.fHeight + "px";
    //     this.fSVG.style.verticalAlign = "top";
	// 	this.fSVG.style.overflow = "visible";
	// }

	// basePenControl(obj:IObject): void {	// provided to bypass the SVG behavior
	// 	super.updatePenControl (obj);
	// }

	// updatePenControl(obj:IObject): void {
	// 	if (obj.fPenControl.modified()) {
	// 		this.fSVG.style.strokeWidth = obj.fPenControl.getPenWidth().toString();
	// 		this.fSVG.style.stroke = obj.fPenControl.getPenColor().getRGBString();
	// 		this.fSVG.style.strokeOpacity = (obj.fPenControl.getPenAlpha()/255).toString();
	// 		this.fSVG.style.strokeDasharray = VHtmlSvg.penStyle2Dash(obj.fPenControl.getPenStyleNum());
	// 	}
	// }

	// getViewScale (obj: IObject): number { return obj.fPosition.getScale(); }

	// updateCommonSVG (obj: IObject, w: number, h: number) : void {
    //    	let target = this.getSVGTarget();
	// 	target.setAttribute('width', w.toString());
	// 	target.setAttribute('height', h.toString());
    //     target.style.transform = this.strokeTranslate(obj);
	// }

	// innerTranslate  (obj: IObject): {x: number, y: number} {
    // 	let w = obj.fPenControl.getPenWidth() / 2;
    // 	return {x: w, y: w}
	// }

    // strokeTranslate(obj:IObject) : string {
    // 	let t = this.innerTranslate(obj);
    //     return (t.x || t.y) ? `translate(${t.x}px,${t.y}px) ` : "none";
    // }

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
