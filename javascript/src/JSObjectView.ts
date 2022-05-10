
///<reference path="lib/libINScore.d.ts"/>
///<reference path="AudioObject.ts"/>
///<reference path="inscore.ts"/>
///<reference path="interfaces.ts"/>


interface Point {
	x: number;
	y: number;
}

// events types
const kMouseEnterID 	= 1;
const kMouseLeaveID 	= 2;
const kMouseDownID  	= 3;
const kMouseUpID    	= 4;
const kMouseMoveID  	= 5;
const kMouseDClickID	= 6;

//----------------------------------------------------------------------------
abstract class JSObjectView {

	private static fGlobalID = 0;
	private static fObjects = new Array<JSObjectView>();
	private fID = 0;
	private fElement : HTMLElement;
	private fParent  : JSObjectView;
	private fSyncManager : GraphicSyncManager;
	private fIObject : number;			// a pointer to the IObject (used with sync management)
	private fOrigin : Point;

    constructor(elt: HTMLElement, parent: JSObjectView, absolute=true) { 
		this.fID = ++JSObjectView.fGlobalID; 		// create a unique identifier
    	JSObjectView.fObjects[this.fID] = this; 	// store the div using its id
    	this.fParent = parent; 
		this.fElement = elt; 
		this.fSyncManager = null;
		this.fIObject = null;
		this.fOrigin = { x: 0, y: 0};
		if (parent) parent.getElement().appendChild (elt);
		if (absolute) elt.style.position = "absolute";
	}

	abstract clone (parent: JSObjectView) : JSObjectView;
	static getObjectView(id: number) : JSObjectView		{ return JSObjectView.fObjects[id]; }

	setSyncManager(sync: GraphicSyncManager) : void { this.fSyncManager = sync; }
	setIObject(id: number) : void   { this.fIObject = id; }
	getIObject() : number   		{ return this.fIObject; }
	toString() : string				{ return "JSObjectView"; }
	getId() : number	 			{ return this.fID; }
	getElement() : HTMLElement		{ return this.fElement; }
	getParent() : JSObjectView		{ return this.fParent; }
	delete() : void { 
		if (this.fSyncManager) this.fSyncManager.clean();
		let parent = this.getElement().parentNode; // parent could be deleted
		if (parent) parent.removeChild (this.getElement());
		JSObjectView.fObjects[this.fID] = null; 
	}
	toAudioObject() : AudioObject { return null; }

	parentWidth() : number			{ 
		let elt = this.getElement().parentElement;
		return Math.min(elt.clientWidth, elt.clientHeight); 
	}
	parentHeight() : number			{ 
		let elt = this.getElement().parentElement;
		return Math.min(elt.clientWidth, elt.clientHeight); 
	}
	
	updateSpecial(obj: INScoreObject /*, oid: number*/)	: boolean { return true; }
	updateSpecific(obj: INScoreObject)	: void { }

	// the scale applied to preserve proportional rendering regarding scene size
	parentScale() : number { 
		let parent = this.getParent();
		let pscale = parent ? parent.parentScale() : 1;
		return pscale;
	}
	getScale(scale: number) : number {  return scale * this.parentScale(); }
	
	// the ratio applied in synchronisation mode to preserve the slave proportions
	parentSyncRatio()	: number { 
		let div = this.getElement();
		if (div && div.parentElement)
			return Math.min(div.clientWidth, div.offsetHeight) / Math.min(div.parentElement.offsetWidth, div.parentElement.offsetHeight);
		return 1;
	}
	getSyncRatio()	: number {  return this.getParent().parentSyncRatio(); }


	//---------------------------------------------------------------------
	// synchronous initialisation method - must be overriden by subclasses
	//---------------------------------------------------------------------
	initView (obj: INScoreObject) : boolean { return true; }

	//---------------------------------------------------------------------
	// update methods
	//---------------------------------------------------------------------
	updateView(obj: INScoreObject, /*oid: number,*/ master: number, force: boolean, keepRatio = false) : void {
		if (obj.deleted()) { this.delete(); return; }

		if (this.fSyncManager && this.fSyncManager.updateSync (obj))
			return;			// object is synchronized, update is done

		if (obj.newData()) 
			if (!this.updateSpecial (obj /*, oid*/)) return;

		let infos = obj.getUpdateInfos(master);
		if (keepRatio) {
			let r = this.getSyncRatio();
			infos.position.scale /= r;
		}

		if (infos.newclass) {
			this.getElement().className = infos.classNames;	
			force = true;
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
		if (infos.updateevents || force)
			this.updateEvents(infos.events, obj.getOSCAddress());
		if (infos.showmap) 
			console.log (this + " show map -> " + obj.getMaps().size());
	}


	updateColor(color: OColor) : void {
		this.fElement.style.color = color.rgb;
		this.fElement.style.opacity = color.alpha.toString();
	}

	updatePenControl(brush: OPen) : void {
		let elt = this.getElement();
		elt.style.border = `${brush.penWidth}px ${JSObjectView.penStyle2Css(brush.penStyle)} ${brush.penColor}`;
	}

	getOrigin() : Point { 
		let div = this.getElement();
		return { x: div.offsetWidth/2, y: div.offsetHeight/2 };
	}

	getPos(pos: OPosition) : Point {
		let ppos = this.getParent().getOrigin();
		let scale = this.getScale(pos.scale);
		let div = this.getElement();
		let x = ppos.x + this.relative2SceneWidth (pos.x) - (div.offsetWidth * (1 + pos.xorigin * scale) / 2 );
		let y = ppos.y + this.relative2SceneHeight(pos.y) - (div.offsetHeight * (1 + pos.yorigin * scale) / 2 );
		this.fOrigin.x = pos.xorigin;
		this.fOrigin.y = pos.yorigin;
		return { x: x, y: y};
	}

	updatePosition(pos: OPosition, elt: HTMLElement) : void {
		elt.style.visibility = (pos.hidden) ? "hidden" : "inherit";
		elt.style.transform = this.getTransform (pos);
		this.updateDimensions (pos);
		if (pos.x > 90000) { // synchronized object is out of master time
			elt.style.visibility = "hidden";
		}
		else {
			let p = this.getPos (pos);
			elt.style.left 	= p.x + "px";
			elt.style.top  	= p.y + "px";
		}
		elt.style.zIndex = pos.zorder.toString();
	}

	getTransform(pos: OPosition) : string {
		let transform = "";
		let scale = this.getScale(pos.scale);
		if (scale != 1)  transform += `scale(${scale},${scale}) `;
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
	// mouse events handlers and update
	getPoints(event: MouseEvent): { relative: Point, obj: Point, scene: Point} {
		let div = this.getElement();
		let relx = event.offsetX / div.clientWidth;
		let rely = event.offsetY / div.clientHeight;
		let x = 0.5 + (0.5 * this.fOrigin.x) - relx;
		if (x < 0) x = -x;		// make sure the position is the relative distance to the origin
		let y = 0.5 + (0.5 * this.fOrigin.y) - rely;
		if (y < 0) y = -y;		// make sure the position is the relative distance to the origin
		let pdiv = div.parentElement;
		let r = pdiv.getBoundingClientRect();
		let sx = ((event.clientX - r.left) / pdiv.clientWidth * 2) -1 ;
		let sy = ((event.clientY - r.top) / pdiv.clientHeight * 2) -1 ;
		return { relative: {x: x, y: y}, obj: {x: relx, y: rely}, scene: {x: sx, y: sy}} ;
	}

	accept(event: MouseEvent, id: number): boolean {
		if (id == kMouseLeaveID) return true;
		let div = this.getElement();
		return (event.offsetX >= 0) && (event.offsetY >= 0) && (event.offsetX <= div.clientWidth) && (event.offsetY <= div.clientHeight);
	}

	notify(event: MouseEvent, id: number, dest: string): void {
		event.stopImmediatePropagation();
		event.stopPropagation();
		event.preventDefault();

		if (!this.accept(event, id)) return;
		if ((id == kMouseMoveID) && (event.buttons != 1)) return;	// ignore move event without mouse button
		let mevent = null;
		switch (id) {
			case kMouseEnterID:	 mevent = "mouseEnter"; break;
			case kMouseLeaveID:  mevent = "mouseLeave"; break;
			case kMouseDownID: 	 mevent = "mouseDown"; break;
			case kMouseUpID:	 mevent = "mouseUp"; break;
			case kMouseMoveID: 	 mevent = "mouseMove"; break;
			case kMouseDClickID: mevent = "doubleClick"; break;
			default: return;  // unexpected event
		}

		let msg = inscore.newMessageM ("event");
		inscore.msgAddStr (msg, mevent);
		let p = this.getPoints (event);
		inscore.msgAddF (msg, p.relative.x)
		inscore.msgAddF (msg, p.relative.y)
		inscore.msgAddF (msg, p.obj.x)
		inscore.msgAddF (msg, p.obj.y)
		inscore.msgAddF (msg, p.scene.x)
		inscore.msgAddF (msg, p.scene.y)
		inscore.postMessage (dest, msg);
	}

	private defaultEvent (event : MouseEvent) { event.preventDefault(); event.stopImmediatePropagation(); };
	private initEvents (dest: string) { 
		this.updateEvents ( {
			watchMouseEnter : false,
			watchMouseLeave : false,
			watchMouseMove   : false,
			watchMouseDown   : false,
			watchMouseUp     : false,
			watchMouseDClick : false
		}, dest);
	};

	updateEvents(events: OEvents, dest: string): void {
		let div = this.getElement();
		if (events.watchMouseEnter) div.onmouseenter = (event : MouseEvent) : void => { this.notify(event, kMouseEnterID, dest); };
		else div.onmouseenter = (event : MouseEvent) : void => this.defaultEvent(event);

		if (events.watchMouseLeave) div.onmouseleave = (event : MouseEvent) : void => { this.notify(event, kMouseLeaveID, dest); };
		else div.onmouseleave = (event : MouseEvent) : void => this.defaultEvent(event);

		if (events.watchMouseDown) 	div.onmousedown = (event : MouseEvent) : void => { this.notify(event, kMouseDownID, dest); };
		else div.onmousedown = (event : MouseEvent) : void => this.defaultEvent(event);

		if (events.watchMouseUp) 	div.onmouseup = (event : MouseEvent) : void => { this.notify(event, kMouseUpID, dest); };
		else div.onmouseup  = (event : MouseEvent) : void => this.defaultEvent(event);

		if (events.watchMouseMove) 	div.onmousemove = (event : MouseEvent) : void => { this.notify(event, kMouseMoveID, dest); };
		else div.onmousemove  = (event : MouseEvent) : void => this.defaultEvent(event);

		if (events.watchMouseDClick) div.ondblclick = (event : MouseEvent) : void => { this.notify(event, kMouseDClickID, dest); };
		else div.ondblclick = (event : MouseEvent) : void => this.defaultEvent(event);
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
	// updateObjectSize (objid : number, w: number, h: number) : void {
	// 	let obj = INScore.objects().create(objid);
	// 	this.updateObjectSizeSync (obj, w, h);
	// 	INScore.objects().del (obj);		
	// }

	updateObjectSize (obj: INScoreObject, w: number, h: number) : void {
		// obj.updateWidth  (this.scene2RelativeWidth  (w)); 
		// obj.updateHeight (this.scene2RelativeHeight (h)); 
		obj.setSize (this.scene2RelativeWidth(w), this.scene2RelativeHeight(h));
		let div = this.getElement();
		obj.updateViewBoundingRect (div.clientLeft, div.clientTop, w, h);
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
	// Main update method
	// id  : the view id 
	// optr : the IObject id (actually a pointer stored as number)
	// forcepos : used to enforce updatePosition
	static updateObjectView (id : number, optr : number, forcepos: boolean)	: void { 
    	let view = JSObjectView.fObjects[id];
    	if (view) {
			view.setIObject (optr);
			try {
				let obj = INScore.objects().adapter(optr);
				view.updateView (obj, 0, forcepos); 
			}
			catch (error) {
				console.error (error);
			}
    	}
    }
 
	//---------------------------------------------------------------------
	// Synchronous init method
	// id  : the view id 
	// optr : the IObject id (actually a pointer stored as number)
	static initObjectView (id : number, optr : number)	: void { 
    	let view = JSObjectView.fObjects[id];
    	if (view) {
			view.setIObject (optr);
			try {
				let obj = INScore.objects().adapter(optr);
				view.initView (obj); 
			}
			catch (error) {
				console.error (error);
			}
    	}
    }

    static getVObject (id : number)		: JSObjectView	{ return JSObjectView.fObjects[id]; }
}
