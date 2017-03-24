
//<reference path="../inscore.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="Methods.ts"/>

interface TAttributesTable 		{ [index: string]: any; }
interface TStringEventsTable 	{ [index: string]: Array<IMessage>; }
interface TTimeEventsTable 		{ [index: number]: Array<IMessage>; }
interface TEventSender 			{ postMessage (address: string, params: Array<any>) : void; }

interface TRawMessage 			{ address: string; params: Array<any> }

var INScore : INScoreInterface;

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
    private clear (): void {
		this.fUserEvents 		= {} as TStringEventsTable;
		this.fInternalEvents 	= {} as TStringEventsTable;
		this.fAttributeEvents 	= {} as TStringEventsTable;

		this.fTimeEnterEvents 	= {} as TTimeEventsTable;
		this.fTimeLeaveEvents 	= {} as TTimeEventsTable;
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
    private msg2msgsArray (list: Array<any>):  Array<IMessage> {
    	let out : Array<IMessage> = []
    	for (var i=0; i < list.length; i++) {
			console.log ("msg2msgsArray  -> " + list[i]);
 	    	let m = <TRawMessage>list[i];
	    	let address = m.address;
	    	let params = m.params;
	    	out.push (new IMessage (address.toString(), params));
 		    console.log ("  -> address: " + address + " : " + params );
  		}
		return out;
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
				else if (n== 2) {				// a single array of messages is expected
	    			let arg = msg.paramArray (2);
	    			if (arg.correct) {
						let msgs = this.msg2msgsArray (arg.value);
						if (msgs.length) {
							a.tbl[event.value] = msgs;
							return eMsgStatus.kProcessedNoChange;
						}
					}
					return eMsgStatus.kBadParameters; 
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
