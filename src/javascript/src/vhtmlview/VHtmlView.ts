///<reference path="../model/IObject.ts"/>
///<reference path="../view/VObjectView.ts"/>

class VHtmlView extends VObjectView {
    protected fHtmlElt : HTMLElement;
    protected fParent  : VHtmlView;
    
    fTop: number;	fLeft: number;
    fWidth: number; fHeight: number;

    constructor(elt: HTMLElement, parent?: VHtmlView)  { 
    	super();
    	this.fParent = parent;
    	this.setPos(0, 0, 100, 100);
    	this.fHtmlElt = elt; 
    	if (parent) parent.getHtml().appendChild (elt);
   }

	getParent() : VObjectView 			{ return this.fParent; }
	getHtml() : HTMLElement 			{ return this.fHtmlElt; }
	// nominal scale is implemented at scene view level
	nominalScale() : number 			{ return 1 * this.fParent.nominalScale(); }

	remove() : void 					{ this.fHtmlElt.parentNode.removeChild(this.fHtmlElt); }

	updateView	( obj: IObject) : void {
		this.updatePos	(obj);
		this.updateColor(obj);
		this.updatePenControl (obj);
	}

	// target of color style depend on the html element implementation 
	colorTarget(): HTMLElement { return this.fHtmlElt; }
	updateColor (obj: IObject): void {
        if (obj.fColor.modified()) {
	        let elt = this.colorTarget();
	        elt.style.color = obj.fColor.getRGBString();
	        let alpha =  obj.fColor.getA() / 255;
	        elt.style.opacity = alpha.toString();
	    }
	}

	// getScale is intended to catch the div using auto height and width (like text, html...)
	getScale (obj: IObject): number 	{ return obj.fPosition.getScale();  }
	// getScale is intended to divs using auto height and width (like text, html...)
	autoScale (obj: IObject): number 	{ return obj.getRScale() * obj.getParent().getRSizeAsScale() * this.nominalScale(); }

	updatePenControl (obj: IObject) {
		let penWidth = obj.fPenControl.getPenWidth();
		let penColor = obj.fPenControl.fPenColor.getRGBString();
		let penStyle = obj.fPenControl.getPenStyle();
		let penAlpha = obj.fPenControl.getAlphaString();
    	
		let elt = this.getHtml();
		elt.style.borderWidth = penWidth + 'px'; 
		elt.style.borderColor = penColor;
		elt.style.borderStyle = penStyle;
		elt.style.borderColor = penAlpha;
	}

	updatePos (obj: IObject): void {
		let pos 	 = obj.getPosition();
		let size 	 = obj.getSize();
		let scale 	 = this.getScale(obj);
		let penWidth = obj.fPenControl.getPenWidth() ? obj.fPenControl.getPenWidth() : 0;
		let z	     = obj.fPosition.getZOrder();
        let w   	 = this.relative2SceneWidth (size.w) * scale + penWidth;
        let h 		 = this.relative2SceneHeight(size.h) * scale + penWidth;
        let left  	 = this.relative2SceneX(pos.x) - w/2.0 - (w * obj.fPosition.getXOrigin() / 2.0);
        let top 	 = this.relative2SceneY(pos.y) - h/2.0 - (h * obj.fPosition.getYOrigin() / 2.0);

        console.log("VHtmlView updatePos pos xy : " + pos.x + ", " + pos.y + " size hw : " + size.h + ", " + size.w +
		" penWindth " + penWidth + " wh : " + w + ", " + h + " left top " + left + ", " + top);

    	let elt = this.getHtml();
        elt.style.width  = (w ? w : 1) + "px";
        elt.style.height = (h ? h : 1) + "px";
        elt.style.left   =  left + "px";
        elt.style.top 	 =  top  + "px";
        elt.style.zIndex =  z.toString();
		elt.style.transform  = this.getTransform(obj);
        elt.style.visibility = obj.fPosition.getVisible() ? "inherit" : "hidden";
        this.setPos( top, left, w, h);
	}

	// to be used for elts with auto width and height
	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fHtmlElt.clientWidth);
        let h = this.scene2RelativeHeight(this.fHtmlElt.clientHeight);

		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
    }

	getTransform (obj: IObject): string {
		let rotate = obj.getRotate();
        return `rotate(${rotate.z}deg)`;
	}

	setPos (top: number,	left: number, width: number, height: number): void {
    	this.fTop = top;
    	this.fLeft = left;
    	this.fWidth = width;
    	this.fHeight = height;
	}
	
	positionString() : string { return `top: ${this.fTop} left: ${this.fLeft} w: ${this.fWidth} h: ${this.fHeight}`; }

	// Maps the IObject [-1,1] y coordinate to the referenceRect().
	relative2SceneY(y: number) : number 			{ return this.fParent.fHeight * (y+1.0) / 2.0; }

	// Maps the IObject [-1,1] x coordinate to the referenceRect().
	relative2SceneX(x: number) : number				{ return this.fParent.fWidth * (x+1.0) / 2.0; }

	// Maps the IObject [0,2] width value to the corresponding referenceRect() value.
	relative2SceneWidth(width: number) : number		{ return this.fParent.fWidth * width / 2.0; }

	// Maps the IObject [0,2] height value to the corresponding referenceRect() value.
	relative2SceneHeight(height: number) : number	{ return this.fParent.fHeight * height / 2.0; }

	// Maps the referenceRect() width value to the corresponding [0,2] value.
	scene2RelativeWidth(width: number) : number		{ return (width * 2.0) / this.fParent.fWidth; }

	// Maps the referenceRect() height value to the corresponding [0,2] value.
	scene2RelativeHeight(height: number) : number	{ return (height * 2.0) / this.fParent.fHeight; }

	// Maps the referenceRect() x value to the corresponding [-1,1] value.
	scene2RelativeX(x: number) : number				{ return x / (this.fParent.fWidth / 2.0) - 1; }

	// Maps the referenceRect() y value to the corresponding [-1,1] value.
	scene2RelativeY(y: number) : number				{ return y / (this.fParent.fHeight / 2.0) - 1; }

	// updates the local mapping (do nothing at IObject level) 
//	updateLocalMapping (obj: IObject ): void;
		
	// initialize an object view (do nothing at IObject level)
	initialize (obj: IObject ): void  {}
}
