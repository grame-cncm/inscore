///<reference path="IText.ts"/>

interface TTxtfLoadEndHandler 		{ (): void; }

class ITextf extends IText {
    protected fTextFile: string;
    //protected kTextfType: string;
        
    constructor(name: string, parent: IObject) {
        super(name, parent);
        //this.kTextfType = 'txtf';
        this.fTypeString = kTextfType;

        super.setHandlers();
     	this.fGetMsgHandlerMap[""] = new TGetMsgHandlerText(this._getTextFile());
    }    

// GETS / SETS VALUES 
//--------------------------------------------------------------    
    getTextFile(): string           { return this.fTextFile; }
    _getTextFile(): GetStringMethod { return () => this.fTextFile; }
    setTextFile(file: string): void	{ this.fTextFile = file; }

// SET HANDLER
//--------------------------------------------------------------    
   set(msg: IMessage): eMsgStatus { 
		        console.log("ITextf set: " + msg);
        let status = super.set(msg);
        if (status != eMsgStatus.kProcessed) return status; 

        let n = msg.size();
        if (n == 3) {
        	let file = msg.paramStr(2);
        	if (file.correct) {
        		this.fTextFile = file.value;
		        let reader = new FileReader();
		        let b = new Blob([file.value]);
		        console.log("readAsText: " + b);
        		reader.onloadend = this._setText(reader);
		        reader.readAsText(b);
	            status = eMsgStatus.kProcessed;
        	}
	        else status = eMsgStatus.kBadParameters;        	
        }
        return status;
    }
    _setText(reader: FileReader) : TTxtfLoadEndHandler { return () => { console.log("_setText: " +reader.result); this.setText(reader.result); }
}

// GETSET METHOD
//--------------------------------------------------------------    
    getSet(): IMessage	{ 
    	let a: Array<any> = [kset_SetMethod, this.fTypeString];
    	return new IMessage(this.getOSCAddress(), a.concat ("'"+this.fTextFile+"'") ); 
    }
}