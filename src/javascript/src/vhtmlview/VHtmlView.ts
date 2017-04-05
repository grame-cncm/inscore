///<reference path="../lib/TTypes.ts"/>
///<reference path="../model/IObject.ts"/>
///<reference path="../view/VObjectView.ts"/>
///<reference path="../mapping/TTime2GraphicRelation.ts"/>

class VHtmlView extends VObjectView {
//	static fClickTarget: IObject;
	protected fHtmlElt: HTMLElement;
	protected fParent: VHtmlView;

	fTop: number; fLeft: number;
	fWidth: number; fHeight: number;
	fTranslateX: number; fTranslateY: number

	constructor(elt: HTMLElement, parent?: VHtmlView) {
		super();
		this.fParent = parent;
		this.setPos(0, 0, 100, 100);
		this.fHtmlElt = elt;
		this.fTranslateX = this.fTranslateY = 0;
//		VHtmlView.fClickTarget = null;
		if (parent) parent.getHtml().appendChild(elt);
		this.setDefaultPositionStyle();
	}

	setDefaultPositionStyle(): void { this.fHtmlElt.style.position = "absolute"; }
	getParent(): VObjectView { return this.fParent; }
	getHtml(): HTMLElement { return this.fHtmlElt; }
	remove(): void { this.fHtmlElt.parentNode.removeChild(this.fHtmlElt); }

	//------------------------------------------------------------------------------------
	updateView(obj: IObject): void {
		this.updatePos(obj);
		this.updateColor(obj);
		this.updatePenControl(obj);
		this.updateEffects(obj);
		this.updateEvents(obj);
		if (obj.fDebug.fShowName) 	this.showName (obj);
		if (obj.fDebug.fShowMap) 	this.showMap (obj);
	}
	
	//------------------------------------------------------------------------------------
	showName(obj: IObject): void {
		let div = document.createElement('div');
        div.className = "inscore-debug";
        div.innerHTML  = obj.getName();
        this.getHtml().appendChild (div);
	}

	//------------------------------------------------------------------------------------
	private addMap(seg: TGraphicSegment, i: number): void {
		let colors = [ "DarkOrange", "ForestGreen"];
		let x = this.fWidth * seg.first().first();
		let w = this.fWidth * seg.first().size();
		let y = this.fHeight * seg.second().first();
		let h = this.fHeight * seg.second().size();
		let div = document.createElement('div');
		div.style.position = "absolute";
		div.style.width = w +"px";
		div.style.height = h +"px";
		div.style.left = x + "px";
		div.style.top = y + "px";
		div.style.backgroundColor = colors[i%2];
		div.style.opacity = "0.4";
        this.getHtml().appendChild (div);
	}

	//------------------------------------------------------------------------------------
	showMap(obj: IObject): void {
		let color = [ "DarkOrange", "rgb(10 200 10)"];
		let map : Array<TTime2GraphicRelation> = obj.fMapping.getRelations();
		for (var i=0; i<map.length; i++)
			this.addMap (map[i].fGraph, i);
	}

	//------------------------------------------------------------------------------------
	mouseEvent (obj: IObject, type: eUIEvents, ev: MouseEvent) : any {
		ev.stopPropagation();

		let div = this.getHtml();
		let o = this.getRelativeCoord (ev, div);
		let x = o.x;
		let y = o.y;
		let rx = o.rx;
		let ry = o.ry;
		let p = this.getRelativeCoord (ev, div.parentElement);
		let sx = p.rx; //this.scene2RelativeX (x );
		let sy = p.ry; //this.scene2RelativeY (y);
		obj.handleMouseEvent (type, {x: rx, y: ry, ax: x, ay: y, sx: sx, sy: sy});
		
//		if (type == eUIEvents.kMouseDown)
//			console.log ("mouseEvent on " + obj.getName() + " => " + x + " " + y + " rel: " +rx + " " + ry + " srel: " + sx + " " + sy );
	}

	// get coordinates relative to an HTMLElement
	getRelativeCoord(ev : MouseEvent, elt: HTMLElement): {x: number, y: number, rx: number, ry: number} {
		let r = elt.getBoundingClientRect();
		let x = ev.pageX - (r.left + window.scrollX);
		let y = ev.pageY - (r.top + window.scrollY);
		return {x: x, y: y, rx: x / (r.width / 2) - 1, ry: y / (r.height / 2) - 1};
	}

	removeAllEvents(div: HTMLElement) : void {
		div.onmousedown = null; 
		div.onmouseup = null; 
		div.onmouseenter = null; 
		div.onmouseleave = null; 
		div.ondblclick = null; 
	}
	
	updateEvents(obj: IObject) : void {
		let evs = obj.hasUIEvents();
		let div = this.getHtml();
		if (evs) {
			if (evs & eUIEvents.kMouseDown)
				div.onmousedown = (ev: MouseEvent): any => { /*if (!VHtmlView.fClickTarget) VHtmlView.fClickTarget = obj;*/ return this.mouseEvent(obj, eUIEvents.kMouseDown, ev); }; 
			else div.onmousedown = null;

			if (evs & eUIEvents.kMouseMove) 
				div.onmousemove = (ev: MouseEvent): any => { return (ev.which == 1) /*&& (VHtmlView.fClickTarget == obj)*/ ? this.mouseEvent(obj, eUIEvents.kMouseMove, ev) : null; }
			else div.onmousemove = null;

			if (evs & eUIEvents.kMouseUp)
				div.onmouseup = (ev: MouseEvent): any => { /*VHtmlView.fClickTarget = null;*/ return this.mouseEvent(obj, eUIEvents.kMouseUp, ev); }; 
			else div.onmouseup = null;

			if (evs & eUIEvents.kMouseEnter)
				div.onmouseenter = (ev: MouseEvent): any => { return this.mouseEvent(obj, eUIEvents.kMouseEnter, ev); }; 
			else div.onmouseenter = null;

			if (evs & eUIEvents.kMouseLeave)
				div.onmouseleave = (ev: MouseEvent): any => { return this.mouseEvent(obj, eUIEvents.kMouseLeave, ev); }; 
			else div.onmouseleave = null;
		}
		else this.removeAllEvents (div); 
	}
	
	//------------------------------------------------------------------------------------
	// update color
	// target of color style depend on the html element implementation 
	colorTarget(): HTMLElement { return this.fHtmlElt; }
	updateColor(obj: IObject): void {
		if (obj.fColor.modified()) {
			let elt = this.colorTarget();
			elt.style.color = obj.fColor.getRGBString();
			let alpha = obj.fColor.getA() / 255;
			elt.style.opacity = alpha.toString();
		}
	}

	//------------------------------------------------------------------------------------
	// update pen
	updatePenControl(obj: IObject) {
		let penWidth = obj.fPenControl.getPenWidth();
		let penColor = obj.fPenControl.getPenColor().getRGBString();
		let penStyle = VHtmlView.penStyle2Dash(obj.fPenControl.getPenStyleNum());
		let penAlpha = obj.fPenControl.getPenColor().getA();

		let elt = this.getHtml();
		elt.style.borderWidth = penWidth + 'px';
		elt.style.borderColor = penColor;
		elt.style.borderStyle = penStyle;
	}

	//------------------------------------------------------------------------------------
	// update position
	getSize(obj: IObject): { w: number, h: number } {
		let size = obj.getSize();
		let strokeWidth = obj.fPenControl.getPenWidth();
		let w = this.relative2SceneWidth(size.w) + strokeWidth;
		let h = this.relative2SceneHeight(size.h) + strokeWidth;
		return { w: (w ? w : 1), h: (h ? h : 1) };
	}

	updatePos(obj: IObject): void {
		let pos = obj.getPosition();
		let size = this.getSize(obj);
		let z = obj.fPosition.getZOrder();
		let left = this.relative2SceneX(pos.x);
		let top = this.relative2SceneY(pos.y);
		this.setPos(top, left, size.w, size.h);		// store the metrics
		let shear = obj.fPosition.getShear();

		let elt = this.getHtml();
		elt.style.width = size.w + "px";
		elt.style.height = size.h + "px";
		elt.style.left = left + "px";
		elt.style.top = top + "px";
		elt.style.zIndex = z.toString();
		elt.style.transform = this.getTransform(obj) + " skewX(" + shear[0] + "rad) skewY(" + shear[1] + "rad)";
		elt.style.visibility = obj.fPosition.getVisible() ? "inherit" : "hidden";
	}

	// to be used for elts with auto width and height
	updateObjectSize(obj: IObject): void {
		let w = this.scene2RelativeWidth(this.fHtmlElt.clientWidth);
		let h = this.scene2RelativeHeight(this.fHtmlElt.clientHeight);
		obj.fPosition.setWidth(w);
		obj.fPosition.setHeight(h);
	}

	getParentsScale(obj: IObject): number {
		let p = obj.getParent();
		if (p) return p.fPosition.getScale() * this.getParentsScale(p);
		return 1;
	}
	getViewScale(obj: IObject): number { return obj.fPosition.getScale() * this.getParentsScale(obj); }

	getScale(obj: IObject): string {
		let scale = this.getViewScale(obj);
		return (scale == 1) ? "" : `scale(${scale},${scale}) `;
	}

	getTranslate(obj: IObject): string {
		let scale = obj.fPosition.getScale();
		let xo = obj.fPosition.getXOrigin() * scale;
		let yo = obj.fPosition.getYOrigin() * scale;
		this.fTranslateX = -this.fWidth * (1 + xo) / 2.0;
		this.fTranslateY = -this.fHeight * (1 + yo) / 2.0;
		return (this.fTranslateX || this.fTranslateY) ? `translate(${this.fTranslateX}px,${this.fTranslateY}px) ` : " ";
	}


	getRotateX(obj: IObject): string {
		let rotate = obj.getRotate();
		return (rotate.x) ? "rotateX(" + rotate.x + "deg)" : "";
	}

	getRotateY(obj: IObject): string {
		let rotate = obj.getRotate();
		return (rotate.y) ? "rotateY(" + rotate.y + "deg)" : "";
	}

	getRotateZ(obj: IObject): string {
		let rotate = obj.getRotate();
		return (rotate.z) ? `rotateZ(${rotate.z}deg) ` : "";
	}

	getTransform(obj: IObject): string {
		return this.getTranslate(obj) + this.getScale(obj) + this.getRotateX(obj) + this.getRotateY(obj) + this.getRotateZ(obj);
	}

	setPos(top: number, left: number, width: number, height: number): void {
		this.fTop = top;
		this.fLeft = left;
		this.fWidth = width;
		this.fHeight = height;
	}

	//------------------------------------------------------------------------------------
	// update effects
	updateEffects(obj: IObject): void {
		if (!obj.fEffect.fEffectModified) return;

		let elt = this.getHtml();
		switch (obj.fEffect.type()) {
			case eEffect.kNone: this.setNone();
				break;
			case eEffect.kBlur: this.setBlur(obj.fEffect.param(0));
				break;
			case eEffect.kShadow: this.setShadow(obj.fEffect.params());
				break;
		}
	}

	setNone(): void { this.setBlur(0); }
	setBlur(val: number): void {
		this.getHtml().style.boxShadow = "(0px 0px)";
		this.getHtml().style.filter = "blur( " + val + "px)";
	}

	setShadow(params: Array<number>): void {
		let color = new IColor(params.slice(2, 6));
		this.getHtml().style.boxShadow = color.getCSSRGBAString() + params[0] + "px " + params[1] + "px " + params[6] + "px";
		this.getHtml().style.filter = "blur(0)";
	}

	static penStyle2Dash(style: number): string {
		switch (style) {
			case 0: return "solid";
			case 1: return "dashed";
			case 2: return "dotted";
			default: return "solid";
		}
	}

	positionString(): string { return `top: ${this.fTop} left: ${this.fLeft} w: ${this.fWidth} h: ${this.fHeight}`; }

	// Maps the IObject [-1,1] y coordinate to the referenceRect().
	relative2SceneY(y: number): number { return this.fParent.fHeight * (y + 1.0) / 2.0; }

	// Maps the IObject [-1,1] x coordinate to the referenceRect().
	relative2SceneX(x: number): number { return this.fParent.fWidth * (x + 1.0) / 2.0; }

	// Maps the IObject [0,2] width value to the corresponding referenceRect() value.
	relative2SceneWidth(width: number): number { return Math.min(this.fParent.fWidth, this.fParent.fHeight) * width / 2.0; }

	// Maps the IObject [0,2] height value to the corresponding referenceRect() value.
	relative2SceneHeight(height: number): number { return Math.min(this.fParent.fWidth, this.fParent.fHeight) * height / 2.0; }

	// Maps the referenceRect() width value to the corresponding [0,2] value.
	scene2RelativeWidth(width: number): number { return (width * 2.0) / this.fParent.fWidth; }

	// Maps the referenceRect() height value to the corresponding [0,2] value.
	scene2RelativeHeight(height: number): number { return (height * 2.0) / this.fParent.fHeight; }

	// Maps the referenceRect() x value to the corresponding [-1,1] value.
	scene2RelativeX(x: number): number { return x / (this.fParent.fWidth / 2.0) - 1; }

	// Maps the referenceRect() y value to the corresponding [-1,1] value.
	scene2RelativeY(y: number): number { return y / (this.fParent.fHeight / 2.0) - 1; }

	// updates the local mapping (do nothing at IObject level) 
	//	updateLocalMapping (obj: IObject ): void;

	// initialize an object view (do nothing at IObject level)
	initialize(obj: IObject): void { }
}