
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="../model/IText.ts"/>

class VHtmlTextView extends VHtmlHtmlView {

    constructor(parent: VHtmlView) {
		super(parent); 
    	let elt = this.getHtml();
        elt.className = "inscore-txt";
        elt.style.verticalAlign = "middle";
	}

	static getPre( t: IText) {
		if (t.fontModified()) return "<pre style='" + VHtmlTextView.getCSSFont(t)+"'>";
		else return "<pre>";
	}
	
	getText	( obj: IText) : string { return VHtmlTextView.getPre(<IText>obj) + obj.getText() +"</pre>"; }

	setFont	( t: IText) : void {
		let elt = this.getHtml();
        elt.style.fontSize 		= t.getFontSize()+"px";
        elt.style.fontFamily 	= t.getFontFamily();
        elt.style.fontStyle 	= t.getFontStyle();
        elt.style.fontWeight 	= VHtmlHtmlView.fontWeight2Num(t.getFontWeight()).toString();
	}
	static getCSSFont	( t: IText) : string {
		let font = "font-size: " + t.getFontSize()+"px; "
			     + "font-family: "  + t.getFontFamily() +"; "
			     + "font-style: "   + t.getFontStyle() +"; "
				 + "font-weight: "  + VHtmlHtmlView.fontWeight2Num(t.getFontWeight()) + "; ";

		switch (t.fEffect.fEffectArray.length){
			case 0 : return font;
			case 1 : return font += "text-shadow: 0px 0px " + t.fEffect.getEffect()[0] + "px";
			case 2 : return font += "";
			case 3 : return font += "text-shadow: " + VHtmlView.getEffects(t);
		}
		return font;
	}
}