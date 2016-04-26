///<reference path="IRectShape.ts"/>

class IRect extends IRectShape {
    
    protected kRectType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kRectType = 'rect';
        this.fTypeString = this.kRectType;      
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