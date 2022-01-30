
///<reference path="JSObjectView.ts"/>

class JSLayerView extends JSObjectView {

    constructor(parent: JSObjectView) {
		super( document.createElement('div'), parent); 
    }
    clone (parent: JSObjectView) : JSObjectView { return new JSLayerView(parent); }

	updateSpecial ( obj: INScoreObject)	: boolean {		
		this.getElement().id = obj.getID();
		return true;
	}

    toString() : string			{ return "JSLayerView"; }
    parentScale() : number      { return 1; }
}