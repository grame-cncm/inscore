///<reference path="JSObjectView.ts"/>


//----------------------------------------------------------------------------
class JSSceneView extends JSObjectView {

    constructor(id: string, objid: number) {
    	super(document.getElementById(id), null, false);
		this.updateObjectSize (objid);
    }

	parentWidth() : number			{ return this.getElement().parentElement.offsetWidth; }
	parentHeight() : number			{ return this.getElement().parentElement.offsetHeight; }

	updateColor(color: OColor) {
		let div = this.getElement();
		div.style.background = color.rgb;
		div.style.opacity 	 = color.alpha.toString();
	}

	toString() : string					{ return "JSSceneView"; }
}
