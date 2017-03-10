
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
        if(t.fEffect.fEffectModified){

			switch (t.fEffect.fEffectArray.length){
				case 0 : elt.style.textShadow = "text-shadow: 0px 0px";
					break;
				case 1 : elt.style.textShadow = "0px 0px " + t.fEffect.getEffect()[0] + "px";
				console.log("VHtmlHtmlView setFont blur test : " + "text-shadow: 0px 0px " + t.fEffect.getEffect()[0] + "px");
					break;
				case 2 : "";
					break;
				case 3 : elt.style.textShadow = VHtmlView.getEffects(t);
					break;
			}
        	}
    }

	updateView	( obj: IObject) : void {
		let t = <IText>obj;
    	let elt = this.getHtml();
        elt.innerHTML  = this.getText(t);
		if (t.fontModified() || obj.fEffect.fEffectModified) this.setFont (t);
		super.updateView(obj);
	}

	getAutoElement() : HTMLElement 	{ return this.getHtml(); }
}