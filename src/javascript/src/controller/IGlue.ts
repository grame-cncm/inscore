
///<reference path="IMessage.ts"/>
///<reference path="../globals.ts"/>
///<reference path="../model/IAppl.ts"/>
///<reference path="../events/documentEvents.ts"/>
///<reference path="../view/ViewUpdater.ts"/>

interface TTimerTask  	{ (): void; }

class IGlue { 
	protected fAppl: IAppl;
//	protected fTimer: number;		// this is to catch multiple defs in nodes and in browser contexts
	protected fTimer: any;			// should find a typed solution
	
    constructor() 			{ 
    	this.fAppl = new IAppl(); 
    }

    initEventHandlers(): void {
		document.addEventListener("drop", dropEvent, false);
		document.addEventListener("dragover", dragOverEvent, false);
		window.addEventListener("resize", resizeDocument);
    }
    
    start(scene?: string): void {
		let target = "/ITL/scene";
    	if (scene) 
    		target = "/ITL/" + scene;
    	INScore.postMessage (target, ["new"]);
		if (gCreateView)
	    	this.fTimer = setTimeout (this._timetask(), this.fAppl.getRate()) ;		
    }

    stop(): void {
    	INScore.postMessage ("/ITL", ["quit"]);
    	clearTimeout (this.fTimer) ;		
    }

    getRoot(): IAppl { return this.fAppl; }

	timetask() : void {
		ViewUpdater.update (this.fAppl);
		IObject.timeTaskCleanup (this.fAppl);
    	this.fTimer = setTimeout (this._timetask(), this.fAppl.getRate()) ;		
	}
    _timetask()	: TTimerTask 		{ return () => this.timetask(); };
}
