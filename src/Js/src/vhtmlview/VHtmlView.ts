///<reference path="../view/VObjectView.ts"/>

class VHtmlView extends VObjectView {
    
    protected fDiv 	  : HTMLDivElement;
    protected fParent : VObjectView;
	protected getDiv() : HTMLDivElement 					{ return this.fDiv }

    constructor(div: HTMLDivElement, parent?: VObjectView)  { super(); this.fParent = parent; this.fDiv = div; }

	getParent() : VObjectView 								{ return this.fParent }

	updateView			( obj: IObject) : void {}

	// basically do nothing, should be implemented in subclasses when necessary
	updateObjectSize	( obj: IObject ) : void		{} 

	// Maps the IObject [-1,1] y coordinate to the referenceRect().
	relative2SceneY(y: number, item: any ) : number 			{ return 0; }

	// Maps the IObject [-1,1] x coordinate to the referenceRect().
	relative2SceneX(x: number, item: any ) : number				{ return 0; }

	// Maps the IObject [0,2] width value to the corresponding referenceRect() value.
	relative2SceneWidth(width: number, item: any ) : number		{ return 0; }

	// Maps the IObject [0,2] height value to the corresponding referenceRect() value.
	relative2SceneHeight(height: number, item: any ) : number	{ return 0; }

	// Maps the referenceRect() width value to the corresponding [0,2] value.
	scene2RelativeWidth(width: number, item: any ) : number		{ return 0; }

	// Maps the referenceRect() height value to the corresponding [0,2] value.
	scene2RelativeHeight(height: number, item: any ) : number	{ return 0; }

	// Maps the referenceRect() x value to the corresponding [-1,1] value.
	scene2RelativeX(x: number, item: any ) : number				{ return 0; }

	// Maps the referenceRect() y value to the corresponding [-1,1] value.
	scene2RelativeY(y: number, item: any ) : number				{ return 0; }

	// updates the local mapping (do nothing at IObject level) 
//	updateLocalMapping (obj: IObject ): void;
		
	// initialize an object view (do nothing at IObject level)
	initialize (obj: IObject ): void  {}
}
