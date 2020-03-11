
"use strict";


//----------------------------------------------------------------------------
class JSSceneView extends JSObjectView {

    constructor(id, objid) {
    	super(document.getElementById(id), null);
		this.updateObjectSize (objid);
    }

	parentWidth()				{ return document.body.clientWidth; }
	parentHeight()				{ return document.body.clientHeight; }
	colorTarget() 				{ return this.getElement(); }

	updateColor(obj, div) {
		if (obj.colorChanged()) {
			div.style.background = obj.getColor();
			div.style.opacity = obj.getAlpha().toString();
		}
	}

	updateObjectSize (objid) {
		let obj = INScore.objects().create(objid);
		obj.updateWidth  (super.scene2RelativeWidth  (this.getElement().clientWidth)); 
		obj.updateHeight (super.scene2RelativeHeight (this.getElement().clientHeight)); 
		INScore.objects().del (obj);		
	}
}


