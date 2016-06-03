///<reference path="IRectShape.ts"/>

class IRect extends IRectShape {
    
    //protected kRectType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        //this.kRectType = 'rect';
        this.fTypeString = kRectType;      
    } 
}