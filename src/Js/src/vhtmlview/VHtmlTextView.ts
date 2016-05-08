
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="../model/IText.ts"/>

class VHtmlTextView extends VHtmlHtmlView {

    constructor(parent: VHtmlView) {
		super(parent); 
    	let div = this.getDiv();
        div.className = "inscore-txt";
        div.style.verticalAlign = "middle";
    }    

	getText	( obj: IText) : string { return "<pre>" + obj.getText() +"</pre>"; }
}