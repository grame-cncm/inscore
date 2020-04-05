
///<reference path="JSObjectView.ts"/>

class JSLayerView extends JSObjectView {

    constructor(parent: JSObjectView) {
		super( document.createElement('div'), parent); 
        this.getElement().className = "inscore-layer";
    }

	toString() : string					{ return "JSLayerView"; }
	// updateDimensions(pos: OPosition) : void {}
}