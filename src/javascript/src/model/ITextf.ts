///<reference path="IText.ts"/>

interface TTxtfLoadEndHandler 		{ (): void; }

class ITextf extends IText {
    protected fTextFile: string;
        
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kTextfType;
    }
    
    setHandlers() : void {
        super.setHandlers();
     	this.fGetMsgHandlerMap[""] = new TGetMsgHandlerText( (): string => { return this.getTextFile(); });
    }

// GETS / SETS VALUES 
//--------------------------------------------------------------    
    getTextFile(): string           { return this.fTextFile; }
    setTextFile(file: string): void	{ this.fTextFile = file; }

// SET HANDLER
//--------------------------------------------------------------    
   set(msg: IMessage): eMsgStatus { 
        let status = super.set(msg);
        if (status != eMsgStatus.kProcessed) return status; 

        let n = msg.size();
        if (n == 3) {
        	let file = msg.paramStr(2);
        	if (file.correct) {
        		Tools.readFile(file.value, this.success, this.error);
		        let reader = new FileReader();
		        let b = new Blob([file.value]);
        		reader.onloadend = this._setText(reader);
		        reader.readAsText(b);
	            status = eMsgStatus.kProcessed;
        	}
	        else status = eMsgStatus.kBadParameters;        	
        }
        return status;
    }
    _setText(reader: FileReader) : TTxtfLoadEndHandler { 
    	return () => { this.setText(reader.result); }
	}

// GETSET METHOD
//--------------------------------------------------------------    
    getSet(): IMessage	{ 
    	let a: Array<any> = [kset_SetMethod, this.fTypeString];
    	return new IMessage(this.getOSCAddress(), a.concat ("'" + this.fTextFile + "'") ); 
    }

// READER METHOD
//--------------------------------------------------------------    
    success(content: string): void{
        this.fTextFile = content;
        console.log("ITextf success content : " + this.fTextFile);
    }

    error(content: string): void{
        console.log("Text file error !");
    }
}