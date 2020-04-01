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
		this.updateObjectSize (objid);
		div.style.filter = `blur(0px)`;
    }

	parentWidth() : number			{ return this.getElement().parentElement.clientWidth; }
	parentHeight() : number			{ return this.getElement().parentElement.clientHeight; }

	getOrigin () : Point { 
		if (this.fAbsolutePos)
			return super.getOrigin();
		let div = this.getElement();
		let x = div.offsetWidth / 2;
		let y = div.offsetHeight / 2;
// console.log (this + " '" + div.style.width + "'");
		// let x = div.offsetLeft + div.offsetWidth/2;
		// let y = div.offsetTop + div.offsetHeight / 2;
		return  { x: x, y: y};
	}

	getParentOrigin () : Point { 
		let div = this.getElement().parentElement;
		let r = div.getBoundingClientRect();
		let x = r.left + (div.clientWidth / 2);
		let y = r.top + (div.clientHeight / 2);
		return  { x: r.left + div.clientWidth/2, y: r.top + div.clientHeight / 2};
	}

	getPos(pos: OPosition) : Point {
		let ppos = this.getParentOrigin();
		let x = ppos.x + this.relative2SceneWidth (pos.x - (pos.width * (1 + pos.xorigin * pos.scale) / 2 ));
		let y = ppos.y + this.relative2SceneHeight(pos.y - (pos.height * (1 + pos.yorigin * pos.scale) / 2 ));
		return { x: x, y: y};
	}

	updatePosition(pos: OPosition, elt: HTMLElement) : void {
		if (this.fAbsolutePos) {
			super.updatePosition (pos, elt);
		}
		else {
			elt.style.visibility = (pos.hidden) ? "hidden" : "inherit";
			// this.updateDimensions (pos);
			elt.style.transform = this.getTransform (pos);
		}
	}

	updateColor(color: OColor) {
		let div = this.getElement();
		div.style.background = color.rgb;
		div.style.opacity 	 = color.alpha.toString();
	}

	toString() : string					{ return "JSSceneView"; }
}
