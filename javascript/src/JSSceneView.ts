
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
	fFullScreen: boolean;

    constructor(id: string, objid: number) {
		let div = document.getElementById(id);
		let style = window.getComputedStyle(div, null);
		let absolute = style.position == "absolute";
		super(div, null, absolute);
		this.fAbsolutePos = absolute;
		this.updateObjectSize (objid, div.clientWidth, div.clientHeight);
		// for a yet unknown reason, removing the next line result in incorrect
		// children positionning (like if position becomes relative to the window)
		div.style.filter = `blur(0px)`;
		this.fFullScreen = false;
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

	static closeFullscreen() {
		let elt = document as fsDocument;
		if (elt.exitFullscreen) {
			elt.exitFullscreen();
		} else if (elt.webkitExitFullscreen) { /* Safari */
			elt.webkitExitFullscreen();
		} else if (elt.msExitFullscreen) { /* IE11 */
			elt.msExitFullscreen();
		}
	}

	static enterFullscreen(elt: fsElement) {
		if (elt.requestFullscreen) {
			elt.requestFullscreen();
		} else if (elt.webkitRequestFullscreen) { /* Safari */
			elt.webkitRequestFullscreen();
		} else if (elt.msRequestFullscreen) { /* IE11 */
			elt.msRequestFullscreen();
		}
	  }

	updateSpecific(obj: INScoreObject)	: void { 
		let fullscreen = obj.getSceneInfos().fullscreen;
		// there is an issue with the fullscreen mode
		// with standard use, the model is not informed of the fullscreen mode exit
		// if (fullscreen && !this.fFullScreen) {
		// 	this.enterFullscreen(this.getElement() as fsElement);
		// 	this.fFullScreen = true;
		// }
		// else if (!fullscreen && this.fFullScreen) {
		// 	this.closeFullscreen();
		// 	this.fFullScreen = false;
		// }
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
