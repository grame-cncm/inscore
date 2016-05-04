///<reference path="../model/IObject.ts"/>
///<reference path="../view/VObjectView.ts"/>

class VHtmlView extends VObjectView {
    protected fDiv 	  : HTMLDivElement;
    protected fParent : VHtmlView;
    
    fTop: number;	fLeft: number;
    fWidth: number; fHeight: number;

    constructor(div: HTMLDivElement, parent?: VHtmlView)  { 
    	super();
    	this.fParent = parent;
    	this.setPos(0, 0, 100, 100);
    	this.fDiv = div; 
    	if (div) div.style.position = "absolute";
    }

	getParent() : VObjectView 					{ return this.fParent }
	getDiv() : HTMLDivElement 					{ return this.fDiv }

	updateView	( obj: IObject) : void {
		let pos = obj.getPosition();
    	this.fDiv.setAttribute ("x", pos.x.toString() + "px");
    	this.fDiv.setAttribute ("y", pos.y.toString() + "px");		
	}

	updateColor (obj: IObject): void {
        if (obj.fColor.modified())
	        this.fDiv.style.background = obj.fColor.getRGBString();
	}

	getScale (obj: IObject): number { return obj.fPosition.getScale();  }
	updatePos (obj: IObject): void {
		let pos 	= obj.getPosition();
		let size 	= obj.getSize();
		let scale 	= this.getScale(obj);
		let z		= obj.fPosition.getZOrder();
        let w  		= this.relative2SceneWidth (size.w)  * scale;
        let h 		= this.relative2SceneHeight (size.h) * scale;
        let left  	= this.relative2SceneX (pos.x) - w/2.0 - (w * obj.fPosition.getXOrigin() / 2.0);
        let top 	= this.relative2SceneY (pos.y) - h/2.0 - (h * obj.fPosition.getYOrigin() / 2.0);

    	let div = this.getDiv();
        div.style.width  = w.toString()+"px";
        div.style.height = h.toString()+"px";
        div.style.left 	=  left.toString() + "px";
        div.style.top 	=  top.toString() + "px";
        div.style.zIndex = z.toString();
		div.style.transform  = this.getTransform(obj);
        this.setPos( top, left, w, h);
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

	// basically do nothing, should be implemented in subclasses when necessary
	updateObjectSize	( obj: IObject ) : void		{} 

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
