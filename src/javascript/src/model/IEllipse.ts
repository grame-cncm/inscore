///<reference path="IRectShape.ts"/>

class IEllipse extends IRectShape {
    
    //protected kEllipseType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        //this.kEllipseType = 'ellipse';
        this.fTypeString = kEllipseType;
    }
}