///<reference path="JSObjectView.ts"/>


//----------------------------------------------------------------------------
class JSSceneView extends JSObjectView {
	
	fAbsolutePos: boolean;

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
	}
	clone (parent: JSObjectView) : JSObjectView { return null; }
	toString() : string					{ return "JSSceneView"; }

	parentScale() : number { 
		let div = this.getElement();
		let scale = Math.min(div.clientWidth, div.clientHeight) / Math.min(screen.width, screen.height) * 2; 
		return scale; 
	}
	getScale(pos: OPosition) : number {  return pos.scale; }

	parentWidth() : number			{ return this.getElement().parentElement.offsetWidth; }
	parentHeight() : number			{ return this.getElement().parentElement.offsetHeight; }

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
