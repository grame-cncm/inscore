///<reference path="Methods.ts"/>
///<reference path="IRectShape.ts"/>

class IRect extends IRectShape {
    
    protected kRectType: string;
    protected fRadius: Array<number>  
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kRectType = 'rect';        
        this.fTypeString = this.kRectType;  
    
        this.fGetMsgHandlerMap[kradius_GetSetMethod] = new TGetMsgHandlerArray(this._getRadius());
        this.fMsgHandlerMap[kradius_GetSetMethod] 	 = new TMsgHandlerNumArray(this._setRadius());
    } 
    
    getRadius() : Array<number>             { return this.fRadius }
    setRadius(radius : Array<number>): eMsgStatus { 
    	if (radius.length != 2) return eMsgStatus.kBadParameters;
    	this.fRadius = radius;
       	return eMsgStatus.kProcessed;
    }

    _getRadius()  {return () => this.getRadius()}
    _setRadius()  {return (radius : Array<number>) => this.setRadius(radius)}
}
