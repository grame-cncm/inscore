
///<reference path="JSObjectView.ts"/>

class JSLayerView extends JSObjectView {

    constructor(parent: JSObjectView) {
		super( document.createElement('div'), parent); 
        this.getElement().className = "inscore-layer";
    }
    clone (parent: JSObjectView) : JSObjectView { return new JSLayerView(parent); }

    toString() : string			{ return "JSLayerView"; }
    parentScale() : number      { return 1; }
}