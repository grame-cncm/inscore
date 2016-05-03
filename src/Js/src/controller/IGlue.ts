
///<reference path="IMessage.ts"/>
///<reference path="../inscore.ts"/>
///<reference path="../model/IAppl.ts"/>
///<reference path="../events/documentEvents.ts"/>
///<reference path="../view/ViewUpdater.ts"/>

interface TTimerTask  { (): void; }

class IGlue { 
	protected fAppl: IAppl;
	protected fTimer: number
	
    constructor() 			{ 
    	this.fAppl = new IAppl(); 
    	let inscore = new INScore(this.fAppl);
    }
//	getRoot() : IAppl		{ return this.fAppl; }

    initEventHandlers(): void {
		document.addEventListener("drop", dropEvent, false);
		document.addEventListener("dragover", dragOverEvent, false);
		window.addEventListener("resize", resizeDocument);
    }
    
    start(): void {
    	INScore.postMessage ("/ITL/scene", ["new"]);
    	this.fTimer = setTimeout (this._timetask(), this.fAppl.getRate()) ;		
    }

    stop(): void {
    	INScore.postMessage ("/ITL", ["quit"]);
    	clearTimeout (this.fTimer) ;		
    }

	timetask() : void {
		ViewUpdater.update (this.fAppl);
		this.fAppl.cleanup();
    	this.fTimer = setTimeout (this._timetask(), this.fAppl.getRate()) ;		
	}
    _timetask()	: TTimerTask 		{ return () => this.timetask(); };
}
