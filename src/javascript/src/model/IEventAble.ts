
///<reference path="../inscore-interface.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/TInterval.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="../scripting/TEnv.ts"/>
///<reference path="../scripting/TMessageEvaluator.ts"/>
///<reference path="Methods.ts"/>

interface TAttributesTable 		{ [index: string]: any; }
interface TRawMessage 			{ address: string; params: Array<any> }

type TStringEventsTable =       { [index: string]: IMessageList };
type TTimeEventValue 	=       { find: boolean, event?: TTimeEvent };

//-----------------------------------------------------------------------------------
class TTimeEvent  {
	fInterval : NumberInterval;
	fMsgs :		IMessageList = [];

	constructor(interval: NumberInterval, msgs: IMessageList) { 
		this.fInterval = interval;
		this.fMsgs = msgs;
	}
	toMessage (addr: string, event: string ) : IMessage { return new IMessage (addr, [event, ]); }
};

//-----------------------------------------------------------------------------------
class TTimeEventsTable {
	private fTable: Array<TTimeEvent>
			fEvent: string;

	constructor (arg: string | TTimeEventsTable) { 
		if (typeof arg === "string") {
			this.fEvent = arg; 
			this.fTable = [];
		}
		else {
			let tbl = <TTimeEventsTable>arg;
			this.fEvent = tbl.fEvent; 
			this.fTable = tbl.fTable.slice(0);
		}
	}
	clear(): void				{ this.fTable = []; }
	size(): number				{ return this.fTable.length; }

	getIndex (interval: NumberInterval): { find: boolean, index?: number } {
		for (var i=0; i < this.fTable.length; i++)
			if (interval.eq (this.fTable[i].fInterval)) return { find: true, index: i };
		return { find: false };
	}

	set (interval: NumberInterval, msgs: IMessageList): void {
		let i = this.getIndex (interval);
		let te = new TTimeEvent (interval, msgs);
		if (i.find) this.fTable[i.index] = te;
		else this.fTable.push (te);
	}

	contains (d: number):  TTimeEventValue {
		for (var i=0; i < this.fTable.length; i++)
			if (this.fTable[i].fInterval.includeLocation(d)) return { find: true, event: this.fTable[i] };
		return { find: false };
	}
	
	toMsgs (addr: string) : IMessageList {
		let out: IMessageList = [];
		for (var i=0; i < this.fTable.length; i++) {
			let event = this.fTable[i];
			if (event && event.fMsgs.length) {
				for (var n=0; n < event.fMsgs.length; n++) {
					let msg = event.fMsgs[n];
					let params : Array<any> = [ kwatch_GetSetMethod, this.fEvent];
					params = params.concat(event.fInterval.toArray());
					params = params.concat([ "(", msg.toString(), ");" ]);
					out.push ( new IMessage (addr, params) );
				}
			}
		}
		return out;
	}
};

//-----------------------------------------------------------------------------------
class InteractionState {
    //---------------------------------------------------------------
    // tables that associates events to messages
    //---------------------------------------------------------------
	fUserEvents: 		TStringEventsTable; 
	fInternalEvents:	TStringEventsTable;
	fAttributeEvents:	TStringEventsTable;
	fTimeEnterEvents:	TTimeEventsTable
	fTimeLeaveEvents:	TTimeEventsTable
	fDurEnterEvents: 	TTimeEventsTable
	fDurLeaveEvents: 	TTimeEventsTable

   //---------------------------------------------------------------
	constructor (state? : InteractionState) { 
		if (typeof state === "undefined") {
			this.fTimeEnterEvents	= new TTimeEventsTable("timeEnter");
			this.fTimeLeaveEvents	= new TTimeEventsTable("timeLeave");
			this.fDurEnterEvents	= new TTimeEventsTable("durEnter");
			this.fDurLeaveEvents	= new TTimeEventsTable("durLeave");
			this.clear();  
		}
		else {
			this.fUserEvents = {};
			this.fInternalEvents = {};
			this.fAttributeEvents = {};
			for (var key in state.fUserEvents)  	this.fUserEvents[key] = state.fUserEvents[key];
			for (var key in state.fInternalEvents)  this.fInternalEvents[key] = state.fInternalEvents[key];
			for (var key in state.fAttributeEvents) this.fAttributeEvents[key] = state.fAttributeEvents[key];
			
			this.fTimeEnterEvents	= new TTimeEventsTable (state.fTimeEnterEvents);
			this.fTimeLeaveEvents	= new TTimeEventsTable (state.fTimeLeaveEvents);
			this.fDurEnterEvents	= new TTimeEventsTable (state.fDurEnterEvents);
			this.fDurLeaveEvents	= new TTimeEventsTable (state.fDurLeaveEvents);
		}
	}
	
   //---------------------------------------------------------------
    getAttributeMsgs (attribute: string): IMessageList 	{ return this.fAttributeEvents[attribute]; }
    getTimeEnter (d: Fraction): TTimeEventValue 		{ return this.fTimeEnterEvents.contains(d.toNum()); }
    getTimeLeave (d: Fraction): TTimeEventValue 		{ return this.fTimeLeaveEvents.contains(d.toNum()); }
    getDurEnter (d: Fraction): TTimeEventValue 			{ return this.fDurEnterEvents.contains(d.toNum()); }
    getDurLeave (d: Fraction): TTimeEventValue 			{ return this.fDurLeaveEvents.contains(d.toNum()); }
    getMouseMsgs (type: string): IMessageList 			{ return this.fInternalEvents[type]; }
	
   //---------------------------------------------------------------
    clear (): void {
		this.fUserEvents 		= {} as TStringEventsTable;
		this.fInternalEvents 	= {} as TStringEventsTable;
		this.fAttributeEvents 	= {} as TStringEventsTable;
		this.fAttributeEvents["watch"] = null;		// this is for firefox !!!

		this.fTimeEnterEvents.clear();
		this.fTimeLeaveEvents.clear();
		this.fDurEnterEvents.clear();
		this.fDurLeaveEvents.clear();
    }

   //---------------------------------------------------------------
    event2TimeArray (event:string): { find: boolean, tbl?: TTimeEventsTable } {
		if (event === this.fTimeEnterEvents.fEvent) return { find: true, tbl: this.fTimeEnterEvents};
		if (event === this.fTimeLeaveEvents.fEvent) return { find: true, tbl: this.fTimeLeaveEvents};
		if (event === this.fDurEnterEvents.fEvent)  return { find: true, tbl: this.fDurEnterEvents};
		if (event === this.fDurLeaveEvents.fEvent)  return { find: true, tbl: this.fDurLeaveEvents};
		return { find: false };
    }

   	//---------------------------------------------------------------
    getWatch(addr: string): IMessageList	{ 
		let out: IMessageList = [];
		out = out.concat ( this.makeMsgs (this.fInternalEvents, addr) );
		out = out.concat ( this.makeMsgs (this.fAttributeEvents, addr) );
		out = out.concat ( this.makeMsgs (this.fUserEvents, addr) );
		out = out.concat ( this.fTimeEnterEvents.toMsgs (addr) );
		out = out.concat ( this.fTimeLeaveEvents.toMsgs (addr) );
		out = out.concat ( this.fDurEnterEvents.toMsgs (addr) );
		out = out.concat ( this.fDurLeaveEvents.toMsgs (addr) );
		if (!out.length)
			out.push (new IMessage (addr, [kwatch_GetSetMethod]));
    	return out; 
    }

   //---------------------------------------------------------------
    hasUIEvents (): number {
		var efield = 0;
    	for (var i=0; i <  IEventAble.fUIEvents.length; i++) {
			let msgs: Array<IMessage> = this.fInternalEvents[IEventAble.fUIEvents[i]];
			if (msgs && msgs.length) efield |= 1 << i;
    	}
    	return efield;
    }
	
   //---------------------------------------------------------------
	private makeMsgs (tbl: TStringEventsTable, addr: string) : IMessageList {
		let out: IMessageList = [];
		for (var key in tbl) {
			let msg = tbl[key];
			if (msg) {
				let params : Array<any> = [ kwatch_GetSetMethod, key, "(", msg.toString(), ");"  ];
				out.push ( new IMessage (addr, params) );
			}
		}
		return out;
	} 
}

//-----------------------------------------------------------------------------------
class IEventAble {

    //---------------------------------------------------------------
    // events definitions
    //---------------------------------------------------------------
	// WARNING: changing the events order requires to change the eUIEvents enum too
	static fUIEvents	: Array<string> 		= [ "mouseDown", "mouseMove", "mouseUp", 
													"mouseEnter", "mouseLeave",
													"doubleClick",
													"touchBegin", "touchEnd", "touchUpdate"];
	protected fAttributesNames: Array<string> 	= [ ];
	protected fSpecificEvents: Array<string> 	= [ "newData" ];

    private fState: InteractionState;				// the current interaction state
    private fStatesStack: Array<InteractionState>;	// the interaction states stack
	
    //---------------------------------------------------------------
	constructor () {  this.fState = new InteractionState(); this.fStatesStack = []; }

	specifics (evslist: Array<string>) 	{ this.fSpecificEvents = this.fSpecificEvents.concat(evslist); }
	attributes (a: TAttributesTable) 	{ for (var key in a)  this.fAttributesNames.push(key); }

    //---------------------------------------------------------------
    // check the type of an event
    specificEvent 	(event: string): boolean 	{ return IEventAble.find (this.fSpecificEvents, event); }
    attributeEvent 	(event: string): boolean 	{ return IEventAble.find (this.fAttributesNames, event); }

    //---------------------------------------------------------------
    // give the active UI events as a bit field
    hasUIEvents (): number { return this.fState.hasUIEvents(); }

     //---------------------------------------------------------------
    // interface for triggering events 
    //---------------------------------------------------------------
    handleAttributeChange (attribute: string): void {
    	let msgs = this.fState.getAttributeMsgs (attribute);
    	if (msgs && msgs.length)  this.send ( msgs );
    }
	
	checkTimeEvent(ev: TTimeEvent, d: number) : void {
		if (!ev.fInterval.includeLocation(d)) {
	    	let msgs = ev.fMsgs;
    		if (msgs && msgs.length)  this.send ( msgs );
		}
	}
	
	handleTimeChange(d1: Fraction, d2: Fraction) : void {
		let t = this.fState.getTimeEnter (d2);
		if (t.find) this.checkTimeEvent(t.event, d1.toNum());
		else {
			t = this.fState.getTimeLeave (d1);
			if (t.find)  this.checkTimeEvent(t.event, d2.toNum())
		}
	}
	
	handleDurChange(d1: Fraction, d2: Fraction) : void {
		let t = this.fState.getDurEnter (d2);
		if (t.find) this.checkTimeEvent(t.event, d1.toNum());
		else {
			t = this.fState.getDurLeave (d1);
			if (t.find)  this.checkTimeEvent(t.event, d2.toNum())
		}
	}
	
	private event2evStr (ev: eUIEvents) : string { 
		switch (ev) {
			case eUIEvents.kMouseDown: 		return IEventAble.fUIEvents[0];
			case eUIEvents.kMouseMove: 		return IEventAble.fUIEvents[1];
			case eUIEvents.kMouseUp: 		return IEventAble.fUIEvents[2];
			case eUIEvents.kMouseEnter: 	return IEventAble.fUIEvents[3];
			case eUIEvents.kMouseLeave: 	return IEventAble.fUIEvents[4];
			case eUIEvents.kDoubleClick: 	return IEventAble.fUIEvents[5];
			case eUIEvents.kTouchBegin: 	return IEventAble.fUIEvents[6];
			case eUIEvents.kTouchEnd: 		return IEventAble.fUIEvents[7];
			case eUIEvents.kTouchUpdate: 	return IEventAble.fUIEvents[8];
		}
		return ""; 
	}
	handleMouseEvent (type: eUIEvents, env: TEnv) : void {
		let str = this.event2evStr (type);
    	let msgs = this.fState.getMouseMsgs (str);
    	if (msgs && msgs.length) 
			this.evalAndSend ( msgs, env );
	}
	
   //---------------------------------------------------------------
    // interface for messages handling
    //---------------------------------------------------------------
	// WATCH METHOD
    //---------------------------------------------------------------
    watch (msg:IMessage): eMsgStatus {
    	let n = msg.size() - 1;				// first param is 'watch'
    	if (!n) {
    		this.fState.clear();			// no parameter: clear the interaction state
    		return  eMsgStatus.kProcessed;
    	}

		let event = msg.paramStr(1);
		if (!event.correct) return eMsgStatus.kBadParameters;
		if (n == 1) 								// no associated message
			return this.clear1Event (event.value);	// clear the corresponding event

		if (n == 2) {
	    	let arg = msg.paramArray (2);
			let a = this.event2StringArray (event.value);
	    	if (arg.correct && a.find) {
				let msgs = this.msg2msgsArray (arg.value);
				if (msgs.length) {
					a.tbl[event.value] = msgs;
					return eMsgStatus.kProcessed;
				}
			}
		}
		else return this.timewatch (event.value, msg);
		return eMsgStatus.kBadParameters;
    }

    //---------------------------------------------------------------
    // internal event msg handling
    private ievent (ev: string, env: TEnv): eMsgStatus {
	    let a = this.event2StringArray (ev);			// look for the table containing the event
	    if (a.find) {
	    	let msgs = a.tbl[ev];
	    	if (msgs && msgs.length) {					// check if the event is set
				this.evalAndSend ( msgs, env);			// request to eval and send the messages
			}
	    }
		else return eMsgStatus.kBadParameters;			// there is no support for time events at this level
		return eMsgStatus.kProcessedNoChange;
    }

    //---------------------------------------------------------------
    // EVENT METHOD
    //---------------------------------------------------------------
    event (msg:IMessage): eMsgStatus {
    	let ui = this.hasUIEvents();
    	if ( msg.size() < 2) return eMsgStatus.kBadParameters;

    	let event = msg.paramStr(1);
    	if (!event.correct) return eMsgStatus.kBadParameters;
    	
    	let m : TMouseEnv; let d: Fraction;
    	let env = new TEnv (msg.address(), m, d, d, msg.params().slice(2));
 	    return this.ievent (event.value, env);
    }

	// GET WATCH METHOD
	//--------------------------------------------------------------    
    getWatch(addr: string): IMessageList	{  return this.fState.getWatch (addr); }

	// PUSH & POP METHOD
	//--------------------------------------------------------------    
    push(): void	{
    	let copy = new InteractionState (this.fState);
    	this.fStatesStack.push (copy);
    }
    pop(): void		{ 
    	if (this.fStatesStack.length)
    		this.fState = this.fStatesStack.pop();
    }

	//--------------------------------------------------------------    
	// STATIC METHODS
	//--------------------------------------------------------------    
    static find(a: Array<string>, s: string) : boolean { 
    	for (var i=0; i < a.length; i++) if (a[i] === s) return true;
    	return false; 
    }

    //---------------------------------------------------------------
    // check if an event is a user defined event
    static userEvent (event: string): boolean {
		let regexp = new RegExp("^[A-Z][A-Z0-9]*$");
		return regexp.test(event);
    }
    static uiEvent 	(event: string): boolean 	{ return IEventAble.find(IEventAble.fUIEvents, event); }

// PRIVATE METHOD
//--------------------------------------------------------------    
    
    //---------------------------------------------------------------
    private send (msgs: Array<IMessage>): void {
		msgs.forEach ( function(msg: IMessage) { INScore.postMessage (msg.address(), msg.params()) })
    }
    private evalAndSend (msgs: Array<IMessage>, env: TEnv): void {
    	let me = new TMessageEvaluator(env);
    	msgs = me.eval(msgs);
		msgs.forEach( function(msg: IMessage) { INScore.postMessage (msg.address(), msg.params()) })
    }
        
    //---------------------------------------------------------------
    private event2StringArray (event:string): { find: boolean, tbl?: TStringEventsTable } {
		if (IEventAble.uiEvent(event)) 		return { find: true, tbl: this.fState.fInternalEvents};
		if (IEventAble.userEvent(event)) 	return { find: true, tbl: this.fState.fUserEvents};
		if (this.attributeEvent(event)) 	return { find: true, tbl: this.fState.fAttributeEvents};
		if (this.attributeEvent(event)) 	return { find: true, tbl: this.fState.fAttributeEvents};
		return { find: false };
    }
    //---------------------------------------------------------------
    private msg2msgsArray (list: Array<any>):  IMessageList {
    	let out : IMessageList = []
    	for (var i=0; i < list.length; i++) {
 	    	let m = <TRawMessage>list[i];
	    	out.push (new IMessage (m.address.toString(), m.params));
  		}
		return out;
    }

    //---------------------------------------------------------------
    // clear a single event
    private clear1Event (event: string): eMsgStatus {
		let a = this.event2StringArray (event);
	    if (a.find)						// look for a string indexed table
	    	a.tbl[event] = [];			// clear the corresponding entry
	    else {
	    	let t = this.fState.event2TimeArray (event);
	    	if (t.find)					// look for a time table
		    	t.tbl.clear();			// clear the corresponding table
		    else return eMsgStatus.kBadParameters; 
	    }
		return eMsgStatus.kProcessed;
    }

    //---------------------------------------------------------------
    // look for time intervals in the message parameters
    private params2intervals (msg:IMessage): { argi: number, interval?: TimeInterval } {
		let n = msg.size() - 2; 	// first param is watch, second is the event name

		// we're expecting a time interval sepcified as "n1/d1" "n2/d2" | start end | n1 d1 n2 d2
		// followed by an array that is actually the raw messages list
		// i.e. an args count of 3 or 5
		if (n == 5) {
			let n1 = msg.paramNum (2);
			let d1 = msg.paramNum (3);
			let n2 = msg.paramNum (4);
			let d2 = msg.paramNum (5);
			if (n1.correct && n2.correct && d1.correct && d2.correct)
				return { argi: 6, interval: new TimeInterval(new Fraction(n1.value, d1.value), new Fraction(n2.value, d2.value)) };
		}
		else if (n == 3) {
			let start 	= msg.paramNum (2);
			let end 	= msg.paramNum (3);
			let startStr= msg.paramStr (2);
			let endStr 	= msg.paramStr (3);
			if (start.correct && end.correct)
				return { argi: 4, interval: new TimeInterval(new Fraction(start.value,1), new Fraction(end.value,1)) };
			else if (startStr.correct && endStr.correct)
				return { argi: 4, interval: new TimeInterval(new Fraction(startStr.value), new Fraction(endStr.value)) };
		}
		return { argi: 0 };
    }
    
    //---------------------------------------------------------------
    // internal method for time watch msg  handling
    // param event: the event name, decoded by watch
    //---------------------------------------------------------------
    private timewatch (event: string, msg:IMessage): eMsgStatus {
	    let a = this.fState.event2TimeArray (event);
	    let i = this.params2intervals (msg);
	    if (a.find && i.argi) {
	    	let arg = msg.paramArray (i.argi);
	    	if (arg.correct) {
				let msgs = this.msg2msgsArray (arg.value);
				if (msgs.length) {
					a.tbl.set (i.interval.toNumInterval(), msgs);
					return eMsgStatus.kProcessed;
				}
	    	}
	    }
		return eMsgStatus.kBadParameters; 
    }
}
