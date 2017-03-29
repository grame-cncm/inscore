
///<reference path="IMessage.ts"/>
///<reference path="../globals.ts"/>
///<reference path="../model/IAppl.ts"/>
///<reference path="../events/documentEvents.ts"/>
///<reference path="../view/ViewUpdater.ts"/>
///<reference path="../model/ModelUpdater.ts"/>

interface TTimerTask  	{ (): void; }

class IGlue { 
	private   fCurrentTime: number;

	protected fAppl: IAppl;
	protected fTimer: number;		// this is to catch multiple defs in nodes and in browser contexts
	private   fStack: Array<IMessage>;
	private   fModelUpdater: ModelUpdater;

    constructor() 			{ 
    	this.fAppl = new IAppl();
		this.fStack = new Array<IMessage>();
		this.fModelUpdater = new ModelUpdater(this.fAppl);
		this.fCurrentTime = 0;
    }

	getStack(): Array<IMessage> 	{ return this.fStack; }
	popStack(): IMessage 			{ return this.fStack.shift(); }
	setStack(msg: IMessage): void 	{ this.fStack.push(msg); }

    initEventHandlers(): void {
		//document.addEventListener("dragover", inscore_dragOverEvent, false);
		window.addEventListener("resize", inscore_resizeDocument);
    }
    
    start(scene: string, position: string): void {
    	let target = "/ITL/" + scene;
    	INScore.postMessage (target, ["new"]);
    	INScore.postMessage (target, ["position", position]);	
		if (gCreateView)
	    	this.fTimer = setTimeout (this._timetask(), this.fAppl.getRate()) ;		
    }

    stop(): void {
    	INScore.postMessage ("/ITL", ["quit"]);
    	clearTimeout (this.fTimer) ;		
    }

    getRoot(): IAppl { return this.fAppl; }

	timetask() : void {
		let d= new Date();
		let now = d.getTime();
		if (this.fCurrentTime)
			IAppl.fRealRate = now - this.fCurrentTime;
		this.fCurrentTime = now;
		let stack = this.fStack;
		this.fStack = [];
		this.fModelUpdater.update (stack);
		ViewUpdater.update (this.fAppl);
		IObject.timeTaskCleanup (this.fAppl);
    	this.fTimer = setTimeout (this._timetask(), this.fAppl.getRate()) ;		
	}
    _timetask()	: TTimerTask 			{ return () => this.timetask(); };
}
