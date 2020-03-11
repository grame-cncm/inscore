
"use strict";


//----------------------------------------------------------------------------
class JSObjectView {

    constructor(elt, parent) { 
		this.id = ++JSObjectView.fGlobalID; 	// create a unique identifier
    	JSObjectView.fObjects[this.id] = this; 	// store the div using its id
    	this.fParent = parent; 
    	this.fElement = elt; 
	}
	
	getElement()				{ return this.fElement; }
	parentWidth()				{ return this.fElement.clientWidth; }
	parentHeight()				{ return this.fElement.clientHeight; }


    getId() 			{ return this.id; }
	colorTarget() 		{ return this.fDiv; }

	updateView(obj) {
		//this.updatePos(obj);
		this.updateColor(obj, this.colorTarget());
		// this.updatePenControl(obj);
		// this.updateEffects(obj);
		// this.updateEvents(obj);
	}


	updateColor(obj, elt) {
		if (obj.colorChanged()) {
			elt.style.color = obj.getColor();
			elt.style.opacity = obj.getAlpha().toString();
		}
	}

	// updatePos(obj: IObject): void {
	// 	let pos = this.fPositionHandler();
	// 	if (pos.x == kNoPosition) {
	// 		this.getHtml().style.visibility = "hidden";
	// 		return;
	// 	}

	// 	let size = this.getSize(obj);
	// 	let z = obj.fPosition.getZOrder();
	// 	let left = this.relative2SceneX(pos.x);
	// 	let top = this.relative2SceneY(pos.y);
	// 	this.setPos(top, left, size.w, size.h);		// store the metrics
	// 	let shear = obj.fPosition.getShear();

	// 	let elt = this.getHtml();
	// 	elt.style.width = size.w + "px";
	// 	elt.style.height = size.h + "px";
	// 	elt.style.left = left + "px";
	// 	elt.style.top = top + "px";
	// 	elt.style.zIndex = z.toString();
	// 	elt.style.transform = this.getTransform(obj) + " skewX(" + shear[0] + "rad) skewY(" + shear[1] + "rad)";
	// 	elt.style.visibility = obj.fPosition.getVisible() ? "inherit" : "hidden";
	// }

	parentWidth()				{ return this.fParent.clientWidth; }
	parentHeight()				{ return this.fParent.clientHeight; }

	relative2SceneY(y) 			{ return this.parentHeight() * (y + 1.0) / 2.0; }
	relative2SceneX(x) 			{ return this.parentWidth() * (x + 1.0) / 2.0; }
	relative2SceneWidth(width) 	{ return Math.min(this.parentWidth(), this.parentHeight()) * width / 2.0; }
	relative2SceneHeight(height){ return Math.min(this.parentWidth(), this.parentHeight()) * height / 2.0; }
	scene2RelativeWidth(width)	{ return (width * 2.0) / this.parentWidth(); }
	scene2RelativeHeight(height){ return (height * 2.0) / this.parentHeight(); }
	scene2RelativeX(x) 			{ return x / (this.parentWidth() / 2.0) - 1; }
	scene2RelativeY(y) 			{ return y / (this.parentHeight() / 2.0) - 1; }

    static getVObject (id)		{ return JSObjectView.fObjects[id]; }
    static updateObjectView (id, oid)	{ 
    	let view = JSObjectView.fObjects[id];
    	if (view) {
	    	let obj = INScore.objects().create(oid);
    		view.updateView (obj); 
    		INScore.objects().del (obj);
    	}
    }
}
JSObjectView.fGlobalID = 0;
JSObjectView.fObjects = new Array;
