
///<reference path="../externals/libfaust.d.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/Tools.ts"/>

///<reference path="IFaust.ts"/>

class IFaustf extends IFaust {
	private fFile: string;
	        
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kFaustfType;
        this.fFile = "";
    }

// READER METHOD
//--------------------------------------------------------------    
    success(content: string): void 	{ 
    	this.createDsp (content); 
    }

    error(content: string): void{
        console.log("Read file error !");
    }
   
// SET HANDLER
//--------------------------------------------------------------    
   set(msg: IMessage): eMsgStatus { 
        let status = this.objectset(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status; 

        let n = msg.size();
        if (n != 3) return eMsgStatus.kBadParameters;
        let file =  msg.paramStr(2);
        if (!file.correct) return eMsgStatus.kBadParameters;
        
        this.fFile = file.value;
        Tools.readFile(file.value, (arg: string): void => this.success(arg), (arg: string): void => this.error(arg));
        return eMsgStatus.kProcessed;
    }

// GETSET METHOD
//--------------------------------------------------------------    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fFile] ); 
    }
}
