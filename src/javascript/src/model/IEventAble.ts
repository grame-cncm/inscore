
///<reference path="../inscore-interface.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/TInterval.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="Methods.ts"/>

interface TAttributesTable 		{ [index: string]: any; }
interface TRawMessage 			{ address: string; params: Array<any> }

type TStringEventsTable =       { [index: string]: IMessageList };

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
	fTable: Array<TTimeEvent>
	fEvent: string;

	constructor (event: string) { this.fEvent = event; this.fTable = [] }
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
class IEventAble {

    //---------------------------------------------------------------
    // events definitions
    //---------------------------------------------------------------
	// WARNING: changing the events order requires to change the eUIEvents enum too
	protected static fUIEvents	: Array<string> = [ "mouseDown", "mouseMove", "mouseUp", 
													"mouseEnter", "mouseLeave",
													"doubleClick",
													"touchBegin", "touchEnd", "touchUpdate"];
	protected fAttributesEvents: Array<string> 	= [ ];
	protected fSpecificEvents: Array<string> 	= [ "newData" ];

    //---------------------------------------------------------------
    // tables that associates events to messages
    //---------------------------------------------------------------
	protected fUserEvents: 		TStringEventsTable; 
	protected fInternalEvents:  TStringEventsTable;
	protected fAttributeEvents: TStringEventsTable;
	protected fTimeEnterEvents: TTimeEventsTable
	protected fTimeLeaveEvents: TTimeEventsTable
	protected fDurEnterEvents: 	TTimeEventsTable
	protected fDurLeaveEvents: 	TTimeEventsTable
	
    //---------------------------------------------------------------
	constructor () {  
		this.fTimeEnterEvents	= new TTimeEventsTable("timeEnter");
		this.fTimeLeaveEvents	= new TTimeEventsTable("timeLeave");
		this.fDurEnterEvents	= new TTimeEventsTable("durEnter");
		this.fDurLeaveEvents	= new TTimeEventsTable("durLeave");
		this.clear();  
	}
	specifics (evslist: Array<string>) 	{ this.fSpecificEvents = this.fSpecificEvents.concat(evslist); }
	attributes (a: TAttributesTable) 	{ for (var key in a)  this.fAttributesEvents.push(key); }

    //---------------------------------------------------------------
    // check the type of an event
    specificEvent 	(event: string): boolean 	{ return IEventAble.find (this.fSpecificEvents, event); }
    attributeEvent 	(event: string): boolean 	{ return IEventAble.find (this.fAttributesEvents, event); }

    //---------------------------------------------------------------
    // give the active UI events as a bit field
    hasUIEvents (): number {
		var efield = 0;
    	for (var i=0; i <  IEventAble.fUIEvents.length; i++) {
			let msgs: Array<IMessage> = this.fInternalEvents[IEventAble.fUIEvents[i]];
			if (msgs && msgs.length) efield |= 1 << i;
    	}
    	return efield;
    }

    //---------------------------------------------------------------
    watch (msg:IMessage): eMsgStatus {
    	let n = msg.size() - 1;				// first param is 'watch'
    	if (!n) {
    		this.clear();					// no parameter: clear all the tables
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
    //---------------------------------------------------------------
    // internal event msg handling
    private ievent (ev: string, args: Array<any>): eMsgStatus {
	    let a = this.event2StringArray (ev);			// look for the table containing the event
	    if (a.find) {
	    	let msgs = a.tbl[ev];
	    	if (msgs && msgs.length) {					// check if the event is set
				this.send ( msgs );						// and the associated messages if any
			}
	    }
		else return eMsgStatus.kBadParameters;			// there is no support for time events at this level
		return eMsgStatus.kProcessedNoChange;
    }

    //---------------------------------------------------------------
    // event msg handling
    event (msg:IMessage): eMsgStatus {
    	let ui = this.hasUIEvents();
    	if (msg.size() < 2) return eMsgStatus.kBadParameters;
    	let event = msg.paramStr(1);
    	if (!event.correct) return eMsgStatus.kBadParameters;
	    return this.ievent (event.value, msg.params().slice(2));
    }

// GET WATCH METHOD
//--------------------------------------------------------------    
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

	// gives the messages parameters only, msg addressing is IObject responsibility 
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
     private clear (): void {
		this.fUserEvents 		= {};
		this.fInternalEvents 	= {};
		this.fAttributeEvents 	= {};

		this.fTimeEnterEvents.clear();
		this.fTimeLeaveEvents.clear();
		this.fDurEnterEvents.clear();
		this.fDurLeaveEvents.clear();
    }
    
    //---------------------------------------------------------------
    private send (msgs: Array<IMessage>): void {
		msgs.forEach(function(msg: IMessage) { INScore.postMessage (msg.address(), msg.params()) })
    }
    
    //---------------------------------------------------------------
    private event2TimeArray (event:string): { find: boolean, tbl?: TTimeEventsTable } {
		if (event === this.fTimeEnterEvents.fEvent) return { find: true, tbl: this.fTimeEnterEvents};
		if (event === this.fTimeLeaveEvents.fEvent) return { find: true, tbl: this.fTimeLeaveEvents};
		if (event === this.fDurEnterEvents.fEvent)  return { find: true, tbl: this.fDurEnterEvents};
		if (event === this.fDurLeaveEvents.fEvent)  return { find: true, tbl: this.fDurLeaveEvents};
		return { find: false };
    }
    
    //---------------------------------------------------------------
    private event2StringArray (event:string): { find: boolean, tbl?: TStringEventsTable } {
		if (IEventAble.uiEvent(event)) 		return { find: true, tbl: this.fInternalEvents};
		if (IEventAble.userEvent(event)) 	return { find: true, tbl: this.fUserEvents};
		if (this.attributeEvent(event)) 	return { find: true, tbl: this.fAttributeEvents};
		if (this.attributeEvent(event)) 	return { find: true, tbl: this.fAttributeEvents};
		return { find: false };
    }

    //---------------------------------------------------------------
    private msg2msgsArray (list: Array<any>):  IMessageList {
    	let out : IMessageList = []
    	for (var i=0; i < list.length; i++) {
 	    	let m = <TRawMessage>list[i];
//	    	let address = m.address;
//	    	let params = m.params;
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
	    	let t = this.event2TimeArray (event);
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
	    let a = this.event2TimeArray (event);
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
