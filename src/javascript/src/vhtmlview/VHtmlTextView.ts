
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="../model/IText.ts"/>

class VHtmlTextView extends VHtmlHtmlView {

    constructor(parent: VHtmlView) {
		super(parent); 
    	let elt = this.getHtml();
        elt.className = "inscore-txt";
        elt.style.verticalAlign = "middle";
	}

	getPre( t: IText) {
		if (t.fontModified()) return "<pre style='" + this.getCSSFont(t)+"'>";
		else return "<pre>";
	}
	
	getText	( obj: IText) : string { return this.getPre(<IText>obj) + obj.getText() +"</pre>"; }

	setFont	( t: IText) : void {
		let elt = this.getHtml();
        elt.style.fontSize 		= t.getFontSize()+"px";
        elt.style.fontFamily 	= t.getFontFamily();
        elt.style.fontStyle 	= t.getFontStyle();
        elt.style.fontWeight 	= this.fontWeight2Num(t.getFontWeight()).toString();
	}
	getCSSFont	( t: IText) : string {

		return "font-size: " + t.getFontSize()+"px; "
    			+ "font-family: " + t.getFontFamily() +"; "
    			+ "font-style: "  + t.getFontStyle() +"; "
    			+ "font-weight: " + this.fontWeight2Num(t.getFontWeight()) + "; "
				+ "text-shadow: " + VHtmlView.getEffects(t);
	}
}