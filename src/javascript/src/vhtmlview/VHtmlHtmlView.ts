
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
	fontWeight2Num	( weight: string) : string {
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
        elt.style.fontWeight 	= this.fontWeight2Num(t.getFontWeight());
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