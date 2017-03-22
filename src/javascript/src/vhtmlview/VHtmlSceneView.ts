
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
	protected fAbsolutePos: boolean;
	protected fReferenceWidth: number;

    //-----------name for document getElementById-------------
    protected fName : string

    constructor(name: string) {
    	let parent = new VHtmlSceneContainer();
    	super (document.createElement('div'), parent);
    	this.fDoc = parent;
    	this.fReferenceWidth = Math.min(screen.width, screen.height);

        let div = this.getHtml();
		div.className = "inscore-scene";
		div.setAttribute("name", name); 
		div.addEventListener("drop", inscore_dropEvent, false);
		div.addEventListener("dragover", inscore_dragOverEvent, false);	
		this.fAbsolutePos = false;
        div.setAttribute("fullscreen", "yes");

		let style = window.getComputedStyle(div);
	    this.fAbsolutePos = (style.position === 'absolute');
    }

	getViewScale (obj: IObject): number 			{ return Math.min(obj.fPosition.getWidth(), obj.fPosition.getHeight()) * obj.fPosition.getScale(); }

	relative2SceneX(x: number) : number 			{ return this.fParent.fLeft + super.relative2SceneX(x); }
	relative2SceneY(y: number) : number 			{ return this.fParent.fTop + super.relative2SceneY(y); }
	relative2SceneWidth(width: number) : number 	{ return this.fReferenceWidth * width / 2; }
	relative2SceneHeight(height: number) : number	{ return this.fReferenceWidth * height / 2; }

	getTranslate (obj: IObject): string 			{ return this.fAbsolutePos ? super.getTranslate(obj) : ""; }
	scenePosition(obj: IObject): void{
		let scene = <IScene>obj;
		let div = this.getHtml();
		div.style.position = (scene.fAbsolutePos) ? IScene.kAbsolute : IScene.kRelative;
	}

	updateView	( obj: IObject) : void {
		this.scenePosition(obj);
		this.fDoc.updatePos();
		this.fWidth = this.fDoc.fWidth;
		this.fHeight = this.fDoc.fHeight;
		super.updateView(obj);
        this.enableDisableFullScreen(obj);
	}

	   //-------------------FullScreenManagement---------------------
    enableDisableFullScreen(obj: IObject) {
		let scene = <IScene>obj;
        if (scene.fFullScreen) this.launchFullscreen(this.getHtml());
        else this.exitFullscreen();
    }

    // Find the right method, call on correct element
    launchFullscreen(element: HTMLElement): void {
        if (element.requestFullscreen) {
            //Standard
            element.requestFullscreen();
        } else if (element.mozRequestFullScreen) {
            //Mozilla
            element.mozRequestFullScreen();
        } else if (element.webkitRequestFullscreen) {
            //Chrome - Edge
            element.webkitRequestFullscreen();
        } else if (element.msRequestFullscreen) {
            //IE
            element.msRequestFullscreen();
        }
    }

    exitFullscreen(): void {
        if (document.exitFullscreen) {
            //Standard
            document.exitFullscreen();
        } else if (document.mozCancelFullScreen) {
            //Mozilla
            document.mozCancelFullScreen();
        } else if (document.webkitExitFullscreen) {
            //Chrome - Edge
            document.webkitExitFullscreen();
        } else if (document.msExitFullscreen) {
            //IE
            document.msExitFullscreen();
        }
    }
}