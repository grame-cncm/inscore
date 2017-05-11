///<reference path="IText.ts"/>

interface TTxtfLoadEndHandler 		{ (): void; }

class ITextf extends IText {
    protected fFile: string;
        
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
    getTextFile(): string           { return this.fFile; }
    setTextFile(file: string): void	{ this.fFile = file; }

// SET HANDLER
//--------------------------------------------------------------    
   set(msg: IMessage): eMsgStatus { 
        let status = super.set(msg);
        if (status != eMsgStatus.kProcessed) return status; 

		let file = Tools.setFile (msg, (arg: string): void => this.success(arg), (arg: string): void => this.error(arg));
		if (file) {
			this.fFile = file;
        	return eMsgStatus.kProcessed;
		}
        return eMsgStatus.kBadParameters;
    }

    getText(): string { 
       if (this.fText !== "") return this.fText
       else return this.fFile; 
    }

// GETSET METHOD
//--------------------------------------------------------------    
    getSet(): IMessage	{ 
    	let a: Array<any> = [kset_SetMethod, this.fTypeString];
    	return new IMessage(this.getOSCAddress(), a.concat ("'" + this.fFile + "'") ); 
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