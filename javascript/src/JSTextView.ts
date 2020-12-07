
///<reference path="JSHtmlView.ts"/>

class JSTextView extends JSHtmlView {

    constructor(parent: JSObjectView) {
		super(parent); 
		this.getElement().className = "inscore-txt";
		this.getElement().style.whiteSpace = "nowrap";
    }
	clone (parent: JSObjectView) : JSObjectView { return new JSTextView(parent); }

	toString() : string					{ return "JSTextView"; }

	getText (text: string) : string {
		return text.replace(/\r?\n/g, "<br />");   // transforms new lines in <br />
	}
}