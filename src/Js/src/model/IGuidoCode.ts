///<reference path="IObject.ts"/>
///<reference path="../externals/guido/libGUIDOEngine.d.ts"/>


class IGuidoCode extends IObject { 
    protected kGuidoCodeType: string;
    
    protected fGMN: string;
    protected fPage: number;
    protected fPageFormat: Array<number>;
    
    protected fCurrentPagesCount: number;
    
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kGuidoCodeType = 'gmn';
        this.fTypeString = this.kGuidoCodeType;
        
        this.fCurrentPagesCount = 1; 
        this.fPage = 1; 
        //this.fPageFormat = [21.0f, 29.7f]; 
	    
        super.setHandlers();
    }
    
    setGMN(gmn: string): void				            { this.fGMN = gmn; /*localMapModified(true);*/ }
	setPage(page: number): void							{ this.fPage = page; /*localMapModified(true);*/ }
	setPageFormat(pageFormat: Array<number>): void	    { this.fPageFormat = pageFormat; /*localMapModified(true);*/ }
    //setdPage(dpage: number): void                       {}
    
    getGMN(): string			        { return this.fGMN; }
	getPage(): number					{ return this.fPage; }
	getPageFormat(): Array<number>		{ return this.fPageFormat; }
	//getPageCount(): number              {return}
    
    set(msg: IMessage): msgStatus {
        let status = super.set(msg);
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status;

        let gmn = msg.paramStr(2);
        
        // test if the parsing works
        let guidoEngine = new Module.GuidoEngineAdapter;
        guidoEngine.init();        
        let p = guidoEngine.openParser();
	    let ar = guidoEngine.string2AR(p, gmn.value);
        
        if ((msg.size() == 3) && gmn.correct && ar) {
            /*
            if(expr){
                if(!fExprHandler.composeExpr(expr, t))
                    return msgStatus.kBadParameters;
            }
            else
                    fExprHandler.clearExpr();
            */
            if (gmn.value != this.getGMN()) {
                this.setGMN(gmn.value);
                status = msgStatus.kProcessed;
                this.newData(true);
            }
            else status = msgStatus.kProcessedNoChange;

        }
        else status = msgStatus.kBadParameters;
        return status;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, 'todo']); 
    }    
}