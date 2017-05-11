///<reference path="IVerovio.ts"/>
///<reference path="../lib/Tools.ts"/>


class IVeroviof extends IVerovio { 
    protected fFile: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kVeroviofType;
    	this.fFile = "";
    }
   
    setSVG(gmn: string): void				{ this.fSVG = gmn; /*localMapModified(true);*/ }    
    getSVG(size: TSize): string				{ return this.fSVG.length ? this.fSVG : Tools.string2svg(this.fFile); }
    
    set(msg: IMessage): eMsgStatus {
        let status = this.basicSet(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;

		let file = Tools.setFile (msg, (arg: string): void => this.success(arg), (arg: string): void => this.error(arg));
		if (file) {
			this.fFile = file;
        	return eMsgStatus.kProcessed;
		}
        return eMsgStatus.kBadParameters;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fFile]); 
    }    

// READER METHOD
//--------------------------------------------------------------    
    success(content: string): void {
        this.mei2svg(content);
		this.fNewData = true;
        this.addState (eObjState.kModified);
        this.subModPropagate (this.fParent);
    }

    error(content: string): void {
        console.log(content);
        this.fSVG = Tools.error2svg();
		this.fNewData = true;
        this.addState (eObjState.kModified);
        this.subModPropagate (this.fParent);
    }
}