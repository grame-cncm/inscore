
///<reference path="JSHtmlView.ts"/>

class JSTextView extends JSHtmlView {

    constructor(parent: JSObjectView) {
		super(parent); 
        this.getElement().className = "inscore-txt";
    }
	clone (parent: JSObjectView) : JSObjectView { return new JSTextView(parent); }

	toString() : string					{ return "JSTextView"; }

	getText (infos: OTextInfo) : string {
		return infos.text.replace(/\r?\n'/g, "<br />");
	}
}