
///<reference path="../lib/libINScore.d.ts"/>
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

    constructor(elt: HTMLElement, parent: JSObjectView, absolute=true) { 
		this.fID = ++JSObjectView.fGlobalID; 		// create a unique identifier
    	JSObjectView.fObjects[this.fID] = this; 	// store the div using its id
    	this.fParent = parent; 
		this.fElement = elt; 
		if (parent) parent.getElement().appendChild (elt);
		if (absolute) elt.style.position = "absolute";
	}
	
	toString() : string				{ return "JSObjectView"; }
	getId() : number	 			{ return this.fID; }
	getElement() : HTMLElement		{ return this.fElement; }
	getParent() : JSObjectView		{ return this.fParent; }
	parentWidth() : number			{ 
		let elt = this.getElement().parentElement;
		return Math.min(elt.clientWidth, elt.clientHeight); 
	}
	parentHeight() : number			{ 
		let elt = this.getElement().parentElement;
		return Math.min(elt.clientWidth, elt.clientHeight); 
	}
	
	updateSpecial(obj: INScoreObject, oid: number)	: boolean { return true; }
	updateSpecific(obj: INScoreObject)	: void { }
	needSpecialUpdate(infos: OUpdateInfos) : boolean { return false; }

	//---------------------------------------------------------------------
	// update methods
	//---------------------------------------------------------------------
	updateView(obj: INScoreObject, oid: number, force = false) : void {
		let infos = obj.getUpdateInfos();
		if (infos.deleted  && this.getElement().parentNode) { // parent could be deleted
			this.getElement().parentNode.removeChild(this.getElement());
			return;
		}

		if (infos.newdata || this.needSpecialUpdate(infos)) {
			if (!this.updateSpecial (obj, oid)) return;
			else infos.updatepos = true;
		}
		if (infos.updatecolor) 
			this.updateColor(infos.color);
		if (infos.updatebrush)
			this.updatePenControl(infos.position.pen);
		this.updateSpecific (obj);
		if (infos.updatepos || infos.updatebrush || force)
			this.updatePosition(infos.position, this.getElement());
		if (infos.updateeffect)
			this.updateEffects(infos.effect);
		if (infos.updateevents)
			this.updateEvents(infos.events);
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

	getOrigin() : Point { 
		let div = this.getElement();
		return { x: div.clientWidth/2, y: div.clientHeight/2 };
	}

	getPos(pos: OPosition) : Point {
		let ppos = this.getParent().getOrigin();
		let x = ppos.x + this.relative2SceneWidth (pos.x) - (this.getElement().clientWidth * (1 + pos.xorigin * pos.scale) / 2 );
		let y = ppos.y + this.relative2SceneHeight(pos.y) - (this.getElement().clientHeight * (1 + pos.yorigin * pos.scale) / 2 );
		return { x: x, y: y};
	}

	updatePosition(pos: OPosition, elt: HTMLElement) : void {
		elt.style.visibility = (pos.hidden) ? "hidden" : "inherit";
		this.updateDimensions (pos);
		elt.style.transform = this.getTransform (pos);
		let p = this.getPos (pos);
		elt.style.left 	= p.x + "px";
		elt.style.top  	= p.y + "px";
		elt.style.zIndex = pos.zorder.toString();
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

	//------------------------------------------------------------------------------------
	// update events (mouse)
	updateEvents(events: OEvents): void {
console.log (this + " update events " + events.watchMouseDown + " " + events.watchMouseUp + " " + events.watchMouseEnter + " " + events.watchMouseLeave);
	}

	//------------------------------------------------------------------------------------
	// update effects
	updateEffects(effect: OEffect): void {
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
		elt.style.boxShadow = "0px 0px";
		elt.style.filter = `blur(${val}px)`;
	}
	setShadow(elt: HTMLElement, val: OShadow): void {
		elt.setAttribute("filter", `drop-shadow(${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px)`);
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
	// called to update object size on model side
	updateObjectSize (objid : number) : void {
		let obj = INScore.objects().create(objid);
		let div = this.getElement();
		obj.updateWidth  (this.scene2RelativeWidth  (div.offsetWidth)); 
		obj.updateHeight (this.scene2RelativeHeight (div.offsetHeight)); 
		INScore.objects().del (obj);		
	}

	updateObjectSizeSync (obj: INScoreObject, w: number, h: number) : void {
		obj.updateWidth  (this.scene2RelativeWidth  (w)); 
		obj.updateHeight (this.scene2RelativeHeight (h)); 
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
	static updateObjectView (id : number, oid : number, forcepos=false)	: void { 
    	let view = JSObjectView.fObjects[id];
    	if (view) {
	    	let obj = INScore.objects().create(oid);
			view.updateView (obj, oid, forcepos); 
    		INScore.objects().del (obj);
    	}
    }

    static getVObject (id : number)		: JSObjectView	{ return JSObjectView.fObjects[id]; }
}
