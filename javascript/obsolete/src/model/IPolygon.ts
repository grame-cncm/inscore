///<reference path="IObject.ts"/>
///<reference path="../lib/TPoint.ts"/>

class IPolygon extends IObject {
    //protected kPolygonType: string;
    protected fPoints: Array<TPoint>;
 
    constructor(name: string, parent: IObject) {
        super(name, parent);
        //this.kPolygonType = 'polygon';
        this.fTypeString = kPolygonType;
        this.fPoints = new Array<TPoint>();
    }
    setHandlers(){
        super.setHandlers();
        this.brushAble();
        this.fGetMsgHandlerMap[""] = new TGetMsgHandlerArray(this._getPoints());
    }
    
    setPoints(points: Array<TPoint>)    { this.fPoints = points; }
    getPoints(): Array<TPoint>          { return this.fPoints; }
    
    _getPoints(): GetArrayMethod        { return () => this.fPoints; }
    
    set(msg: IMessage): eMsgStatus {
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status; 

        if ( (msg.size() > 1) && ( ((msg.size()-1) % 2)==1 ) ) {

            //Build the vector of points reading the message.
            let points = new Array<TPoint>();
            for (let i = 2 ; i < msg.size() ; i+=2 ) {
                let a = msg.paramNum(i), b = msg.paramNum(i+1);
                if (!a.correct || !b.correct) { return eMsgStatus.kBadParameters; }
                points.push( new TPoint(a.value, b.value) );
            }

            //Compares the points vector with the current one.
            if ( points.length != this.getPoints().length ) {
                this.setPoints(points);
                this.newData(true);
                return eMsgStatus.kProcessed;
            }
            for (let i = 0 ; i < points.length ; i++ ) {
                if (points[i] != this.getPoints()[i]) {
                    this.setPoints(points);
                    this.newData(true);
                    return eMsgStatus.kProcessed;
                }
            }
            return eMsgStatus.kProcessedNoChange;
        }
        return eMsgStatus.kBadParameters;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, 'todo']); 
    }
    
}
