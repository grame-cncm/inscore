///<reference path="../model/IObject.ts"/>

abstract class VObjectView {
    
	abstract updateView			( obj: IObject) 		: void;
	abstract updateObjectSize	( obj: IObject ) 		: void;

<<<<<<< HEAD
    
    constructor(obj: IObject, scene: HTMLDivElement, motherScene?: HTMLDivElement) {
        this.fObject = obj;
        this.fScene = scene; 
        this.fMotherScene = scene;
        
        // Si ce n'est pas une scene, on renseigne la scene mère
        if (motherScene) { this.fMotherScene = motherScene; }       
    }
    
    getScene(): HTMLDivElement { return this.fScene }   
    getMotherScene(): HTMLDivElement { return this.fMotherScene }
    
    
    
    updateView(): void {
        if (!this.fScene.firstChild) return;
        var svg = this.fScene.firstElementChild.firstElementChild;
        var obj = this.fObject;
        
        switch (svg.nodeName) {
            case 'ellipse':
                //svg.setAttribute('cx', obj.getPos().getXPos()+'');
                //svg.setAttribute('cy', obj.getPos().getYPos()+'');
                //svg.setAttribute('rx', obj.getPos().getWidth()+'');
                //svg.setAttribute('ry', obj.getPos().getHeight()+'');     
                break;
                
            case 'rect':
                //svg.setAttribute('x', obj.getPos().getXPos()+'');
                //svg.setAttribute('y', obj.getPos().getYPos()+'');
                //svg.setAttribute('height', obj.getPos().getWidth()+'');
                //svg.setAttribute('width', obj.getPos().getHeight()+'');
                break;
                
            case 'curve':
                //svg.setAttribute('d', 'M50,10 q50,10 50,200 t50,100');
                //svg.setAttribute('stroke', '#1F56D2');
                break;
                
            case 'line':
                //svg.setAttribute('x1', '10');
                //svg.setAttribute('y1', '10');
                //svg.setAttribute('x2', '100');
                //svg.setAttribute('y2', '100');
                //svg.setAttribute('stroke', '#1F56D2')   
                break;            
        
            default:
                break;
        }
        
        svg.setAttribute('style', "fill:rgba(" + obj.getColor().getR() + ', ' 
                                                        + obj.getColor().getG() + ', ' 
                                                        + obj.getColor().getB() + ', '
                                                        + obj.getColor().getA() + ")");
=======
	// Maps the IObject [-1,1] y coordinate to the referenceRect().
	abstract relative2SceneY(y: number, item: any ) : number;
>>>>>>> origin/arnaud

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
