///<reference path="IObject.ts"/>

class ICurve extends IObject {
    
    protected kCurveType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kCurveType = 'curve';
        this.fTypeString = this.kCurveType;
    }
}