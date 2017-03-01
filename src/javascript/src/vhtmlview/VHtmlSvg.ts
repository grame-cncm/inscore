
///<reference path="../model/IObject.ts"/>
///<reference path="VHtmlView.ts"/>

class VHtmlSvg extends VHtmlView {
    protected fSVG:SVGSVGElement;
//	protected fPixWidth : number;		// the element width in pixels
//    protected fPixHeight: number;		// the element height in pixels
	protected fStrokeWidth : number;
   
    constructor(parent: VHtmlView) {
    	super (document.createElement('div'), parent);
        this.fSVG = document.createElementNS('http://www.w3.org/2000/svg','svg');
        this.fSVG.setAttribute('xmlns', "http://www.w3.org/2000/svg");
        this.fSVG.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
        this.fSVG.setAttribute('version', "1.1");
    	this.getHtml().appendChild(this.fSVG);
    	this.fStrokeWidth = 0;
	}

	updateColor (obj: IObject): void {
        if (obj.fColor.modified()) {
	        this.fSVG.style.color = obj.fColor.getRGBString();
	        let alpha =  obj.fColor.getA() / 255;
	        this.fSVG.style.fillOpacity = alpha.toString();
		}
	}
	
	updateSvgSize (w: number, h: number): void {
		this.fSVG.style.width = (w ? w : 1) + "px";
        this.fSVG.style.height  = (h ? h : 1)  + "px";
        this.fSVG.style.verticalAlign = "top";
    }

	updatePenControl(obj:IObject): void
	{
		if (obj.fPenControl.modified())
		{
			this.fSVG.style.strokeWidth = obj.fPenControl.getPenWidth().toString();
			this.fSVG.style.stroke = obj.fPenControl.getPenColor().getRGBString();
			this.fSVG.style.strokeOpacity = (obj.fPenControl.getPenAlpha()/255).toString();
			this.fSVG.style.strokeDasharray = this.penStyleDashArrayConstrucor(obj.fPenControl.getPenStyleNum());

			if(obj.fPenControl.getPenWidth() > 0)
			{
				this.fStrokeWidth = obj.fPenControl.getPenWidth();
				this.updateSvgSize(this.fWidth, this.fHeight);
            }
		}
	}

    getTranslate() : string
    {
        return ('translate(' + this.fStrokeWidth/2 + ',' + this.fStrokeWidth/2 + ')');
    }

	penStyleDashArrayConstrucor(style : number) : string
	{
		let dashArray : string;
		switch(style)
		{
			case 0 :
				dashArray = "";
				break;
			case 1 :
				dashArray = "3, 4";
				break;
			case 2 :
				dashArray = "1, 5";
				break;
			case 3 :
				dashArray = "3, 4, 1, 5";
				break;
			case 4 :
				dashArray = "3, 4, 1, 5, 1, 5";
				break;
			default : dashArray = "";
		}
	return dashArray;
	}
}