///<reference path="IObject.ts"/>

class TPoint {
    protected fX: number;
    protected fY: number;
    
    constructor(x: number, y: number) {
        this.fX = x;
        this.fY = y;
    }
}

class ILine extends IObject {
    
    protected kLineType: string;
    protected fPoint: TPoint;
    protected fWAMode: boolean;		

    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kLineType = 'line';
        this.fTypeString = this.kLineType;
    }
    
    setPoint(p: TPoint)		{ this.fPoint = p; }


    set(msg:IMessage): msgStatus {
        let status = super.set(msg);
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status;
        
        if (msg.size() == 5) {
            let mode = msg.paramStr(2); 
            let a = msg.paramNum(3), b = msg.paramNum(4); 
            
            if (!mode.correct)
                return msgStatus.kBadParameters;
            if (!a.correct || !b.correct) {
                return msgStatus.kBadParameters;
            }
            
            
            if (mode.value == "xy") {
                this.setPoint( new TPoint(a.value, b.value) );
            }
            else if (mode.value == "wa") {
                this.fWAMode = true;
                let x: number = a.value * Math.cos(Math.PI * b.value / 180);
                let y: number = a.value * Math.sin(Math.PI * b.value / 180);
                this.setPoint( new TPoint(x, y) );
            }
            else return msgStatus.kBadParameters;
            this.newData(true);
            status = msgStatus.kProcessed;
        }
        else status = msgStatus.kBadParameters;
        return status;
    }
    
    getSet(): IMessage	{
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.kLineType, "todo"]); 
    }
}