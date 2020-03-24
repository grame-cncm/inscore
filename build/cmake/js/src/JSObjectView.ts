
///<reference path="../libINScore.d.ts"/>
///<reference path="inscore.ts"/>


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
		return Math.min(elt.clientWidth, elt.clientHeight); 
	}
	parentHeight() : number			{ 
		let elt = this.getElement().parentElement;
		return Math.min(elt.clientWidth, elt.clientHeight); 
	}
	parentPos() : {x: number, y: number} { 
		if (!this.getParent() || this.getParent().absolutePos())
			return { x: 0, y: 0 };
		let r = this.getElement().parentElement.getBoundingClientRect();
		let width = r.right - r.left;
		let height = r.bottom - r.top;
		let offset = (width - height) / 2;
		return  (width > height) ? { x: r.left + offset, y: r.top } : { x: r.left, y: r.top - offset };
	}
	posTarget() : HTMLElement		{ return this.fElement; }
	
	updateSpecial(obj: INScoreObject, oid: number)	: boolean { return true; }
	updateSpecific(obj: INScoreObject)	: void { }

	updateView(obj: INScoreObject, oid: number) : void {
// console.log("JSObjectView::updateView : " + this + " id: " + this.fID );
		let infos = obj.getUpdateInfos();
		if (infos.deleted  && this.getElement().parentNode) { // parent could be deleted
			this.getElement().parentNode.removeChild(this.getElement());
			return;
		}

		if (infos.newdata) {
			if (!this.updateSpecial (obj, oid)) return;
			else infos.updatepos = true;
		}
		if ( infos.updatecolor) 
			this.updateColor(infos.color);
		if (infos.updatebrush)
			this.updatePenControl(infos.brush);
		this.updateSpecific (obj);
		if (infos.updatepos || infos.updatebrush)
			this.updatePosition(infos.position, this.posTarget());
		// this.updateEffects(obj);
		// this.updateEvents(obj);
	}


	updateColor(color: OColor) : void {
		this.fElement.style.color = color.rgb;
		this.fElement.style.opacity = color.alpha.toString();
	}

	updatePenControl(brush: OBrush) : void {
		let elt = this.getElement();
		elt.style.borderWidth = brush.penWidth + 'px';
		elt.style.borderColor = brush.penColor;
		elt.style.borderStyle = JSObjectView.penStyle2Css (brush.penStyle);
	}

	updatePosition(pos: OPosition, elt: HTMLElement) : void {
		elt.style.visibility = (pos.hidden) ? "hidden" : "inherit";
		let ppos = this.parentPos();
		let x = ppos.x + this.relative2SceneX(pos.x);
		let y = ppos.y + this.relative2SceneY(pos.y);
		let offset = this.getOriginOffset (pos.xorigin, pos.yorigin);
		elt.style.left 	= (x - offset.ox).toString() + "px";
		elt.style.top  	= (y - offset.oy).toString() + "px";
		elt.style.zIndex = pos.zorder.toString();
		this.updateDimensions (pos);
	}

	updateDimensions(pos: OPosition) : void {
		let elt = this.getElement();
		elt.style.width = this.relative2SceneWidth(pos.width) + "px";
		elt.style.height = this.relative2SceneHeight(pos.height) + "px";
	}

	getOriginOffset(xo : number, yo: number)  : {ox: number, oy: number} { 
		let r = this.getElement().getBoundingClientRect();
		let w = (r.right - r.left);
		let h = (r.bottom - r.top);
		return { ox: w * (xo + 1) / 2, oy: h * (yo + 1) / 2 }; 
	}

	relative2SceneX(x : number)  : number			{ return this.parentWidth() * (x + 1.0) / 2.0; }
	relative2SceneY(y : number)  : number			{ return this.parentHeight() * (y + 1.0) / 2.0; }
	relative2SceneWidth(width : number)  : number	{ return Math.min(this.parentWidth(), this.parentHeight()) * width / 2.0; }
	relative2SceneHeight(height : number) : number	{ return Math.min(this.parentWidth(), this.parentHeight()) * height / 2.0; }
	scene2RelativeWidth(width : number)	 : number	{ return (width * 2.0) / this.parentWidth(); }
	scene2RelativeHeight(height : number) : number	{ return (height * 2.0) / this.parentHeight(); }
	scene2RelativeX(x : number)  : number			{ return x / (this.parentWidth() / 2.0) - 1; }
	scene2RelativeY(y : number)  : number			{ return y / (this.parentHeight() / 2.0) - 1; }

	updateObjectSize (objid : number) : void {
		let obj = INScore.objects().create(objid);
// console.log("JSObjectView::updateObjectSize " + this + " " + this.getElement().clientWidth + " -> " + this.parentWidth());
		obj.updateWidth  (this.scene2RelativeWidth  (this.getElement().clientWidth)); 
		obj.updateHeight (this.scene2RelativeHeight (this.getElement().clientHeight)); 
		INScore.objects().del (obj);		
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

    static getVObject (id : number)	: JSObjectView	{ return JSObjectView.fObjects[id]; }
    static updateObjectView (id : number, oid : number)	: void { 
    	let view = JSObjectView.fObjects[id];
    	if (view) {
	    	let obj = INScore.objects().create(oid);
    		view.updateView (obj, oid); 
    		INScore.objects().del (obj);
    	}
    }
}
