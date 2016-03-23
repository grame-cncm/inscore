///<reference path="IRectShape.ts"/>

class IRect extends IRectShape {
    
    protected kRectType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kRectType = 'rect';
        this.fTypeString = this.kRectType;      
    }

    static create(name: string, parent: IObject): IRect { return new IRect(name, parent); }
}