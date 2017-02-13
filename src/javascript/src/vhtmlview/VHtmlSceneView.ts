
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlTools.ts"/>
///<reference path="../model/IObject.ts"/>
///<reference path="../events/documentEvents.ts"/>

//--------------------------------------------------
// VHtmlSceneContainer detects the current element 
// and provides it as a container to the scene
//--------------------------------------------------
class VHtmlSceneContainer extends VHtmlView {  

	static getHtml() : HTMLElement {
		let scripts = document.getElementsByTagName('script');
    	return <HTMLElement>(scripts[scripts.length - 1].parentNode);
	}

    constructor() 	{ super (VHtmlSceneContainer.getHtml()); }
   
   updatePos() : void {
    	let size = TWindow.getSize();
        let w = Math.min(size.w, size.h);
        this.setPos ((size.h - w) / 2.0, (size.w - w) / 2.0, w, w);
    }
}

class VHtmlSceneView extends VHtmlView {
	protected fDoc: VHtmlSceneContainer;
    static fNominalSize = 800;

    constructor(name: string) {
    	let parent = new VHtmlSceneContainer();
    	super (document.createElement('div'), parent);
    	this.fDoc = parent;
        let div = this.getHtml();
		div.className = "inscore-scene";
		div.setAttribute("name", name); 
		div.addEventListener("drop", dropEvent, false);
		div.addEventListener("dragover", dragOverEvent, false);
    }

	relative2SceneX(x: number) : number 			{ return this.fParent.fLeft + super.relative2SceneX(x); }
	relative2SceneY(y: number) : number 			{ return this.fParent.fTop + super.relative2SceneY(y); }
	// nominal scale is intended to adjust contained element scale according to a nominal size
	nominalScale() : number 						{ return Math.min(this.fWidth, this.fHeight) / VHtmlSceneView.fNominalSize; }

	updateView	( obj: IObject) : void {
		this.fDoc.updatePos();
		super.updateView(obj);
	}
}

