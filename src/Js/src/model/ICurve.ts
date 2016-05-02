///<reference path="IObject.ts"/>

class BezierCurve {
    protected fPoints: Array<number>;
        
    constructor(ax: number, ay: number, bx: number, by: number, cx: number, cy: number, dx: number, dy: number ) {
        this.fPoints = [ax, ay, bx, by, cx, cy, dx, dy];
    }
		
	equal (other: BezierCurve) {
		return this.fPoints.every ( ( val: number, index: number) => { return val == other.fPoints[index]; } );
	}

	points(): Array<number> { return this.fPoints; }
}  
    

class ICurve extends IObject {
    
    protected kCurveType: string;
    protected fPoints: Array<BezierCurve>;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kCurveType = 'curve';
        this.fTypeString = this.kCurveType;
        this.fPoints = new Array<BezierCurve>();
    }

    setHandlers()                   		 { super.setHandlers(); }
    setPoints(points: Array<BezierCurve>)    { this.fPoints = points; }
    getPoints(): Array<BezierCurve>          { return this.fPoints; }
    
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
                
                if (!ax.correct	|| !ay.correct ||
                    !bx.correct || !by.correct ||
                    !cx.correct || !cy.correct ||
                    !dx.correct || !dy.correct) {
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
    	let a = this.fPoints[0].points();
    	for ( let i=1; i<this.fPoints.length; i++) 
    		a = a.concat(this.fPoints[i].points());
    	return a;
    }

    getSet(): IMessage	{ 
    	let a: Array<any> = [kset_SetMethod, this.kCurveType];
    	return new IMessage(this.getOSCAddress(), a.concat (this.toArray()) ); 
    }
}