///<reference path="IObject.ts"/>

class IVideo extends IObject {
    
    protected fFile: string;

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kVideoType;      
    }    

    colorAble(): void { }		// color attributes are not available for vidéos
    getFile(): string { return this.fFile; }
    
    set(msg:IMessage): eMsgStatus {
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;
        
        if (msg.size() == 3) {
            let file = msg.paramStr(2);
            if (!file.correct) return eMsgStatus.kBadParameters;
        	this.fFile = file.value;
            this.newData(true);
        	status = eMsgStatus.kProcessed;
        }
        else status = eMsgStatus.kBadParameters;
        return status;
    }

    getSet(): IMessage	{
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, "'"+this.getFile()+"'"]); 
    }    
}

