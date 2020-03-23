///<reference path="JSObjectView.ts"/>


//----------------------------------------------------------------------------
class JSSceneView extends JSObjectView {

	private firstUpdate: boolean;

    constructor(id: string, objid: number) {
    	super(document.getElementById(id), null, false);
		this.updateObjectSize (objid);
		this.firstUpdate = true;
    }
	
	updateColor(color: OColor) {
		let div = this.getElement();
		div.style.background = color.rgb;
		div.style.opacity 	 = color.alpha.toString();
	}


	toString() : string					{ return "JSSceneView"; }
}
