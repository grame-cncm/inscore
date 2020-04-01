///<reference path="IObject.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>
///<reference path="../externals/libGUIDOEngine.ts"/>
///<reference path="../mapping/TTime2GraphicMap.ts"/>


class IGuidoCode extends IObject { 
	static fGuidoEngine: GuidoEngineAdapter;
	static fGuidoMap: GuidoScoreMapAdapter;
 	static fPianoRoll: GUIDOPianoRollAdapter

    protected fGMN: string;
    protected fAR: ARHandler;
    protected fGR: GRHandler;
    protected fSVG: string;
    protected fPage: number;
    protected fPageFormat: Array<number>;    
    protected fCurrentPagesCount: number;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        
        if (!IGuidoCode.fGuidoEngine) {
        	var module = GuidoModule();
        	IGuidoCode.fGuidoEngine = new module.GuidoEngineAdapter();
        	IGuidoCode.fGuidoMap = new module.GUIDOScoreMap();
        	IGuidoCode.fPianoRoll  = new module.GUIDOPianoRollAdapter();
        	IGuidoCode.fGuidoEngine.init();
        }
        
        this.fTypeString = kGuidoCodeType;
        this.fCurrentPagesCount = 1; 
        this.fPage = 1; 
        this.fSVG = "";
        this.fAR = null;
        //this.fPageFormat = [21.0f, 29.7f]; 
        this.fPosition.setWidth (0);
        this.fPosition.setHeight (0);
        super.setHandlers();
    }

	del(): void {
		if (this.fAR) 	IGuidoCode.fGuidoEngine.freeAR (this.fAR);
		super.del();
    }
   
    setSVG(gmn: string): void				        { this.fSVG = gmn; /*localMapModified(true);*/ }
	setPage(page: number): void							{ this.fPage = page; /*localMapModified(true);*/ }
	setPageFormat(pageFormat: Array<number>): void	    { this.fPageFormat = pageFormat; /*localMapModified(true);*/ }
    //setdPage(dpage: number): void                       {}
    
    getSVG(size: TSize): string			{ return this.fSVG.length ? this.fSVG : this.AR2SVG (size); }
	getPage(): number					{ return this.fPage; }
	getPageFormat(): Array<number>		{ return this.fPageFormat; }
	//getPageCount(): number              {return}

    
    guidoMap2inscoreMap(json: string): void {
		let map: Time2GraphicMap = eval(json);
		if (map.length) this.fMapping.clear();

		map.forEach( (elt: Time2GraphicElt) : void => {
        	let timeSegment = new TimeInterval (new Fraction(elt.time.start), new Fraction(elt.time.end));
        	let graphicSegment = new TGraphicSegment (new NumberInterval(elt.graph.left, elt.graph.right), 
        		new NumberInterval(elt.graph.top, elt.graph.bottom));
			this.fMapping.addElt ( new TTime2GraphicRelation(timeSegment, graphicSegment));
		} );
	}    
    getMap(gr: GRHandler): void { this.guidoMap2inscoreMap (IGuidoCode.fGuidoMap.getSystemMap(gr, 1, 1, 1)) };

    str2AR(gmn: string): boolean {
        let p = IGuidoCode.fGuidoEngine.openParser();
	    let ar = IGuidoCode.fGuidoEngine.string2AR(p, gmn);
	    if (!ar) {
			let error = IGuidoCode.fGuidoEngine.parserGetErrorCode(p);
			ITLError.write ("Error line " + error.line + " column " + error.col + ": " + error.msg);
			 return false;
	    }
	    this.fAR = ar;
        IGuidoCode.fGuidoEngine.closeParser(p);
        return true;
    }
    
    mapScale (xscale: number, yscale: number): void {
		this.fMapping.forEach (function (elt: TTime2GraphicRelation) { elt.fGraph.scale(xscale, yscale) } );
    }
    
    AR2SVG(size: TSize): string {
        if (this.fAR) {
        	let gr = IGuidoCode.fGuidoEngine.ar2gr(this.fAR);
        	this.fSVG = IGuidoCode.fGuidoEngine.gr2SVG(gr, 1, false, 0);
        	this.getMap (gr);
        	this.getViews()[0].setMapScaleHandler ((x: number, y: number): void => { this.mapScale(x, y); }) 
       		IGuidoCode.fGuidoEngine.freeGR(gr);
       	}
	    return this.fSVG;
    }
    
    set(msg: IMessage): eMsgStatus {
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;

		if (msg.size() != 3) return eMsgStatus.kBadParameters;
        let gmn = msg.paramStr(2);
		if (!gmn.correct) return eMsgStatus.kBadParameters;
        if ( !this.str2AR (gmn.value))
			return eMsgStatus.kBadParameters;
		
		this.fGMN = gmn.value;
		this.fNewData = true;
        return eMsgStatus.kProcessed;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fGMN]); 
    }    
}