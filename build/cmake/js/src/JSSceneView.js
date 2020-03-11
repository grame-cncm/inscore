
"use strict";


//----------------------------------------------------------------------------
class JSSceneView extends JSObjectView {

    constructor(id, objid) {
    	super();
		this.div = document.getElementById(id);
		this.updateObjectSize (objid);
    }

	parentWidth()				{ return document.body.clientWidth; }
	parentHeight()				{ return document.body.clientHeight; }

	updateColor(obj) {
		if (obj.colorChanged()) {
			this.div.style.background = obj.getColor();
	console.log ("JSSceneView::updateColor: " + obj.getColor());
			this.div.style.opacity = obj.getAlpha().toString();
		}
	}

	updateObjectSize (objid) {
		let obj = INScore.objects().create(objid);
		obj.updateWidth  (super.scene2RelativeWidth (this.div.clientWidth)); 
		obj.updateHeight (super.scene2RelativeHeight (this.div.clientHeight)); 
		INScore.objects().del (obj);		
	}
}


