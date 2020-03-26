
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
	parentPos() : {x: number, y: number} { 
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

	//---------------------------------------------------------------------
	// update methods
	//---------------------------------------------------------------------
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
			this.updatePosition(infos.position, infos.brush.penWidth, this.posTarget());
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

	getPos(pos: OPosition, strokewidth: number) : Point {
		let ppos = this.parentPos();
		// let w = this.relative2SceneWidth (pos.width * (1 + pos.xorigin * pos.scale) / 2 );
		// let h = this.relative2SceneHeight(pos.height * (1 + pos.yorigin * pos.scale) / 2 );
		let x = ppos.x + this.relative2SceneWidth (pos.x - (pos.width * (1 + pos.xorigin * pos.scale) / 2 ));
		let y = ppos.y + this.relative2SceneHeight(pos.y - (pos.height * (1 + pos.yorigin * pos.scale) / 2 ));
		return { x: x, y: y};
	}

	updatePosition(pos: OPosition, strokewidth: number, elt: HTMLElement) : void {
		elt.style.visibility = (pos.hidden) ? "hidden" : "inherit";
		// let ppos = this.parentPos();
		this.updateDimensions (pos, strokewidth);
		// this.debug(null, ppos.x, ppos.y, "black");
		// let x = ppos.x + this.relative2SceneWidth (pos.x - (pos.width / 2 * pos.scale));
		// let y = ppos.y + this.relative2SceneHeight(pos.y - (pos.height / 2 * pos.scale));
		// let x = ppos.x + this.relative2SceneWidth (pos.x - (pos.width * (1 - pos.xorigin) / 2 ));
		// let y = ppos.y + this.relative2SceneHeight(pos.y - (pos.height * (1 - pos.yorigin) / 2 ));
// let offset = this.getOriginOffset (pos.xorigin, pos.yorigin);
		// let offset = this.getTranslate (pos);
		// elt.style.left 	= (x - offset.x).toString() + "px";
		// elt.style.top  	= (y - offset.y).toString() + "px";
		let p = this.getPos (pos, strokewidth);
		elt.style.left 	= p.x + "px";
		elt.style.top  	= p.y + "px";
		elt.style.zIndex = pos.zorder.toString();
		elt.style.transform = this.getTransform (pos);
	}

	getTranslate (pos: OPosition) : {x: number, y: number} {
		// let w = this.getElement().offsetWidth;
		// let h = this.getElement().offsetHeight;
		let w = this.relative2SceneWidth (pos.width);
		let h = this.relative2SceneHeight(pos.height);
		// let offset = this.getOriginOffset (pos.xorigin, pos.yorigin);
		// return {x: w * pos.xorigin * pos.scale / 2, y: h * pos.yorigin * pos.scale / 2};
		return {x: w * pos.xorigin / 2, y: h * pos.yorigin / 2};
		// return (offset.x || offset.y) ? `translate(${-offset.x / pos.scale}px,${-offset.y / pos.scale}px) ` : "";
	}

	getTransform(pos: OPosition) : string {
		// let translate = this.getTranslate(pos);
		let transform = ""; //(translate.x || translate.y) ? `translate(${translate.x}px,${translate.y}px) ` : "";
		if (pos.scale != 1)  transform += `scale(${pos.scale},${pos.scale}) `;
		if (pos.xangle) transform += `rotateX(${pos.xangle}deg) `;
		if (pos.yangle) transform += `rotateY(${pos.yangle}deg) `;
		if (pos.zangle) transform += `rotateZ(${pos.zangle}deg) `;
		return transform;
	}

	updateDimensions(pos: OPosition, strokewidth: number) : void {
		let elt = this.getElement();
		elt.style.width = this.relative2SceneWidth(pos.width) + "px";
		elt.style.height = this.relative2SceneHeight(pos.height) + "px";
	}

	getOriginOffset(xo : number, yo: number)  : {x: number, y: number} { 
		let w = this.getElement().offsetWidth;
		let h = this.getElement().offsetHeight;
		return { x: -w * xo/2, y: -h * yo/2 }; 
	}

	relative2SceneX(x : number)  : number			{ return this.parentWidth() * (x + 1.0) / 2.0; }
	relative2SceneY(y : number)  : number			{ return this.parentHeight() * (y + 1.0) / 2.0; }
	relative2SceneWidth(width : number)  : number	{ return this.parentWidth() * width / 2.0; }
	relative2SceneHeight(height : number) : number	{ return this.parentHeight() * height / 2.0; }
	// relative2SceneWidth(width : number)  : number	{ return Math.min(this.parentWidth(), this.parentHeight()) * width / 2.0; }
	// relative2SceneHeight(height : number) : number	{ return Math.min(this.parentWidth(), this.parentHeight()) * height / 2.0; }
	scene2RelativeWidth(width : number)	 : number	{ return (width * 2.0) / this.parentWidth(); }
	scene2RelativeHeight(height : number) : number	{ return (height * 2.0) / this.parentHeight(); }
	scene2RelativeX(x : number)  : number			{ return x / (this.parentWidth() / 2.0) - 1; }
	scene2RelativeY(y : number)  : number			{ return y / (this.parentHeight() / 2.0) - 1; }

	updateObjectSize (objid : number) : void {
		let obj = INScore.objects().create(objid);
// console.log("JSObjectView::updateObjectSize " + this + " " + this.getElement().clientWidth + " -> " + this.parentWidth());
		let r = this.getElement().getBoundingClientRect();
		obj.updateWidth  (this.scene2RelativeWidth  (r.width)); 
		obj.updateHeight (this.scene2RelativeHeight (r.height)); 
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
