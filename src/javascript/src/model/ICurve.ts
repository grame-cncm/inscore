///<reference path="IObject.ts"/>
///<reference path="../lib/TPoint.ts"/>

class BezierCurve {
    protected fPoints: Array<TPoint>;
        
    constructor(ax: number, ay: number, bx: number, by: number, cx: number, cy: number, dx: number, dy: number ) {
        this.fPoints = new Array<TPoint>();
        this.fPoints.push (new TPoint(ax, ay));
        this.fPoints.push (new TPoint(bx, by));
        this.fPoints.push (new TPoint(cx, cy));
        this.fPoints.push (new TPoint(dx, dy));
    }
		
	equal (other: BezierCurve) {
		return this.fPoints.every ( ( p: TPoint, index: number) => { return p.equal (other.fPoints[index]); } );
	}

	points(): Array<TPoint> { return this.fPoints; }

    toArray(): Array<number> {
    	let a = new Array<number>();
    	for ( let i=1; i< this.fPoints.length; i++) 
    		a = a.concat(this.fPoints[i].toArray());
    	return a;
    }
}  
    

class ICurve extends IObject 
{
    protected fPoints: Array<BezierCurve>;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kCurveType;
        this.fPoints = new Array<BezierCurve>();
        this.fPenControl.setPenWidth(1);
        super.setHandlers();
        this.fGetMsgHandlerMap[""] = new TGetMsgHandlerArray(this._getPoints());
    }

    setHandlers(){
        super.setHandlers();
        this.brushAble();
    }

    setPoints(points: Array<BezierCurve>)    { this.fPoints = points; }
    getPoints(): Array<BezierCurve>          { return this.fPoints; }
    
    _getPoints(): GetArrayMethod        { return () => this.fPoints; }

    set(msg: IMessage): msgStatus	{
        let status = super.set(msg);
        
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status; 

        if ( (msg.size() > 1) && ( (msg.size() % 8)==2 ) ) {
            //Build the vector of points reading the message.
            let curveData = new Array<BezierCurve>();
            for ( let i = 2 ; i < msg.size() ; i+=8 ) {
                let ax = msg.paramNum(i),   ay = msg.paramNum(i+1);
                let bx = msg.paramNum(i+2), by = msg.paramNum(i+3);
                let cx = msg.paramNum(i+4), cy = msg.paramNum(i+5);
                let dx = msg.paramNum(i+6), dy = msg.paramNum(i+7);
                
                if (!ax.correct	|| !ay.correct || !bx.correct || !by.correct ||
                    !cx.correct || !cy.correct || !dx.correct || !dy.correct) {
                        return msgStatus.kBadParameters;
                }                
                let bezierCurve = new BezierCurve( ax.value, ay.value, bx.value, by.value, cx.value, cy.value, dx.value, dy.value );    
                curveData.push( bezierCurve );
            }
            
            //Compares the points vector with the current one.
            if ( curveData.length != this.getPoints().length ) {
                this.setPoints(curveData);
                this.newData(true);
                return msgStatus.kProcessed;
            }
            for (let i = 0 ; i < curveData.length ; i++ ) {
                if (curveData[i] != this.getPoints()[i]) {
                    this.setPoints(curveData);
                    this.newData(true);
                    return msgStatus.kProcessed;
                }
            }
        }
        return msgStatus.kBadParameters;
    }

    toArray(): Array<number> {
    	let a = new Array<number>();
    	for ( let i=0; i < this.fPoints.length; i++)
    		a = a.concat(this.fPoints[i].toArray());
    	return a;
    }

    toString(): string {
    	let str = "";
    	for ( let i=0; i < this.fPoints.length; i++)
    		str += this.fPoints[i].toString();
    	return str;
    }

    getSet(): IMessage	{ 
    	let a: Array<any> = [kset_SetMethod, this.fTypeString];
    	return new IMessage(this.getOSCAddress(), a.concat (this.toArray()) ); 
    }
}