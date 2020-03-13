
"use strict";


//----------------------------------------------------------------------------
class JSSceneView extends JSObjectView {

    constructor(id, objid) {
    	super(document.getElementById(id), null, false);
		this.updateObjectSize (objid);
		this.firstUpdate = true;
    }

	parentWidth()				{ return document.body.clientWidth; }
	parentHeight()				{ return document.body.clientHeight; }
	colorTarget() 				{ return this.getElement(); }

	updateColor(color, div) {
		div.style.background = color.rgb;
		div.style.opacity 	 = color.alpha.toString();
	}

	toString() 					{ return "VSceneView"; }
}
