///<reference path="IObject.ts"/>

abstract class VObjectView {
    
    protected fMotherScene: HTMLDivElement;
    protected fObject: IObject;
    protected fScene: HTMLDivElement;

    
    constructor(motherScene: HTMLDivElement, obj: IObject, scene: HTMLDivElement) {
        this.fMotherScene = motherScene;
        this.fObject = obj;
        this.fScene = scene;        
    }
    
    
    updateView(object: IObject): void {};
    updateObjectSize(object: IObject): void {};
		
    setParentItem(parent: VObjectView) {};
    
    getScene(): HTMLDivElement { return this.fScene }   
    getMotherScene(): HTMLDivElement { return this.fMotherScene }


    /*relative2SceneY(y: number, item:QGraphicsItem  = 0): number {return 0};	
    relative2SceneX(x: number, item:QGraphicsItem  = 0): number {return 0};
    relative2SceneWidth(width: number, item:QGraphicsItem  = 0): number {return 0};
    relative2SceneHeight(height: number, item:QGraphicsItem  = 0): number {return 0};

    scene2RelativeWidth(width: number, item:QGraphicsItem  = 0): number {return 0};
    scene2RelativeHeight(height: number, item:QGraphicsItem  = 0): number {return 0};
    scene2RelativeX(x: number, item:QGraphicsItem  = 0): number {return 0};
    scene2RelativeY(y: number, item:QGraphicsItem  = 0): number {return 0};
    */
}
