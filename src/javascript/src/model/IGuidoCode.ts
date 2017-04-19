///<reference path="IObject.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>
///<reference path="../externals/libGUIDOEngine.ts"/>
///<reference path="../mapping/TTime2GraphicMap.ts"/>


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
        	IGuidoCode.fGuidoEngine.init();
        	IGuidoCode.fGuidoMap = new Module.GUIDOScoreMap;
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
    
    mapScale (xscale: number, yscale: number): void {
		this.fMapping.forEach (function (elt: TTime2GraphicRelation) { elt.fGraph.scale(xscale, yscale) } );
    }
    
    AR2SVG(ar: ARHandler): string {
        let gr = IGuidoCode.fGuidoEngine.ar2gr(ar);
        let svg = IGuidoCode.fGuidoEngine.gr2SVG(gr, 1, false, 0);
        this.getMap (gr);
        this.getViews()[0].setMapScaleHandler ((x: number, y: number): void => { this.mapScale(x, y); }) 
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
		this.fNewData = true;
        return eMsgStatus.kProcessed;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fGMN]); 
    }    
}