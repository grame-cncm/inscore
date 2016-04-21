///<reference path="../model/IObject.ts"/>

abstract class VObjectView {
    
    protected fMotherScene: HTMLDivElement;
    protected fObject: IObject;
    protected fScene: HTMLDivElement;

    
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

        this.fObject.setState(state.kClean);      
    }
    
    updateObjectSize(object: IObject): void {}
		
    setParentItem(parent: VObjectView) {}
    
   


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
