///<reference path="IRectShape.ts"/>

class IEllipse extends IRectShape {
    
    protected kEllipseType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kEllipseType = 'ellipse';
        this.fTypeString = this.kEllipseType;
    }
    
    msgSet(params: Array<any>) {
        if ( !params[2] || !params[3]) { 
            console.log('missing argument : rect need width & height');
            return false;
        }
        else { 
            this.fPosition.setWidth(params[2]);
            this.fPosition.setHeight(params[3]);
            return true;
        }
    } 
}