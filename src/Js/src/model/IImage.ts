///<reference path="IObject.ts"/>

class IImage extends IObject {
    
    protected kImgType: string;
    protected fFile: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kImgType = 'img';
        this.fTypeString = this.kImgType;      
    }

    colorAble(): void { }		// color attributes are not available for images
    getFile(): string { return this.fFile; }

    set(msg:IMessage): msgStatus {
        let status = super.set(msg);
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status;
        
        if (msg.size() == 3) {
            let file = msg.paramStr(2);
            if (!file.correct) return msgStatus.kBadParameters;
        	this.fFile = file.value;
        	status = msgStatus.kProcessed;
        }
        else status = msgStatus.kBadParameters;
        return status;
    }
    
    getSet(): IMessage	{
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.kImgType, "'"+this.getFile()+"'"]); 
    }
}