
///<reference path="../inscore-interface.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="Methods.ts"/>

interface TAttributesTable 		{ [index: string]: any; }
interface TRawMessage 			{ address: string; params: Array<any> }

type TStringEventsTable = { [index: string]: IMessageList };
type TTimeEventsTable   = { [index: string]: IMessageList };

class IEventAble {

    //---------------------------------------------------------------
    // events definitions
    //---------------------------------------------------------------
	protected static fTimeEvents: Array<string> = ["timeEnter", "timeLeave"];
	protected static fDurEvents	: Array<string> = ["durEnter", "durLeave"];

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
	
    //---------------------------------------------------------------
	constructor () 						{ this.clear(); }
	specifics (evslist: Array<string>) 	{ this.fSpecificEvents.concat(evslist); }
	attributes (a: TAttributesTable) 	{ for (var key in a)  this.fAttributesEvents.push(key); }

    //---------------------------------------------------------------
    // check the type of an event
    specificEvent 	(event: string): boolean 	{ return IEventAble.find (this.fSpecificEvents, event); }
    attributeEvent 	(event: string): boolean 	{ return IEventAble.find (this.fAttributesEvents, event); }


    //---------------------------------------------------------------
    // give the UI events set as a bit field
    hasUIEvents (): number {
		var efield = 0;
    	for (var i=0; i <  IEventAble.fUIEvents.length; i++) {
			let msgs: Array<IMessage> = this.fInternalEvents[IEventAble.fUIEvents[i]];
			if (msgs && msgs.length)
    			efield |= 1 << i;
    	}
    	return efield;
    }

    //---------------------------------------------------------------
    watch (msg:IMessage): eMsgStatus {
    	let n = msg.size() - 1;			// first param is 'watch'
    	if (!n)  this.clear();			// no parameter: clear the tables
    	else {
    		let event = msg.paramStr(1);
	    	if (!event.correct) return eMsgStatus.kBadParameters;
	    	let a = this.event2StringArray (event.value);
	    	if (a.find) {
	    		if (n == 1) 					// no associated message
	    			a.tbl[event.value] = [];	// clear the corresponding entry
				else if (n== 2) {				// otherwise a single array of messages is expected
	    			let arg = msg.paramArray (2);
	    			if (arg.correct) {
						let msgs = this.msg2msgsArray (arg.value);
						if (msgs.length) {
							a.tbl[event.value] = msgs;
							return eMsgStatus.kProcessed;
						}
					}
					return eMsgStatus.kBadParameters; 
				}
	    	}
	    	else {
	    		// check for time events
	    	}
	    }
		return eMsgStatus.kProcessed;
    }

    //---------------------------------------------------------------
    // internal events handling
    ievent (ev: string, args: Array<any>): eMsgStatus {
	    let a = this.event2StringArray (ev);			// look for the table containing the event
	    if (a.find) {
	    	let msgs = a.tbl[ev];
	    	if (msgs && msgs.length) {					// check if the event is set
				this.send ( msgs );						// and the associated messages if any
			}
	    }
		else return eMsgStatus.kBadParameters;
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
	makeMsgs (tbl: TStringEventsTable, addr: string) : IMessageList {
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
    static timeEvent(event: string): boolean 	{ return IEventAble.find(IEventAble.fTimeEvents, event); }
    static durEvent (event: string): boolean 	{ return IEventAble.find(IEventAble.fDurEvents, event); }


// PRIVATE METHOD
//--------------------------------------------------------------    
     private clear (): void {
		this.fUserEvents 		= {};
		this.fInternalEvents 	= {};
		this.fAttributeEvents 	= {};
		this.fTimeEnterEvents 	= {};
		this.fTimeLeaveEvents 	= {};
    }
    
    //---------------------------------------------------------------
    private send (msgs: Array<IMessage>): void {
		msgs.forEach(function(msg: IMessage) { INScore.postMessage (msg.address(), msg.params()) })
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
	    	let address = m.address;
	    	let params = m.params;
	    	out.push (new IMessage (address.toString(), params));
  		}
		return out;
    }
}
