
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
	protected fTimerTask: any;			// should find a typed solution
	private   fStack: Array<IMessage>;

    constructor() 			{ 
    	this.fAppl = new IAppl(); 
    	let inscore = new INScore(this.fAppl);
		this.fStack = new Array<IMessage>();
    }

	getStack(): Array<IMessage> 	{ return this.fStack; }
	popStack(): IMessage 			{ return this.fStack.shift(); }
	setStack(msg: IMessage): void 	{ this.fStack.push(msg); }

    initEventHandlers(): void {
		//document.addEventListener("dragover", inscore_dragOverEvent, false);
		window.addEventListener("resize", inscore_resizeDocument);
    }
    
    start(scene?: string): void {
		let target = "/ITL/scene";
    	if (scene) 
    		target = "/ITL/" + scene;
    	INScore.postMessage (target, ["new"]);
		
		if (gCreateView)
	    	this.fTimerTask = setTimeout (this._timetask(), this.fAppl.getTaskRate()) ;		
    }

    stop(): void {
    	INScore.postMessage ("/ITL", ["quit"]);
    	clearTimeout (this.fTimerTask) ;		
    }

	timetask() : void {
		ModelUpdater.update(this.getStack());		
		ViewUpdater.update (this.fAppl);		
		let a = new IObjectTreeApply();
		a.applyCleanup (this.fAppl);
    	this.fTimerTask = setTimeout (this._timetask(), this.fAppl.getTaskRate()) ;		
	}
    _timetask()	: TTimerTask 			{ return () => this.timetask(); };
}
