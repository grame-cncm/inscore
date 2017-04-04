///<reference path="IObject.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>
///<reference path="../externals/libGUIDOEngine.ts"/>

class IGuidoCode extends IObject { 
	static fGuidoEngine: GuidoEngineAdapter;
	static fGuidoMap: GuidoScoreMapAdapter;

    protected fGMN: string;
    protected fSVG: string;
    protected fPage: number;
    protected fPageFormat: Array<number>;    
    protected fCurrentPagesCount: number;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        
        if (!IGuidoCode.fGuidoEngine) {
        	IGuidoCode.fGuidoEngine = new Module.GuidoEngineAdapter;
//        	IGuidoCode.fGuidoMap = new Module.GuidoScoreMapAdapter;
        	IGuidoCode.fGuidoEngine.init();
        }
        
        this.fTypeString = kGuidoCodeType;
        this.fCurrentPagesCount = 1; 
        this.fPage = 1; 
        //this.fPageFormat = [21.0f, 29.7f]; 
        this.fPosition.setWidth (0);
        this.fPosition.setHeight (0);
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

/*    
    getMap(gr: GRHandler): void {
		let map = IGuidoCode.fGuidoMap.getSystemMap(gr, 1, 100, 100);
console.log ("IGuidoCode getMap: " + map.map.length + " elements");
    }
*/
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
//        this.getMap (gr);
        IGuidoCode.fGuidoEngine.freeGR(gr);
	    return svg;
    }
    
    set(msg: IMessage): eMsgStatus {
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;

		if (msg.size() != 3) return eMsgStatus.kBadParameters;
        let gmn = msg.paramStr(2);
		if (!gmn.correct) return eMsgStatus.kBadParameters;
        let ar = this.str2AR (gmn.value);
		if (!ar) return eMsgStatus.kBadParameters;
		
		this.fGMN = gmn.value;
		this.fSVG = this.AR2SVG (ar);
		IGuidoCode.fGuidoEngine.freeAR (ar);
        return eMsgStatus.kProcessed;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fGMN]); 
    }    
}