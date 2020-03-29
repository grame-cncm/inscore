
///<reference path="../libINScore.d.ts"/>
///<reference path="inscore.ts"/>


interface Point {
	x: number;
	y: number;
}


//----------------------------------------------------------------------------
class JSObjectView {

	private static fGlobalID = 0;
	private static fObjects = new Array<JSObjectView>();
	private fID = 0;
	private fElement : HTMLElement;
	private fParent  : JSObjectView;
	private fAbsolutePos : boolean;

    constructor(elt: HTMLElement, parent: JSObjectView, absolute=true) { 
		this.fID = ++JSObjectView.fGlobalID; 		// create a unique identifier
    	JSObjectView.fObjects[this.fID] = this; 	// store the div using its id
    	this.fParent = parent; 
		this.fElement = elt; 
		if (parent) parent.getElement().appendChild (elt);
		this.fAbsolutePos = absolute;
		if (absolute) elt.style.position = "absolute";
	}
	
	toString() : string				{ return "JSObjectView"; }
	getId() : number	 			{ return this.fID; }
	absolutePos() : boolean			{ return this.fAbsolutePos; }
	getElement() : HTMLElement		{ return this.fElement; }
	getParent() : JSObjectView		{ return this.fParent; }
	parentWidth() : number			{ 
		let elt = this.getElement().parentElement;
		return Math.min(elt.offsetWidth, elt.offsetHeight); 
	}
	parentHeight() : number			{ 
		let elt = this.getElement().parentElement;
		return Math.min(elt.offsetWidth, elt.offsetHeight); 
	}

	//---------------------------------------------------------------------
	// parentPos gives the coordinates of the object using inscore schema
	// i.e. the output x and y refers to the center of the element
	parentPos() : Point { 
		let parent = this.getElement().parentElement;
		if (!parent || !this.getParent())
			return { x: 0, y: 0 };
		if (this.getParent().absolutePos())
			return { x: parent.offsetWidth/2, y: parent.offsetHeight/2 };
		let r = parent.getBoundingClientRect();
		return  { x: r.left + parent.offsetWidth/2, y: r.top + parent.offsetHeight / 2};
	}
	posTarget() : HTMLElement		{ return this.fElement; }
	
	updateSpecial(obj: INScoreObject, oid: number)	: boolean { return true; }
	updateSpecific(obj: INScoreObject)	: void { }
	needSpecialUpdate(infos: OUpdateInfos) : boolean { return false; }

	//---------------------------------------------------------------------
	// update methods
	//---------------------------------------------------------------------
	updateView(obj: INScoreObject, oid: number) : void {
		let infos = obj.getUpdateInfos();
		if (infos.deleted  && this.getElement().parentNode) { // parent could be deleted
			this.getElement().parentNode.removeChild(this.getElement());
			return;
		}

		if (infos.newdata || this.needSpecialUpdate(infos)) {
			if (!this.updateSpecial (obj, oid)) return;
			else infos.updatepos = true;
		}
		if ( infos.updatecolor) 
			this.updateColor(infos.color);
		if (infos.updatebrush)
			this.updatePenControl(infos.position.pen);
		this.updateSpecific (obj);
		if (infos.updatepos || infos.updatebrush)
			this.updatePosition(infos.position, this.posTarget());
		if (infos.updateeffect)
			this.updateEffects(infos.effect);
		// this.updateEvents(obj);
	}


	updateColor(color: OColor) : void {
		this.fElement.style.color = color.rgb;
		this.fElement.style.opacity = color.alpha.toString();
	}

	updatePenControl(brush: OPen) : void {
		let elt = this.getElement();
		elt.style.borderWidth = brush.penWidth + 'px';
		elt.style.borderColor = brush.penColor;
		elt.style.borderStyle = JSObjectView.penStyle2Css (brush.penStyle);
	}

	getPos(pos: OPosition) : Point {
		let ppos = this.parentPos();
		let x = ppos.x + this.relative2SceneWidth (pos.x - (pos.width * (1 + pos.xorigin * pos.scale) / 2 ));
		let y = ppos.y + this.relative2SceneHeight(pos.y - (pos.height * (1 + pos.yorigin * pos.scale) / 2 ));
		return { x: x, y: y};
	}

	updatePosition(pos: OPosition, elt: HTMLElement) : void {
		elt.style.visibility = (pos.hidden) ? "hidden" : "inherit";
		this.updateDimensions (pos);
		let p = this.getPos (pos);
		elt.style.left 	= p.x + "px";
		elt.style.top  	= p.y + "px";
		elt.style.zIndex = pos.zorder.toString();
		elt.style.transform = this.getTransform (pos);
	}

	getTransform(pos: OPosition) : string {
		let transform = "";
		if (pos.scale != 1)  transform += `scale(${pos.scale},${pos.scale}) `;
		if (pos.xangle) transform += `rotateX(${pos.xangle}deg) `;
		if (pos.yangle) transform += `rotateY(${pos.yangle}deg) `;
		if (pos.zangle) transform += `rotateZ(${pos.zangle}deg) `;
		return transform;
	}

	updateDimensions(pos: OPosition) : void {
		let elt = this.getElement();
		elt.style.width = this.relative2SceneWidth(pos.width) + "px";
		elt.style.height = this.relative2SceneHeight(pos.height) + "px";
	}

	getOriginOffset(xo : number, yo: number)  : Point { 
		let w = this.getElement().offsetWidth;
		let h = this.getElement().offsetHeight;
		return { x: -w * xo/2, y: -h * yo/2 }; 
	}

	//------------------------------------------------------------------------------------
	// update effects
	updateEffects(effect: OEffect): void {
console.log (this + " updateEffects type: " + effect.type);
		let elt = this.getElement();
		switch (effect.type) {
			case Effect.kNone: this.removeEffect (elt);
				break;
			case Effect.kBlur: this.setBlur (elt, effect.blur.radius);
				break;
			case Effect.kColorize: console.log (this + ": colorize effect is not supported");
				break;
			case Effect.kShadow: this.setShadow(elt, effect.shadow);
				break;
		}
	}

	removeEffect(elt: HTMLElement): void { this.setBlur(elt, 0); }
	setBlur(elt: HTMLElement, val: number): void {
		elt.style.boxShadow = "(0px 0px)";
		elt.style.filter = `blur(${val}px)`;
	}

	setShadow(elt: HTMLElement, val: OShadow): void {
console.log (this + " setShadow " + `${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px`);
		elt.setAttribute("filter", `drop-shadow(${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px)`);
		// elt.style.boxShadow = `${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px`;
		// elt.style.filter = "blur(0)";
	}

	//---------------------------------------------------------------------
	// conversions from inscore to scene space and reverse
	relative2SceneX(x : number)  : number			{ return this.parentWidth() * (x + 1.0) / 2.0; }
	relative2SceneY(y : number)  : number			{ return this.parentHeight() * (y + 1.0) / 2.0; }
	relative2SceneWidth(width : number)  : number	{ return this.parentWidth() * width / 2.0; }
	relative2SceneHeight(height : number) : number	{ return this.parentHeight() * height / 2.0; }
	scene2RelativeWidth(width : number)	 : number	{ return (width * 2.0) / this.parentWidth(); }
	scene2RelativeHeight(height : number) : number	{ return (height * 2.0) / this.parentHeight(); }
	scene2RelativeX(x : number)  : number			{ return x / (this.parentWidth() / 2.0) - 1; }
	scene2RelativeY(y : number)  : number			{ return y / (this.parentHeight() / 2.0) - 1; }

	//---------------------------------------------------------------------
	// called from javascript to update object size on model side
	updateObjectSize (objid : number) : void {
		let obj = INScore.objects().create(objid);
// console.log("JSObjectView::updateObjectSize " + this + " " + this.getElement().clientWidth + " -> " + this.parentWidth());
		let r = this.getElement().getBoundingClientRect();
		obj.updateWidth  (this.scene2RelativeWidth  (r.width)); 
		obj.updateHeight (this.scene2RelativeHeight (r.height)); 
		INScore.objects().del (obj);		
	}

	//---------------------------------------------------------------------
	// utilities
	debug(target: HTMLElement, x: number, y: number, color: string) : void {
		let div = document.createElement('div');
		div.style.position = "absolute";
		div.style.left = x + "px";
		div.style.top = y + "px";
		div.style.width = 10 + "px";
		div.style.height = 10 + "px";
		div.style.background = color;
		if (target) target.appendChild (div);
		else document.body.appendChild (div);
	}

	static penStyle2Css(style: number): string {
		let str = "solid";
		switch (style) {
			case INScoreModule.kDashDotStyle:
			case INScoreModule.kDashStyle:			str = "dashed"; break;
			case INScoreModule.kDashDotDotStyle:
			case INScoreModule.kDotStyle:			str = "dotted"; break;
		}
		return str;
	}
 
	//---------------------------------------------------------------------
	// main update method
	static updateObjectView (id : number, oid : number)	: void { 
    	let view = JSObjectView.fObjects[id];
    	if (view) {
	    	let obj = INScore.objects().create(oid);
    		view.updateView (obj, oid); 
    		INScore.objects().del (obj);
    	}
    }

    static getVObject (id : number)	: JSObjectView	{ return JSObjectView.fObjects[id]; }
}
