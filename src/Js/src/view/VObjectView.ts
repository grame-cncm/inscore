///<reference path="../model/IObject.ts"/>

abstract class VObjectView {
    
	abstract updateView			( obj: IObject) 		: void;
	abstract updateObjectSize	( obj: IObject ) 		: void;

	// Maps the IObject [-1,1] y coordinate to the referenceRect().
	abstract relative2SceneY(y: number, item: any ) : number;

	// \brief Maps the IObject [-1,1] x coordinate to the referenceRect().
	abstract relative2SceneX(x: number, item: any ) : number;

	// \brief Maps the IObject [0,2] width value to the corresponding referenceRect() value.
	abstract relative2SceneWidth(width: number, item: any ) : number;

	// \brief Maps the IObject [0,2] height value to the corresponding referenceRect() value.
	abstract relative2SceneHeight(height: number, item: any ) : number;

	// \brief Maps the referenceRect() width value to the corresponding [0,2] value.
	abstract scene2RelativeWidth(width: number, item: any ) : number;

	// \brief Maps the referenceRect() height value to the corresponding [0,2] value.
	abstract scene2RelativeHeight(height: number, item: any ) : number;

	// \brief Maps the referenceRect() x value to the corresponding [-1,1] value.
	abstract scene2RelativeX(x: number, item: any ) : number;

	// \brief Maps the referenceRect() y value to the corresponding [-1,1] value.
	abstract scene2RelativeY(y: number, item: any ) : number;

	// \brief updates the local mapping (do nothing at IObject level) 
//	abstract updateLocalMapping (obj: IObject ): void;
		
	// \brief initialize an object view (do nothing at IObject level)
	abstract initialize (obj: IObject ): void
}
