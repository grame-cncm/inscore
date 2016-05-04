
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlTools.ts"/>
///<reference path="../model/IObject.ts"/>

//--------------------------------------------------
// a fake html view to serve as scene view parent
//--------------------------------------------------
class VHtmlDocument extends VHtmlView {  
    constructor() {
    	let foo: HTMLDivElement;
    	super (foo);
	}
   
   updatePos() : void {
    	let size = TWindow.getSize();
        let w = Math.min(size.w, size.h);
        this.setPos ((size.h - w) / 2.0, (size.w - w) / 2.0, w, w);
    }
}

class VHtmlSceneView extends VHtmlView {
    protected fDoc: VHtmlDocument;
    constructor() {
    	let doc = new VHtmlDocument();
    	super (document.createElement('div'), doc);
    	this.fDoc = doc;
    	let div = this.getDiv();
        this.getDiv().className = "scene";
        document.getElementsByTagName('body')[0].appendChild (div);
    }

	relative2SceneX(x: number) : number 			{ return this.fParent.fLeft + super.relative2SceneX(x); }
	relative2SceneY(y: number) : number 			{ return this.fParent.fTop + super.relative2SceneY(y); }

	updateView	( obj: IObject) : void {
		this.fDoc.updatePos();
		this.updatePos (obj);
		this.updateColor (obj);
		return;
	}
}

