///<reference path="IObject.ts"/>

class BezierCurve {
    protected fPointA: [number, number];
	protected fPointB: [number, number];
	protected fPointC: [number, number];
   	protected fPointD: [number, number];
        
    constructor(a: [number, number], b: [number, number], c: [number, number], d: [number, number]) {
        this.fPointA = a;
        this.fPointB = b;
        this.fPointC = c;
        this.fPointD = d;
    }
		
	diff (other: BezierCurve) {
		return  (this.fPointA!=other.fPointA) || 
                (this.fPointB!=other.fPointB) || 
                (this.fPointC!=other.fPointC) || 
                (this.fPointD!=other.fPointD);
    }
}  
    
class CurveData {
    protected fdata: Array<BezierCurve>;
    
    constructor() { this.fdata = new Array<BezierCurve>(); }

    addCurve(curve: BezierCurve): void  { this.fdata.push(curve); }
    getCurve(): Array<BezierCurve>      { return this.fdata; }
    size(): number                      { return this.fdata.length; }   
}     


class ICurve extends IObject {
    
    protected kCurveType: string;
    protected fPoints: CurveData;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kCurveType = 'curve';
        this.fTypeString = this.kCurveType;
        this.fPoints = new CurveData();
    }

    setHandlers()                   {  super.setHandlers(); }
    setPoints(points: CurveData)    { this.fPoints = points; }
    getPoints(): CurveData          { return this.fPoints; }
    
    set(msg: IMessage): msgStatus	{
        let status = super.set(msg);
        
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status; 

        if ( (msg.size() > 1) && ( (msg.size() % 8)==2 ) ) {
            //Build the vector of points reading the message.
            let curveData = new CurveData();
            for ( let i = 2 ; i < msg.size() ; i+=8 ) {
                let ax = msg.paramNum(i),   ay = msg.paramNum(i+1);
                let bx = msg.paramNum(i+2), by = msg.paramNum(i+3);
                let cx = msg.paramNum(i+4), cy = msg.paramNum(i+5);
                let dx = msg.paramNum(i+6), dy = msg.paramNum(i+7);
                
                if (!ax.correct	|| !ay.correct ||
                    !bx.correct || !by.correct ||
                    !cx.correct || !cy.correct ||
                    !dx.correct || !dy.correct) {
                        return msgStatus.kBadParameters;
                }                
                let bezierCurve = new BezierCurve( [ax.value, ay.value],
                                                   [bx.value, by.value],
                                                   [cx.value, cy.value],
                                                   [dx.value, dy.value] );    
                curveData.addCurve( bezierCurve );
            }
            
            //Compares the points vector with the current one.
            if ( curveData.size() != this.getPoints().size() ) {
                this.setPoints(curveData);
                this.newData(true);
                return msgStatus.kProcessed;
            }
            for (let i = 0 ; i < curveData.size() ; i++ ) {
                if (curveData[i] != this.getPoints()[i]) {
                    this.setPoints(curveData);
                    this.newData(true);
                    return msgStatus.kProcessed;
                }
            }
        }
        return msgStatus.kBadParameters;
    }

    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.kCurveType, "todo"]); 
    }
}