
//<reference path="../inscore.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="Methods.ts"/>

interface TAttributesTable 		{ [index: string]: any; }
interface TStringEventsTable 	{ [index: string]: Array<IMessage>; }
interface TTimeEventsTable 		{ [index: number]: Array<IMessage>; }

class IEventAble {

    //---------------------------------------------------------------
    // events definitions
    //---------------------------------------------------------------
	protected static fTimeEvents: Array<string> = ["timeEnter", "timeLeave"];
	protected static fDurEvents	: Array<string> = ["durEnter", "durLeave"];
	protected static fUIEvents	: Array<string> = [ "mouseMove", "mouseUp", 
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
    static find(a: Array<string>, s: string) : boolean { 
    	for (var i=0; i < a.length; i++) if (a[i] === s) return true;
    	return false; 
    }

    //---------------------------------------------------------------
    // static methods
    //---------------------------------------------------------------
    // check if an event is a user defined event
    static userEvent (event: string): boolean {
		let regexp = new RegExp("^[A-Z][A-Z0-9]*$");
		return regexp.test(event);
    }
    static uiEvent 	(event: string): boolean 	{ return IEventAble.find(IEventAble.fUIEvents, event); }
    static timeEvent(event: string): boolean 	{ return IEventAble.find(IEventAble.fTimeEvents, event); }
    static durEvent (event: string): boolean 	{ return IEventAble.find(IEventAble.fDurEvents, event); }

    //---------------------------------------------------------------
    // check the type of an event
    specificEvent 	(event: string): boolean 	{ return IEventAble.find (this.fSpecificEvents, event); }
    attributeEvent 	(event: string): boolean 	{ return IEventAble.find (this.fAttributesEvents, event); }

    //---------------------------------------------------------------
    protected clear (): void {
		this.fUserEvents 		= {} as TStringEventsTable;
		this.fInternalEvents 	= {} as TStringEventsTable;
		this.fAttributeEvents 	= {} as TStringEventsTable;

		this.fTimeEnterEvents 	= {} as TTimeEventsTable;
		this.fTimeLeaveEvents 	= {} as TTimeEventsTable;
    }
    
    //---------------------------------------------------------------
    private send (msgs: Array<IMessage>): void {
console.log ("IEventAble send: ")
		msgs.forEach(function(msg: IMessage) { console.log(" -> " + msg); })
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
    private msg2msgsArray (msg: IMessage, startindex: number):  Array<IMessage> {
    	let n = msg.size();
    	let out : Array<IMessage> = []
    	console.log ("msg2msgsArray : " + (n - startindex) + " msgs")
    	for (var i=startindex; i < n; i++) {
	    	let arg = msg.paramArray (i);
	    	if (arg.correct) {
	    		let msg = arg.value;
			    console.log ("  -> " + msg);
	    		for (var j=0; j<msg.length; j++)
			    	console.log ("       " + msg[j]);
		    }
		    else 
		    	console.log ("incorrect argument: " + msg.param(i));
    	}
    	return out;
    }

    //---------------------------------------------------------------
    watch (msg:IMessage): eMsgStatus {
    	let n = msg.size() - 1;				// first param is 'watch'
console.log ("IEventAble watch " + n);
    	if (!n) {
    		this.clear();		// no parameter: clear the tables
    	}
    	else {
    		let event = msg.paramStr(1);
	    	if (!event.correct) return eMsgStatus.kBadParameters;
	    	let a = this.event2StringArray (event.value);
	    	if (a.find) {
	    		if (n == 1) 					// no massociated message
	    			a.tbl[event.value] = [];	// clear the corresponding entry
				else {
					let msgs = this.msg2msgsArray (msg, 2);
					a.tbl[event.value] = [ new IMessage ("/ITL/userEvent", msg.params().slice(1)) ];
				}
	    	}
	    	else {
	    		// check for time events
	    	}
	    }
		return eMsgStatus.kProcessedNoChange;
    }

    //---------------------------------------------------------------
    event (msg:IMessage): eMsgStatus {
    	let n = msg.size() - 1;								// first param is 'event'
    	if (!msg.size()) return eMsgStatus.kBadParameters;
    	let event = msg.paramStr(1);
    	if (!event.correct) return eMsgStatus.kBadParameters;
	    let a = this.event2StringArray (event.value);		// look for the table containing the event
	    if (a.find) {
	    	let msgs = a.tbl[event.value];
	    	if (msgs && msgs.length) {						// check if the event is set
				this.send ( msgs );
				return eMsgStatus.kProcessedNoChange;
			}
	    }
		return eMsgStatus.kBadParameters;
    }

}
