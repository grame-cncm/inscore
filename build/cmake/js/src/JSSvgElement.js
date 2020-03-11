
interface SVGStyle {
    color: string;
    fill: string;
    fillOpacity: string;
    transform: string;
}

interface SVGShape {
	setAttribute (a: string, v: string) : void;
    style: SVGStyle;
}

class JSSvgElement extends JSOjectView {
    constructor(parent) {
    	super (document.createElement('div'), parent);
		this.fSVG = document.createElementNS('http://www.w3.org/2000/svg','svg');
		this.fSVG.setAttribute('xmlns', "http://www.w3.org/2000/svg");
		this.fSVG.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
		this.fSVG.setAttribute('version', "1.1");
		this.getElement().appendChild(this.fSVG);
        this.fSVG.style.verticalAlign = "top";
		this.fSVG.style.overflow = "visible";
	}

	getSVGTarget()		{ return this.fSVG; }
	colorTarget() 		{ return this.fSVG; }

	updateColor (obj, elt) {
		super(obj, elt);
		// let modified = (obj.fColor.modified() || obj.fBrushStyle.brushModified()) && (obj.fBrushStyle.getBrushStyle() != eBrushStyle.kNone);
		let modified = (obj.colorChanged());
		if (obj.brushChanged() && (obj.getBrushStyle() == kNoBrushStyle)) {
			elt.style.fill = "none";
		}
		else if (modified) {
	        elt.style.fill = obj.fColor.getRGBAString();
	        elt.style.fillOpacity = obj.fColor.getSVGA().toString();
		}
	}
		
	getInnerSize (obj) {
		let strokeWidth = obj.getPenWidth();
        let w   	 = this.fWidth - strokeWidth;
        let h 		 = this.fHeight - strokeWidth;
		return { w: (w ? w : 1), h: (h ? h : 1) };
	}

	updateView	( obj ) {
		super.updateView(obj);
		this.fSVG.style.width = this.fWidth + "px";
        this.fSVG.style.height = this.fHeight + "px";
	}

	basePenControl(obj) {	// provided to bypass the SVG behavior
		super.updatePenControl (obj);
	}

	updatePenControl(obj) {
		if (obj.brushChanged()) {
			this.fSVG.style.strokeWidth = obj.getPenWidth().toString();
			this.fSVG.style.stroke = obj.getPenColor();
			this.fSVG.style.strokeOpacity = obj.getPenAlpha().toString();
			this.fSVG.style.strokeDasharray = JSSvgElement.penStyle2Dash(obj.getPenStyle());
		}
	}

	getViewScale (obj) { return obj.getScale(); }

	updateCommonSVG (obj: IObject, w: number, h: number) : void {
       	let target = this.getSVGTarget();
		target.setAttribute('width', w.toString());
		target.setAttribute('height', h.toString());
        target.style.transform = this.strokeTranslate(obj);
	}

	innerTranslate  (obj) {
    	let w = obj.getPenWidth() / 2;
    	return {x: w, y: w}
	}

    strokeTranslate(obj) {
    	let t = this.innerTranslate(obj);
        return (t.x || t.y) ? `translate(${t.x}px,${t.y}px) ` : "none";
    }

	setNone () 				{ this.fSVG.setAttribute("filter", "blur(0px)");  }
	setBlur (va) 		 	{ this.fSVG.setAttribute("filter", "blur(" + val + "px)"); }
	setShadow (color, params){
		this.fSVG.setAttribute("filter", "drop-shadow(" + color + params[0] +"px " + params[1] +"px " + params[6] +"px)");
	}

	static penStyle2Dash(style)
	{
		switch(style) {
			case kDashStyle :		return "4, 4";
			case kDotStyle :		return "1, 5";
			case kDashDotStyle :	return "4, 4, 1, 5";
			case kDashDotDotStyle :	return "4, 4, 1, 5, 1, 5";
			default : 				return "";
		}
	}
}