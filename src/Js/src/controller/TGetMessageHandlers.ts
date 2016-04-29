
///<reference path="IMessage.ts"/>
///<reference path="THandlersPrototypes.ts"/>
///<reference path="../externals/fraction/fraction.ts"/>

"use strict"

// ------------------------------------------------------------------------------
// put a single number in a message
// ------------------------------------------------------------------------------
class TGetMsgHandlerNum extends GetMsgHandler<GetNumMethod> {
    constructor(method: GetNumMethod) { super (method); }    
    put(msg: IMessage): IMessage { 
    	msg.add (this.fMethod ());
    	return msg;
    }
}

// ------------------------------------------------------------------------------
// put a single string in a message
// ------------------------------------------------------------------------------
class TGetMsgHandlerText extends GetMsgHandler<GetStringMethod> {
    constructor(method: GetStringMethod) { super (method); }    
    put(msg: IMessage): IMessage { 
    	msg.add (this.fMethod ());
    	return msg;
    }
}

// ------------------------------------------------------------------------------
// put a date in a message
// ------------------------------------------------------------------------------
class TGetMsgHandlerTime extends GetMsgHandler<GetTimeMethod> {
    constructor(method: GetTimeMethod) { super(method); }     
    put(msg: IMessage): IMessage { 
    	let d = this.fMethod ();
    	msg.add (d.getNumerator());
    	msg.add (d.getDenominator());
    	return msg;
    }
}

// ------------------------------------------------------------------------------
// put an array in a message
// ------------------------------------------------------------------------------
class TGetMsgHandlerArray extends GetMsgHandler<GetArrayMethod> {
    constructor(method: GetArrayMethod) { super(method); }     
    put(msg: IMessage): IMessage { 
    	msg.push (this.fMethod ());
    	return msg;
    }
}
