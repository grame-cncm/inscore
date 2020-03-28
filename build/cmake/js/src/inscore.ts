///<reference path="../libINScore.d.ts"/>


//----------------------------------------------------------------------------
// INScore interface
//----------------------------------------------------------------------------
class INScore {

    private static fObjects:   INScoreObject;
    private	fInscore       :   INScoreAdapter;
    private	fInscoreGlue   :   INScoreGlue;
    private	fJSGlue        :   INScoreJSGlue;

    async initialise():Promise<any> { 
        var module = INScoreModule();
        return new Promise( (success: any, failure: any) => {
            module['onRuntimeInitialized'] = () => {
                this.moduleInit (module);
                success ( this ); 
                }
        });
    }
            
    //------------------------------------------------------------------------
    // async initialization
    moduleInit ( module : any ) : void {
        this.fInscore 		= new module.INScoreAdapter();
        this.fJSGlue 		= new module.INScoreJSGlue();
        INScore.fObjects	= new module.IObjectAdapter();
    }
    
    static objects() : INScoreObject	{ return INScore.fObjects; }
        
    //------------------------------------------------------------------------
    // INScore interface
    start() : void	                { this.fInscoreGlue = this.fInscore.start (0, 0, 0); }
	stop()  : void			        { this.fInscore.stop ( this.fInscoreGlue ); }

	loadInscore	 (script: string, autoparse = false)	        { return this.fInscore.loadInscore (script, autoparse); }
	loadInscore2 (script: string)				                { return this.fInscore.loadInscore2 (script); }

	postMessage	(adr: string, msg: TMessage)	: void          { this.fInscore.postMessage (adr, msg); }
	postMessageStr (adr: string, meth: string)	: void          { this.fInscore.postMessageStr (adr, meth); }
	postMessageStrI	(adr: string, meth: string, val: number) : void  { this.fInscore.postMessageStrI (adr, meth, val); }
	postMessageStrF	(adr: string, meth: string, val: number) : void  { this.fInscore.postMessageStrF (adr, meth, val); }
	postMessageStrStr(adr: string, meth: string, val: string): void  { this.fInscore.postMessageStrStr (adr, meth, val); }

    delayMessage (adr: string, msg: TMessage)   : void      { this.fInscore.delayMessage (adr, msg); }
	newMessage ()                               : TMessage  { return this.fInscore.newMessage(); }
	newMessageM (meth: string)                  : TMessage  { return this.fInscore.newMessageM(meth); }
	delMessage (msg: TMessage)                  : void      { return this.fInscore.delMessage(msg); }

    msgAddStr (msg: TMessage, str: string)      : void      { return this.fInscore.msgAddStr (msg, str); }
	msgAddF   (msg: TMessage, val: number)      : void      { return this.fInscore.msgAddF (msg, val); }
	msgAddI   (msg: TMessage, val: number)      : void      { return this.fInscore.msgAddI (msg, val); }

    version ()				: number        { return this.fInscore.version(); }
	versionStr ()			: string        { return this.fInscore.versionStr(); }
	guidoversion ()			: string        { return this.fInscore.guidoversion(); }
	musicxmlversion ()		: string        { return this.fInscore.musicxmlversion(); }
        
    //------------------------------------------------------------------------
    // INScore glue interface
    getRate() 		: number        { return this.fInscoreGlue.getRate(); } 
	timeTask ()	    : void          { this.fInscoreGlue.timeTask(); }
	sorterTask()	: void          { this.fInscoreGlue.sorterTask(); }
}

enum TPenStyle 		{ kSolid, kDash, kDot, kDashDot, kDashDotDot }
enum TBrushStyle 	{ kDense1, kDense2, kDense3, kDense4, kDense5, kDense6, kDense7,
					  kNoBrush, kBrushHor, kBrushVer, kCross, kBDiag, kFDiag, kDiagCross }
enum ArrowHead      { NONE, TRIANGLE, DIAMOND, DISK }
            