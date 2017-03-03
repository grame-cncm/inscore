///<reference path="IObject.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>
///<reference path="../externals/libGUIDOEngine.ts"/>

class IGuidoCode extends IObject { 
	static fGuidoEngine: GuidoEngineAdapter;

    protected fGMN: string;
    protected fSVG: string;
    protected fPage: number;
    protected fPageFormat: Array<number>;    
    protected fCurrentPagesCount: number;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        
        if (!IGuidoCode.fGuidoEngine) {
        	IGuidoCode.fGuidoEngine = new Module.GuidoEngineAdapter;
        	IGuidoCode.fGuidoEngine.init();
        }
        
        this.fTypeString = kGuidoCodeType;
        this.fCurrentPagesCount = 1; 
        this.fPage = 1; 
        //this.fPageFormat = [21.0f, 29.7f]; 
	    
        super.setHandlers();
    }
    
    setSVG(gmn: string): void				        { this.fSVG = gmn; /*localMapModified(true);*/ }
	setPage(page: number): void							{ this.fPage = page; /*localMapModified(true);*/ }
	setPageFormat(pageFormat: Array<number>): void	    { this.fPageFormat = pageFormat; /*localMapModified(true);*/ }
    //setdPage(dpage: number): void                       {}
    
    getSVG(): string			        { return this.fSVG; }
	getPage(): number					{ return this.fPage; }
	getPageFormat(): Array<number>		{ return this.fPageFormat; }
	//getPageCount(): number              {return}
    
    str2AR(gmn: string): ARHandler {
        let p = IGuidoCode.fGuidoEngine.openParser();
	    let ar = IGuidoCode.fGuidoEngine.string2AR(p, gmn);
	    if (!ar) {
			let error = IGuidoCode.fGuidoEngine.parserGetErrorCode(p);
			ITLError.write ("Error line " + error.line + " column " + error.col + ": " + error.msg);
	    }
        IGuidoCode.fGuidoEngine.closeParser(p);
	    return ar;
    }
    
    AR2SVG(ar: ARHandler): string {
        let gr = IGuidoCode.fGuidoEngine.ar2gr(ar);
        let svg = IGuidoCode.fGuidoEngine.gr2SVG(gr, 1, false, 0);
        IGuidoCode.fGuidoEngine.freeGR(gr);
	    return svg;
    }
    
    set(msg: IMessage): msgStatus {
        let status = super.set(msg);
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status;

		if (msg.size() != 3) return msgStatus.kBadParameters;
        let gmn = msg.paramStr(2);
		if (!gmn.correct) return msgStatus.kBadParameters;
        let ar = this.str2AR (gmn.value);
		if (!ar) return msgStatus.kBadParameters;
		
		this.fGMN = gmn.value;
		this.fSVG = this.AR2SVG (ar);
		IGuidoCode.fGuidoEngine.freeAR (ar);
        return msgStatus.kProcessed;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fGMN]); 
    }    
}