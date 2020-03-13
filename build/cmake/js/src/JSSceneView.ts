///<reference path="JSObjectView.ts"/>


//----------------------------------------------------------------------------
class JSSceneView extends JSObjectView {

	private firstUpdate: boolean;

    constructor(id: string, objid: number) {
    	super(document.getElementById(id), null, false);
		this.updateObjectSize (objid);
		this.firstUpdate = true;
    }

	parentWidth() : number				{ return document.body.clientWidth; }
	parentHeight() : number				{ return document.body.clientHeight; }
	colorTarget() : HTMLElement			{ return this.getElement(); }

	updateColor(color: OColor, div: HTMLElement) {
		div.style.background = color.rgb;
		div.style.opacity 	 = color.alpha.toString();
	}

	toString() : string					{ return "VSceneView"; }
}
