
///<reference path="inscoreGlue.ts"/>
///<reference path="JSObjectView.ts"/>
///<reference path="JSHtmlView.ts"/>
///<reference path="JSSceneView.ts"/>

//----------------------------------------------------------------------------
class JSViewFactory {	
	static createScene (id: string, objid: number) : number { 
		const scene = new JSSceneView(id, objid);
		return scene.getId();
	}


	static create (parentid: number, type: string, objid: number) : number	{ 
		let parent = JSObjectView.getVObject(parentid);
		switch (type) {
			case "txt":
console.log ("JSViewFactory::create text parent id: " + parentid);
			let view = new JSHtmlView(parent);
			view.updateObjectSize (objid);
			return view.getId(); 

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
			case "pianoroll":
			case "pianorollstream":
			case "gmnstream":
			case "html":
			case "img":
			case "layer":
			case "line":
			case "memimg":
			case "musicxml":
			case "polygon":
			case "rect":			
			case "rshape":
			case "svg":
			case "scene":
			case "sig":
			case "signode":
			case "video":
console.log ("JSViewFactory::create type " + type + " parent id: " + parent);
				return null; 

			case "gmnf":
			case "pianorollf":
			case "htmlf":
			case "musicxmlf":
			case "svgf":
			case "txtf":
		console.log ("JSViewFactory::create type " + type + " parent id: " + parent);
				return null; 
		
			default:
console.log ("JSViewFactory::create unknown type " + type + " parent id: " + parent);
				return null;
		}
	}
}


