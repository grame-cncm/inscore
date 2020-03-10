
"use strict";


//----------------------------------------------------------------------------
class JSObjectView {

    constructor() 		{ 
    	this.id = ++JSObjectView.fGlobalID; 
    	JSObjectView.fObjects[this.id] = this;
    }
    getId() 				{ return this.id; }
    updateObjectView(oid) 	{ 
    	console.log ("JS JSObjectView::updateObjectView oid: " + oid); 
    	let obj = INScore.objects().create(oid);
    	console.log ("JS JSObjectView::updateObjectView w/h : " + obj.getWidth() + " " + obj.getHeight()); 
    	
    }
    
    static getVObject (id)		{ return JSObjectView.fObjects[id]; }
    static updateView (id, oid)	{ 
    	let view = JSObjectView.fObjects[id];
    	if (view)
    		view.updateObjectView(oid); }
}
JSObjectView.fGlobalID = 0;
JSObjectView.fObjects = new Array;

//----------------------------------------------------------------------------
class VSceneView extends JSObjectView {

    constructor(id) {
    	super();
		this.div = document.getElementById(id);
		this.x = this.div.getBoundingClientRect().left;
		this.y = this.div.getBoundingClientRect().top;
		this.w = this.div.clientWidth;
		this.h = this.div.clientHeight;
		console.log ("JS create VSceneView pos " + this.x + "," + this.y + " size: " + this.w + "," + this.h)
    }
}


//----------------------------------------------------------------------------
class ViewFactory {	
	static createScene (id) 			{ return new VSceneView(id).getId(); }
	static create (parent, type) 	{ 
		switch (type) {
			case "arc":
			case "audio":
			case "curve":
			case "ellipse":
			case "fileWatcher":
			case "graph":
			case "fastgraph":
			case "radialgraph":
			case "grid":
			case "gmn":
			case "gmnf":
			case "pianoroll":
			case "pianorollf":
			case "pianorollstream":
			case "gmnstream":
			case "html":
			case "htmlf":
			case "img":
			case "layer":
			case "line":
			case "memimg":
			case "musicxml":
			case "musicxmlf":
			case "polygon":
			case "rect":			
			case "rshape":
			case "svg":
			case "svgf":
			case "scene":
			case "sig":
			case "signode":
			case "txt":
			case "txtf":
			case "video":
console.log ("JS ViewFactory::create type " + type + " parent id: " + parent);
				return new JSObjectView().getId(); 
									
			default:
console.log ("JS ViewFactory::create unknown type " + type + " parent id: " + parent);
				return null;
		}
	}
}


