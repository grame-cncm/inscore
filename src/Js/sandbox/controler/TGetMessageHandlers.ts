
///<reference path="./IMessage.ts"/>

"use strict"
// ------------------------------------------------------------------------------
// the set message handler type
// ------------------------------------------------------------------------------
interface GetMsgHandler { print(msg: IMessage): IMessage }

// ------------------------------------------------------------------------------
// base class for all get message handlers
// ------------------------------------------------------------------------------
class TGetMessageHandler<C> implements GetMsgHandler { 
    protected fObject: C;    
    protected fMethod: string; 
    constructor(o: C, method: string) { this.fObject = o; this.fMethod = method; }    
    print(msg: IMessage):  IMessage { 
    	let out = new IMessage (msg.address(), msg.param(1));
    	out.push ( this.fObject[this.fMethod]());
    	return out;
    }
}
