///<reference path="IObject.ts"/>
///<reference path="../lib/TPoint.ts"/>

class IPolygon extends IObject {
    protected kPolygonType: string;
    protected fPoints: Array<TPoint>;
 
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kPolygonType = 'polygon';
        this.fTypeString = this.kPolygonType;
        this.fPoints = new Array<TPoint>();
        
        super.setHandlers();
        this.fGetMsgHandlerMap[""] = new TGetMsgHandlerArray(this._getPoints());
    }   
    
    setPoints(points: Array<TPoint>)    { this.fPoints = points; }
    getPoints(): Array<TPoint>          { return this.fPoints; }
    
    _getPoints(): GetArrayMethod        { return () => this.fPoints; }
    
    set(msg: IMessage): msgStatus {
        let status = super.set(msg);
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status; 

        if ( (msg.size() > 1) && ( ((msg.size()-1) % 2)==1 ) ) {

            //Build the vector of points reading the message.
            let points = new Array<TPoint>();
            for (let i = 1 ; i < msg.size() ; i+=2 ) {
                let a = msg.paramNum(2), b = msg.paramNum(3);
                if (!a.correct || !b.correct) { return msgStatus.kBadParameters; }
                points.push( new TPoint(a.value, b.value) );
            }

            //Compares the points vector with the current one.
            if ( points.length != this.getPoints().length ) {
                this.setPoints(points);
                this.newData(true);
                return msgStatus.kProcessed;
            }
            for (let i = 0 ; i < points.length ; i++ ) {
                if (points[i] != this.getPoints()[i]) {
                    this.setPoints(points);
                    this.newData(true);
                    return msgStatus.kProcessed;
                }
            }
            return msgStatus.kProcessedNoChange;
        }
        return msgStatus.kBadParameters;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, 'todo']); 
    }
    
}
