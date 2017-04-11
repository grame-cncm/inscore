///<reference path="IObject.ts"/>

class IFile extends IObject{

    fFile: string;
    
    constructor(name: string, parent: IObject){
        super(name, parent);
        this.fTypeString = kFileType;
    }

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
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, "'" + this.getFile() + "'"]); 
    }
}