
///<reference path="IMessage.ts"/>
///<reference path="THandlersPrototypes.ts"/>
///<reference path="../externals/fraction.ts"/>

"use strict"

// ------------------------------------------------------------------------------
// put a single number in a message
// ------------------------------------------------------------------------------
class TGetMsgHandlerNum extends GetMsgHandler<GetNumMethod> {
    constructor(method: GetNumMethod) { super (method); }    
    fill(msg: IMessage): IMessage { 
    	msg.add (this.fMethod ());
    	return msg;
    }
}

// ------------------------------------------------------------------------------
// put a single string in a message
// ------------------------------------------------------------------------------
class TGetMsgHandlerText extends GetMsgHandler<GetStringMethod> {
    constructor(method: GetStringMethod) { super (method); }    
    fill(msg: IMessage): IMessage { 
    	msg.add (this.fMethod ());
    	return msg;
    }
}

// ------------------------------------------------------------------------------
// put a date in a message
// ------------------------------------------------------------------------------
class TGetMsgHandlerTime extends GetMsgHandler<GetTimeMethod> {
    constructor(method: GetTimeMethod) { super(method); }     
    fill(msg: IMessage): IMessage { 
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
    fill(msg: IMessage): IMessage { 
    	msg.push (this.fMethod ());
    	return msg;
    }
}

// ------------------------------------------------------------------------------
// return a message list 
// ------------------------------------------------------------------------------
class TGetMsgsHandler extends GetMsgsHandler<GetMultiMethod> {
    constructor(method: GetMultiMethod) { super (method); }    
    getMsgs (): IMessageList { return this.fMethod (); }
}
