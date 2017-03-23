
//<reference path="../inscore.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="Methods.ts"/>

interface TUserEventsTable 		{ [index: string]: Array<IMessage>; }
interface TInternalEventsTable 	{ [index: string]: Array<IMessage>; }
interface TAttributeEventsTable { [index: string]: Array<IMessage>; }

class IEventAble {
	protected fUserEvents: 		TUserEventsTable; 
	protected fInternalEvents:  TInternalEventsTable;
	protected fAttributeEvents: TAttributeEventsTable;
	protected fTimeEnterEvents: Array<Array<IMessage>>
	protected fTimeLeaveEvents: Array<Array<IMessage>>
	
	constructor () { this.clear(); }
    
    protected clear (): void {
		this.fUserEvents 		= {} as TUserEventsTable;
		this.fInternalEvents 	= {} as TInternalEventsTable;
		this.fAttributeEvents 	= {} as TAttributeEventsTable;

		this.fTimeEnterEvents 	= [];
		this.fTimeLeaveEvents 	= [];
    }
    
    protected send (msgs: Array<IMessage>): void {
console.log ("IEventAble send: ")
		msgs.forEach(function(msg: IMessage) { console.log(" -> " + msg); })
    }
    
    // check if an event is a user defined event
    static userEvent (event: string): boolean {
		let regexp = new RegExp("^[A-Z][A-Z0-9]*$");
		return regexp.test(event);
    }
    
    watch (msg:IMessage): eMsgStatus {
    	let n = msg.size() - 1;				// first param is 'watch'
console.log ("IEventAble watch " + n);
    	if (!n) {
    		this.clear();		// no parameter: clear the tables
    	}
    	else {
    		let event = msg.paramStr(1);
	    	if (!event.correct) return eMsgStatus.kBadParameters;
			if (IEventAble.userEvent(event.value)) {
				this.fUserEvents[event.value] = [ new IMessage ("/ITL/userEvent", msg.params().slice(1)) ];
			}
	    }
		return eMsgStatus.kProcessedNoChange;
    }

    event (msg:IMessage): eMsgStatus {
    	let n = msg.size() - 1;				// first param is 'event'
    	if (!msg.size()) return eMsgStatus.kBadParameters;
    	let event = msg.paramStr(1);
    	if (!event.correct) return eMsgStatus.kBadParameters;
		
console.log ("IEventAble event " + event.value);
		let msgs: Array<IMessage>;
		if (IEventAble.userEvent(event.value))
			msgs = this.fUserEvents[event.value]; 
		else {
			msgs = this.fAttributeEvents[event.value]; 
			if (!msgs) 
				msgs = this.fInternalEvents[event.value]; 
		}
		if (!msgs) return eMsgStatus.kBadParameters;
		this.send ( msgs );
		return eMsgStatus.kProcessedNoChange;
    }

}
