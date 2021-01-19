
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="../model/IText.ts"/>

class VHtmlTextView extends VHtmlHtmlView {

    constructor(parent: VHtmlView) {
		super(parent); 
    	let elt = this.getHtml();
        elt.className = "inscore-txt";
        elt.style.verticalAlign = "middle";
	}
}