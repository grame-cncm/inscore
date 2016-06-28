
///<reference path="IMessage.ts"/>
///<reference path="../inscore.ts"/>
///<reference path="../globals.ts"/>
///<reference path="../model/IAppl.ts"/>
///<reference path="../events/documentEvents.ts"/>
///<reference path="../view/ViewUpdater.ts"/>
///<reference path="../model/ModelUpdater.ts"/>

interface TTimerTask  	{ (): void; }

class IGlue { 
	protected fAppl: IAppl;
//	protected fTimer: number;		// this is to catch multiple defs in nodes and in browser contexts
	protected fTimerView: any;			// should find a typed solution
	protected fTimerModel: any;

    constructor() 			{ 
    	this.fAppl = new IAppl(); 
    	let inscore = new INScore(this.fAppl);
    }

    initEventHandlers(): void {
		document.addEventListener("dragover", inscore_dragOverEvent, false);
		window.addEventListener("resize", inscore_resizeDocument);
    }
    
    start(scene?: string): void {
		let target = "/ITL/scene";
    	if (scene) 
    		target = "/ITL/" + scene;
    	INScore.postMessage (target, ["new"]);
		
		this.fTimerModel = setTimeout (this._timetaskModel(), this.fAppl.getModelRate()) ;
		if (gCreateView)
	    	this.fTimerView = setTimeout (this._timetaskView(), this.fAppl.getViewRate()) ;		
    }

    stop(): void {
    	INScore.postMessage ("/ITL", ["quit"]);
    	clearTimeout (this.fTimerView) ;		
    }

	timetaskModel() : void {
		ModelUpdater.update(INScore.getStack());    	
		this.fTimerModel = setTimeout (this._timetaskModel(), this.fAppl.getModelRate()) ;				
	}

	timetaskView() : void {
		ViewUpdater.update (this.fAppl);		
		let a = new IObjectTreeApply();
		a.applyCleanup (this.fAppl);
    	this.fTimerView = setTimeout (this._timetaskView(), this.fAppl.getViewRate()) ;		
	}
    _timetaskView()	: TTimerTask 		{ return () => this.timetaskView(); };
    _timetaskModel(): TTimerTask 		{ return () => this.timetaskModel(); };
}
