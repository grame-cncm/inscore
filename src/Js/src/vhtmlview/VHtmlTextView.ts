
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IText.ts"/>

class VHtmlTextView extends VHtmlView {

    constructor(parent: VHtmlView) {
		super( document.createElement('div'), parent); 
    	let div = this.getDiv();
        div.className = "txt";
        parent.getDiv().appendChild (div);
    }    

	updateView	( obj: IObject) : void {
		let t = <IText>obj;
		this.updatePos (obj);
//		this.updateColor (obj);
    	let div = this.getDiv();
        div.innerHTML  = "<pre>" + t.getText() +"</pre>";
	}
}