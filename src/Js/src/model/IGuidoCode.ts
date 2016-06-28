///<reference path="IObject.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>


class IGuidoCode extends IObject { 
    //protected kGuidoCodeType: string;
    
    protected fGMNsvg: string;
    protected fPage: number;
    protected fPageFormat: Array<number>;
    
    protected fCurrentPagesCount: number;
    
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        //this.kGuidoCodeType = 'gmn';
        this.fTypeString = kGuidoCodeType;
        
        this.fCurrentPagesCount = 1; 
        this.fPage = 1; 
        //this.fPageFormat = [21.0f, 29.7f]; 
	    
        super.setHandlers();
    }
    
    setGMNsvg(gmn: string): void				        { this.fGMNsvg = gmn; /*localMapModified(true);*/ }
	setPage(page: number): void							{ this.fPage = page; /*localMapModified(true);*/ }
	setPageFormat(pageFormat: Array<number>): void	    { this.fPageFormat = pageFormat; /*localMapModified(true);*/ }
    //setdPage(dpage: number): void                       {}
    
    getGMNsvg(): string			        { return this.fGMNsvg; }
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
            if (gmn.value != this.getGMNsvg()) {
                if (this.fTypeString == kGuidoCodeType) {
                    let gr = guidoEngine.ar2gr(ar);
                    this.setGMNsvg(guidoEngine.gr2SVG(gr, 1, false, 0));
                    guidoEngine.freeGR(gr);                   
                }
                if (this.fTypeString == kGuidoPianoRollType) {
                    let guidoPianoRoll  = new Module.GUIDOPianoRollAdapter;
                    let pr = guidoPianoRoll.ar2PianoRoll(PianoRollType.kSimplePianoRoll, ar)         
                    this.setGMNsvg(guidoPianoRoll.svgExport(pr, -1, -1));
                    guidoPianoRoll.destroyPianoRoll(pr);                                     
                }
                
                status = msgStatus.kProcessed;
                this.newData(true);
            }
            else status = msgStatus.kProcessedNoChange;

        }
        else status = msgStatus.kBadParameters;
        guidoEngine.freeAR(ar);
        guidoEngine.closeParser(p);
        return status;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, 'todo']); 
    }    
}