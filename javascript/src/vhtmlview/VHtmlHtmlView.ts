
///<reference path="VHtmlAutoSize.ts"/>
///<reference path="../model/IHtml.ts"/>
///<reference path="../model/IText.ts"/>

class VHtmlHtmlView extends VHtmlAutoSize {

    constructor(parent: VHtmlView) {
		super( document.createElement('div'), parent); 
        this.getHtml().className = "inscore-html";
    }    

	getText	( obj: IText) : string { return obj.getText(); }

	// CSS weight are used as numbers
	static fontWeight2Num	( weight: string) : string {
		switch (weight) {
			case IText.kWeightNormal: 		return "400";
			case IText.kWeightLight:		return "200";
			case IText.kWeightDemiBold:		return "550";
			case IText.kWeightBold:			return "700";
			case IText.kWeightBlack:		return "900";
			default: return "400";
		}
	}

	setFont	( t: IText) : void {
    	let elt = this.getHtml();
        elt.style.fontSize 		= t.getFontSize()+"px";
        elt.style.fontFamily 	= t.getFontFamily();
        elt.style.fontStyle 	= t.getFontStyle();
        elt.style.fontWeight 	= VHtmlHtmlView.fontWeight2Num(t.getFontWeight());
    }

	setNone () : void 				{ this.getHtml().style.textShadow = "0px 0px 0px";  }
	setBlur (val: number) : void 	{ this.getHtml().style.textShadow = "0px 0px " + val + "px"; }
	setShadow (params: Array<number>) : void {
		let color = new IColor( params.slice(2,6) );
		this.getHtml().style.textShadow = color.getCSSRGBAString() + params[0] +"px " + params[1] +"px " + params[6] +"px";
	}

	updateView	( obj: IObject) : void {
		let t = <IText>obj;
    	let elt = this.getHtml();
        elt.innerHTML  = this.getText(t);
		if (t.fontModified()) this.setFont (t);
		super.updateView(obj);
	}

	getAutoElement() : HTMLElement 	{ return this.getHtml(); }
}