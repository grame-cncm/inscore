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
                Tools.readFile(file.value, (arg: string): void => this.success(arg), (arg: string): void => this.error(arg));
	            status = eMsgStatus.kProcessed;
        	}
	        else status = eMsgStatus.kBadParameters;        	
        }
        return status;
    }

    getText(): string { 
       if (this.fText !== "") return this.fText
       else return this.fTextFile; 
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
        this.fText = content;
        this.newData(true);
        this.addState (eObjState.kModified);
        this.subModPropagate (this.fParent);
    }

    error(content: string): void{
        console.log("Text file error !");
    }
}