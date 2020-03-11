
"use strict";

//----------------------------------------------------------------------------
class JSViewFactory {	
	static createScene (id, objid) 		{ 
		const scene = new JSSceneView(id, objid);
		return scene.getId();
	}

	static create (parent, type, objid) 	{ 
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
console.log ("JSViewFactory::create type " + type + " parent id: " + parent);
				return new JSObjectView().getId(); 
									
			default:
console.log ("JSViewFactory::create unknown type " + type + " parent id: " + parent);
				return null;
		}
	}
}


