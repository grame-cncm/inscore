
///<reference path="JSObjectView.ts"/>
///<reference path="navigator.ts"/>

interface fsElement extends HTMLElement {
	webkitRequestFullscreen() : void;
	msRequestFullscreen() : void;
}
interface fsDocument extends Document {
	webkitExitFullscreen() : void;
	msExitFullscreen() : void;
}
 
//----------------------------------------------------------------------------
class JSSceneView extends JSObjectView {
	
	fAbsolutePos: boolean;

    constructor(id: string, objid: number) {
		let div = document.getElementById(id);
		let style = window.getComputedStyle(div, null);
		let absolute = style.position == "absolute";
		super(div, null, absolute);
		this.fAbsolutePos = absolute;
		let obj = INScore.objects().adapter(objid);
		this.updateObjectSize (obj, div.clientWidth, div.clientHeight);
		// this.updateObjectSize (objid, div.clientWidth, div.clientHeight);
		// for a yet unknown reason, removing the next line result in incorrect
		// children positionning (like if position becomes relative to the window)
		div.style.filter = `blur(0px)`;
	}
	clone (parent: JSObjectView) : JSObjectView { return null; }
	toString() : string					{ return "JSSceneView"; }

	getOrigin() : Point { 
		let p = super.getOrigin();
		// the browsers below don't compute children absolute position like Chrome or Firefox
		if (Safari || Explorer || Edge) {
			let div = this.getElement();
			p.x += div.offsetLeft;
			p.y += div.offsetTop;
		}
		return p;
	}

	parentScale() : number { 
		let div = this.getElement();
		let screenref = AndroidOS ? Math.max(screen.width, screen.height) :  Math.min(screen.width, screen.height);
		let scale = Math.min(div.clientWidth, div.clientHeight) / screenref * 2; 
 		return scale; 
	}
	getScale(scale: number) : number { return scale; } 

	parentWidth() : number			{ return this.getElement().parentElement.offsetWidth; }
	parentHeight() : number			{ return this.getElement().parentElement.offsetHeight; }

	private exitFullscreen() {
		let elt = document as fsDocument;
		if (elt.exitFullscreen) {
			elt.exitFullscreen();
		} else if (elt.webkitExitFullscreen) { /* Safari */
			elt.webkitExitFullscreen();
		} else if (elt.msExitFullscreen) { /* IE11 */
			elt.msExitFullscreen();
		}
		this.getElement().removeEventListener ("fullscreenchange", (event: UIEvent) => { this.closeFullscreen(event)} );
	}

	private enterFullscreen(elt: fsElement) {
		if (elt.requestFullscreen) {
			elt.requestFullscreen();
		} else if (elt.webkitRequestFullscreen) { /* Safari */
			elt.webkitRequestFullscreen();
		} else if (elt.msRequestFullscreen) { /* IE11 */
			elt.msRequestFullscreen();
		}
		else {
			console.log ("JSSceneView.enterFullscreen: no handler available.")
			return;
		}
		this.getElement().addEventListener ("fullscreenchange", (event: UIEvent) => { this.closeFullscreen(event)} );
	}

	private inFullscreen () : boolean {
		return document.fullscreenElement && (document.fullscreenElement == this.getElement());
	}

	private closeFullscreen (event: UIEvent) { 		// called on fullscreen event
		if (!this.inFullscreen()) {
			inscore.postMessageStrI ("/ITL/" + this.getElement().id, "fullscreen", 0);
			this.getElement().removeEventListener ("fullscreenchange", (event: UIEvent) => { this.closeFullscreen(event)} );
		}
	}

	updateSpecific(obj: INScoreObject)	: void { 
		let fullscreen = obj.getSceneInfos().fullscreen;
		let infull = this.inFullscreen();
		if (fullscreen && !infull) {
			this.enterFullscreen(this.getElement() as fsElement);
		}
		else if (!fullscreen && infull) {
			this.exitFullscreen();
		}
	}

	updatePosition(pos: OPosition, elt: HTMLElement) : void {
		if (this.fAbsolutePos) {
			super.updatePosition (pos, elt);
		}
		else {
			elt.style.visibility = (pos.hidden) ? "hidden" : "inherit";
			elt.style.transform = this.getTransform (pos);
		}
	}

	updateColor(color: OColor) {
		let div = this.getElement();
		div.style.background = color.rgb;
		div.style.opacity 	 = color.alpha.toString();
	}
}
