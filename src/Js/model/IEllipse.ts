///<reference path="IRectShape.ts"/>

class IEllipse extends IRectShape {
    
    protected kEllipseType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kEllipseType = 'ellipse';
        this.fTypeString = this.kEllipseType;
    }

    static create(name: string, parent: IObject): IEllipse { return new IEllipse(name, parent); }
}