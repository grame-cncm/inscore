
///<reference path="../model/IObject.ts"/>
///<reference path="VHtmlView.ts"/>

class VHtmlSvg extends VHtmlView {
    protected fSVG:SVGSVGElement;
   
    constructor(parent: VHtmlView) {
    	super (document.createElement('div'), parent);
        this.fSVG = document.createElementNS('http://www.w3.org/2000/svg','svg');
        this.fSVG.setAttribute('xmlns', "http://www.w3.org/2000/svg");
        this.fSVG.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
        this.fSVG.setAttribute('version', "1.1");
    	this.getHtml().appendChild(this.fSVG);
	}

	updateColor (obj: IObject): void {
        if (obj.fColor.modified()) {
	        this.fSVG.style.color = obj.fColor.getRGBString();
	        let alpha =  obj.fColor.getA() / 255;
	        this.fSVG.style.fillOpacity = alpha.toString();
		}
	}
		
	getInnerSize (obj: IObject):  {w: number, h: number } {
		let strokeWidth = obj.fPenControl.getPenWidth();
        let w   	 = this.fWidth - strokeWidth;
        let h 		 = this.fHeight - strokeWidth;
		return { w: (w ? w : 1), h: (h ? h : 1) };
	}

	updateView	( obj: IObject) : void {
		super.updateView(obj);
		this.fSVG.style.width = this.fWidth + "px";
        this.fSVG.style.height  = this.fHeight  + "px";
        this.fSVG.style.verticalAlign = "top";
	}

	basePenControl(obj:IObject): void {		// provided to bypass the SVG behavior
		super.updatePenControl (obj);
	}

	updatePenControl(obj:IObject): void {
		if (obj.fPenControl.modified()) {
			this.fSVG.style.strokeWidth = obj.fPenControl.getPenWidth().toString();
			this.fSVG.style.stroke = obj.fPenControl.getPenColor().getRGBString();
			this.fSVG.style.strokeOpacity = (obj.fPenControl.getPenAlpha()/255).toString();
			this.fSVG.style.strokeDasharray = this.penStyle2Dash(obj.fPenControl.getPenStyleNum());
		}
	}

	innerTranslate  (obj: IObject): {x: number, y: number} {
    	let w = obj.fPenControl.getPenWidth() / 2;
    	return {x: w, y: w}
	}

    strokeTranslate(obj:IObject) : string {
    	let t = this.innerTranslate(obj);
        return (t.x || t.y) ? `translate(${t.x}px,${t.y}px) ` : "none";
    }

	penStyle2Dash(style : number) : string
	{
		switch(style) {
			case 1 :	return "4, 4";
			case 2 :	return "1, 5";
			case 3 :	return "4, 4, 1, 5";
			case 4 :	return "4, 4, 1, 5, 1, 5";
			default : 	return "";
		}
	}
}