
///<reference path="../libINScore.d.ts"/>
///<reference path="inscore.ts"/>


//----------------------------------------------------------------------------
class JSObjectView {

	private static fGlobalID = 0;
	private static fObjects = new Array<JSObjectView>();
	private fID = 0;
	private fElement : HTMLElement;
	private fParent  : JSObjectView;

    constructor(elt: HTMLElement, parent: JSObjectView, absolute=true) { 
		this.fID = ++JSObjectView.fGlobalID; 	// create a unique identifier
    	JSObjectView.fObjects[this.fID] = this; 	// store the div using its id
    	this.fParent = parent; 
		this.fElement = elt; 
		if (parent) parent.getElement().appendChild (elt);
		if (absolute) elt.style.position = "absolute";
	}
	
	toString() : string				{ return "JSObjectView"; }
	getElement() : HTMLElement		{ return this.fElement; }
	getParent() : JSObjectView		{ return this.fParent; }
	parentWidth() : number			{ return this.getParent().getElement().clientWidth; }
	parentHeight() : number			{ return this.getParent().getElement().clientHeight; }

    getId() : number	 				{ return this.fID; }
	colorTarget() : HTMLElement			{ return this.fElement; }
	posTarget() : HTMLElement			{ return this.fElement; }
	updateSpecial(obj: INScoreObject, oid: number)	: boolean { return true; }

	updateView(obj: INScoreObject, oid: number) : void {
console.log("JSObjectView::updateView : " + this + " id: " + this.fID );
		let infos = obj.getUpdateInfos();
		if (infos.newdata)
			if (!this.updateSpecial (obj, oid)) return;
		if ( infos.updatepos) 
			this.updatePosition(infos.position, this.posTarget());
		if ( infos.updatecolor) 
			this.updateColor(infos.color, this.colorTarget());
		// this.updatePenControl(obj);
		// this.updateEffects(obj);
		// this.updateEvents(obj);
	}


	updateColor(color: OColor, elt: HTMLElement) : void {
		elt.style.color = color.rgb;
		elt.style.opacity = color.alpha.toString();
	}

	updatePosition(pos: OPosition, elt: HTMLElement) : void {
		elt.style.visibility = (pos.hidden) ? "hidden" : "inherit";
		elt.style.left 	= this.relative2SceneX(pos.x).toString() + "px";
		elt.style.top  	= this.relative2SceneY(pos.y).toString() + "px";
	console.log("JSObjectView::updatePosition " + this + " left: " + elt.style.left + " x: " + pos.x );
		elt.style.zIndex = pos.zorder.toString();
		this.updateDimensions (pos, elt);
	}

	updateDimensions(pos: OPosition, elt: HTMLElement) : void {
		elt.style.width = this.relative2SceneWidth(pos.width) + "px";
		elt.style.height = this.relative2SceneHeight(pos.height) + "px";
	}
	// updatePos(obj: IObject): void {
	// 	let pos = this.fPositionHandler();
	// 	if (pos.x == kNoPosition) {
	// 		this.getHtml().style.visibility = "hidden";
	// 		return;
	// 	}

	// 	let size = this.getSize(obj);
	// 	let z = obj.fPosition.getZOrder();
	// 	let left = this.relative2SceneX(pos.x);
	// 	let top = this.relative2SceneY(pos.y);
	// 	this.setPos(top, left, size.w, size.h);		// store the metrics
	// 	let shear = obj.fPosition.getShear();

	// 	let elt = this.getHtml();
	// 	elt.style.width = size.w + "px";
	// 	elt.style.height = size.h + "px";
	// 	elt.style.left = left + "px";
	// 	elt.style.top = top + "px";
	// 	elt.style.zIndex = z.toString();
	// 	elt.style.transform = this.getTransform(obj) + " skewX(" + shear[0] + "rad) skewY(" + shear[1] + "rad)";
	// 	elt.style.visibility = obj.fPosition.getVisible() ? "inherit" : "hidden";
	// }

	// parentWidth() : number				{ return this.fParent ? this.fParent.clientWidth : document.body.clientWidth; }
	// parentHeight() : number				{ return this.fParent ? this.fParent.clientHeight : document.body.clientHeight; }

	relative2SceneY(y : number)  : number			{ return this.parentHeight() * (y + 1.0) / 2.0; }
	relative2SceneX(x : number)  : number			{ return this.parentWidth() * (x + 1.0) / 2.0; }
	relative2SceneWidth(width : number)  : number	{ return Math.min(this.parentWidth(), this.parentHeight()) * width / 2.0; }
	relative2SceneHeight(height : number) : number	{ return Math.min(this.parentWidth(), this.parentHeight()) * height / 2.0; }
	scene2RelativeWidth(width : number)	 : number	{ return (width * 2.0) / this.parentWidth(); }
	scene2RelativeHeight(height : number) : number	{ return (height * 2.0) / this.parentHeight(); }
	scene2RelativeX(x : number)  : number			{ return x / (this.parentWidth() / 2.0) - 1; }
	scene2RelativeY(y : number)  : number			{ return y / (this.parentHeight() / 2.0) - 1; }

	updateObjectSize (objid : number) : void {
		let obj = INScore.objects().create(objid);
console.log("JSObjectView::updateObjectSize " + this + " " + this.getElement().clientWidth + " -> " + this.parentWidth());
		obj.updateWidth  (this.scene2RelativeWidth  (this.getElement().clientWidth)); 
		obj.updateHeight (this.scene2RelativeHeight (this.getElement().clientHeight)); 
		INScore.objects().del (obj);		
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
