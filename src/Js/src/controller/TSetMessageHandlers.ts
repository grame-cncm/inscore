
///<reference path="./IMessage.ts"/>
///<reference path="../externals/fraction/fraction.ts"/>

"use strict"
enum msgStatus { 
    kBadAddress,
    kProcessed = 1,
    kProcessedNoChange = 2,
    kBadParameters = 4,
    kCreateFailure = 8,
}

// ------------------------------------------------------------------------------
// the set message handler type
// ------------------------------------------------------------------------------
interface SetMsgHandler { handle(msg: IMessage): msgStatus }

// ------------------------------------------------------------------------------
// a basic message handler: passes the whole message to the client object
// ------------------------------------------------------------------------------
class TMethodHandler<C> implements SetMsgHandler { 
    protected fObject: C;    
    protected fMethod: string;    
    constructor(o: C, method: string) { this.fObject = o; this.fMethod = method; }    
    handle(msg: IMessage): msgStatus { return this.fObject[this.fMethod]( msg); }
}

// ------------------------------------------------------------------------------
// a no param message handler
// ------------------------------------------------------------------------------
class TMsgHandlerVoid<C> extends TMethodHandler<C> {
    constructor(o: C, method: string) { super(o, method); }      
    handle(msg: IMessage): msgStatus { 
        if ( msg.size() != 1 ) { return msgStatus.kBadParameters; } 
    	this.fObject[this.fMethod](); 
    	return msgStatus.kProcessed;
    }
}

// ------------------------------------------------------------------------------
// a single number message handler: passes a number to the client object
// ------------------------------------------------------------------------------
class TMsgHandlerNum<C> extends TMethodHandler<C> {
    constructor(o: C, method: string) { super(o, method); }      
    handle(msg: IMessage): msgStatus { 
        if ( msg.size() != 2 ) { return msgStatus.kBadParameters; } 
        let ret: MsgParamRetVal<number> = msg.paramNum(1);
        if (!ret.correct)  { return msgStatus.kBadParameters; } 
    	this.fObject[this.fMethod]( ret.value); 
    	return msgStatus.kProcessed;
    }
}

// ------------------------------------------------------------------------------
// a single string message handler: passes a string to the client object
// ------------------------------------------------------------------------------
class TMsgHandlerText<C> extends TMethodHandler<C> {
    constructor(o: C, method: string) { super(o, method); }     
    handle(msg: IMessage): msgStatus { 
        if ( msg.size() != 2 ) { return msgStatus.kBadParameters; } 
        let ret: MsgParamRetVal<string> = msg.paramStr(1);
        if (!ret.correct)  { return msgStatus.kBadParameters; } 
    	this.fObject[this.fMethod]( ret.value); 
    	return msgStatus.kProcessed;
    }
}

// ------------------------------------------------------------------------------
// a color message handler: passes color values to the client object
// alpha value is optional and defaults to 1
// ------------------------------------------------------------------------------
class TMsgHandlerColor<C> extends TMethodHandler<C> {
    constructor(o: C, method: string) { super(o, method); }     
	protected getrgb(msg: IMessage): { err: boolean, r?: number, g?: number, b?: number } {
		if ( msg.size() < 4 ) return { err: true };
        let r = msg.paramNum(1);
        let g = msg.paramNum(2);
        let b = msg.paramNum(3);
        if (!r.correct || !g.correct || !b.correct) return { err: true };
        return { err: false, r: r.value, g: g.value, b: b.value };		
	}
    handle(msg: IMessage): msgStatus { 
		if ( msg.size() > 5 ) return msgStatus.kBadParameters;
        let rgb = this.getrgb(msg);
        if ( rgb.err ) { return msgStatus.kBadParameters; } 
		if ( msg.size() == 5 ) {
	        let r = msg.paramNum(4);
	        if (r.correct) return this.fObject[this.fMethod](rgb.r, rgb.g, rgb.b, r.value); 
	        else return msgStatus.kBadParameters;
	    }
    	this.fObject[this.fMethod](rgb.r, rgb.g, rgb.b); 
    	return msgStatus.kProcessed;
    }
}

// ------------------------------------------------------------------------------
// a time message handler: passes a date to the client object
// it supports the followinf date forms:
//    	- n d
//		- n
//		- a float value
//		- "n/d"
// ------------------------------------------------------------------------------
class TMsgHandlerTime<C> extends TMethodHandler<C> {
    constructor(o: C, method: string) { super(o, method); }     
    handle(msg: IMessage): msgStatus { 
		let n = msg.size();
		if ( n > 3 ) return msgStatus.kBadParameters;
		if (n == 3) {
	        let num = msg.paramNum(1);
	        let denum = msg.paramNum(2);
			if (!num.correct || !denum.correct) return msgStatus.kBadParameters;
    		this.fObject[this.fMethod](new Fraction(num.value, denum.value)); 
		}
		else if (n == 2) {
	        let d = msg.paramNum(1);
	        let dstr = msg.paramStr(1);
	        if (d.correct)
	        	this.fObject[this.fMethod](new Fraction(d.value));
	        else if (dstr.correct)
	        	this.fObject[this.fMethod](new Fraction(dstr.value));
		    else return msgStatus.kBadParameters;
		}
		return msgStatus.kProcessed;
    }
}
