
///<reference path="inscoreGlue.ts"/>
///<reference path="JSObjectView.ts"/>
///<reference path="JSTextView.ts"/>
///<reference path="JSTextfView.ts"/>
///<reference path="JSHtmlfView.ts"/>
///<reference path="JSSceneView.ts"/>
///<reference path="JSRectView.ts"/>
///<reference path="JSEllipseView.ts"/>
///<reference path="JSLineView.ts"/>
///<reference path="JSImageView.ts"/>
///<reference path="JSArcView.ts"/>
///<reference path="JSPolygonView.ts"/>
///<reference path="JSCurveView.ts"/>
///<reference path="JSGMNView.ts"/>
///<reference path="JSGMNfView.ts"/>
///<reference path="JSXMLView.ts"/>
///<reference path="JSXMLfView.ts"/>
///<reference path="JSSVGView.ts"/>
///<reference path="JSPianorollView.ts"/>
///<reference path="JSPianorollfView.ts"/>
///<reference path="JSLayerView.ts"/>
///<reference path="JSSVGfView.ts"/>
///<reference path="JSVideoView.ts"/>
///<reference path="TSyncManager.ts"/>


//----------------------------------------------------------------------------
class JSViewFactory {	
	static createScene (id: string, objid: number) : number { 
		const scene = new JSSceneView(id, objid);
		return scene.getId();
	}


	static create (parentid: number, type: string, objid: number) : number	{ 
		let parent = JSObjectView.getVObject(parentid);
		let view = null;

		switch (type) {
			case "txt": 	  view = new JSTextView(parent); break; 			
			case "html":	  view = new JSHtmlView(parent); break; 			
			case "txtf":	  view = new JSTextfView(parent); break;
			case "htmlf":	  view = new JSHtmlfView(parent); break;
			
			case "rect":	  view = new JSRectView(parent); break; 
			case "ellipse":   view = new JSEllipseView(parent); break; 
			case "line": 	  view = new JSLineView(parent); break; 
			case "img":  	  view = new JSImageView(parent); break;
			case "arc": 	  view = new JSArcView(parent); break;
			case "polygon":   view = new JSPolygonView(parent); break;
			case "curve":     view = new JSCurveView(parent); break;
			case "gmn":       view = new JSGMNView(parent, gGlue.guido()); break;
			case "gmnf":	  view = new JSGMNfView(parent, gGlue.guido()); break;
			case "pianoroll": view = new JSPianoRollView(parent, gGlue.guido()); break;
			case "pianorollf": view = new JSPianoRollfView(parent, gGlue.guido()); break;
			case "musicxml":  view = new JSXMLView(parent, gGlue.xmllib(), gGlue.guido()); break;
			case "musicxmlf": view = new JSXMLfView(parent, gGlue.xmllib(), gGlue.guido()); break;

			case "svg":       view = new JSSVGView(parent); break;
			case "layer":	  view = new JSLayerView(parent); break;
			case "svgf": 	  view = new JSSVGfView(parent); break;
			case "video":	  view = new JSVideoView(parent); break;

			case "audio":
			case "fileWatcher":
			case "graph":
			case "fastgraph":
			case "radialgraph":
			case "grid":
			case "pianorollstream":
			case "gmnstream":
			case "memimg":
			case "rshape":
			case "sig":
			case "signode":
console.log ("JSViewFactory::create pending type " + type + " parent id: " + parent);
				break; 

			default:
				console.error ("JSViewFactory::create unknown type " + type + " parent id: " + parent);
		}
		if (view) {
			view.setSyncManager (new TSyncManager(view));
			return view.getId();
		}
		return 0;
	}
}


