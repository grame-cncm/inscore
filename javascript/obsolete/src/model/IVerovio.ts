///<reference path="IObject.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/verovio-toolkit.d.ts"/>
///<reference path="../mapping/TTime2GraphicMap.ts"/>


class IVerovio extends IObject { 
	static fVerovio: VerovioToolkit;
    protected fMEI: string;
    protected fSVG: string;
    protected fPage: number;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        if (!IVerovio.fVerovio) {
			IVerovio.fVerovio = new verovio.toolkit();
	        console.log ("Verovio " + IVerovio.fVerovio.getVersion() );
	    }
        this.fTypeString = kVerovioType;
        this.fPage = 1; 
        this.fSVG = "";
        this.fPosition.setWidth (0);
        this.fPosition.setHeight (0);
        super.setHandlers();
    }

   
    setSVG(gmn: string): void				        { this.fSVG = gmn; /*localMapModified(true);*/ }
	setPage(page: number): void						{ this.fPage = page; /*localMapModified(true);*/ }
    //setdPage(dpage: number): void                       {}

	mei2svg (data: string) : void {
		this.fMEI = data;
		this.fSVG = IVerovio.fVerovio.renderData (this.fMEI, {});
		this.fNewData = true;
	}
	    
    getSVG(size: TSize): string			{ return this.fSVG.length ? this.fSVG : ""; }
	getPage(): number					{ return this.fPage; }
	//getPageCount(): number              {return}

    set(msg: IMessage): eMsgStatus {
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;

		if (msg.size() != 3) return eMsgStatus.kBadParameters;
        let mei = msg.paramStr(2);
		if (!mei.correct) return eMsgStatus.kBadParameters;
		this.mei2svg (mei.value);
        return eMsgStatus.kProcessed;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fMEI]); 
    }    
}