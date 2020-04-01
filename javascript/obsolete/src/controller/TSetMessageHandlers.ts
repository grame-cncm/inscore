
///<reference path="IMessage.ts"/>
///<reference path="THandlersPrototypes.ts"/>
///<reference path="../externals/fraction.ts"/>

"use strict"

// ------------------------------------------------------------------------------
// a basic message handler: passes the whole message to the client object
// ------------------------------------------------------------------------------
class TMethodHandler extends SetMsgHandler<SetMsgMethod> { 
    constructor(method: SetMsgMethod) { super (method); }    
    handle(msg: IMessage): eMsgStatus { return this.fMethod (msg); }
}

// ------------------------------------------------------------------------------
// a no param message handler
// ------------------------------------------------------------------------------
class TMsgHandlerVoid extends SetMsgHandler<SetVoidMethod> { 
    constructor(method: SetVoidMethod) { super (method); }    
    handle(msg: IMessage): eMsgStatus { 
        if ( msg.size() != 1 ) { return eMsgStatus.kBadParameters; } 
    	this.fMethod ();
    	return eMsgStatus.kProcessed;
    }
}

// ------------------------------------------------------------------------------
// a single number message handler: passes a number to the client object
// ------------------------------------------------------------------------------
class TMsgHandlerNum extends SetMsgHandler<SetNumMethod> {
    constructor(method: SetNumMethod) { super (method); }    
    handle(msg: IMessage): eMsgStatus { 
        if ( msg.size() != 2 ) { return eMsgStatus.kBadParameters; } 
        let ret: MsgParamRetVal<number> = msg.paramNum(1);
        if (!ret.correct)  { return eMsgStatus.kBadParameters; } 
    	this.fMethod (ret.value); 
    	return eMsgStatus.kProcessed;
    }
}

// ------------------------------------------------------------------------------
// a single string message handler: passes a string to the client object
// ------------------------------------------------------------------------------
class TMsgHandlerText extends SetMsgHandler<SetStringMethod> {
    constructor(method: SetStringMethod) { super (method); }    
    handle(msg: IMessage): eMsgStatus { 
        if ( msg.size() != 2 ) { return eMsgStatus.kBadParameters; } 
        let ret: MsgParamRetVal<string> = msg.paramStr(1);
        if (!ret.correct)  { return eMsgStatus.kBadParameters; } 
    	this.fMethod (ret.value); 
    	return eMsgStatus.kProcessed;
    }
}

// ------------------------------------------------------------------------------
// a color message handler: passes color values to the client object
// alpha value is optional and defaults to 1
// ------------------------------------------------------------------------------
class TMsgHandlerColor extends SetMsgHandler<SetColorMethod> {
    constructor(method: SetColorMethod) { super(method); }     
	protected getrgb(msg: IMessage): { err: boolean, rgb?: Array<number> } {
		if ( msg.size() < 4 ) return { err: true };
        let r = msg.paramNum(1);
        let g = msg.paramNum(2);
        let b = msg.paramNum(3);
        if (!r.correct || !g.correct || !b.correct) return { err: true };
        return { err: false, rgb: [r.value, g.value, b.value] };		
	}
    handle(msg: IMessage): eMsgStatus { 
		if ( msg.size() > 5 ) return eMsgStatus.kBadParameters;
        let color = this.getrgb(msg);
        if ( color.err ) { return eMsgStatus.kBadParameters; } 
		if ( msg.size() == 5 ) {
	        let r = msg.paramNum(4);
	        if (r.correct) {
	        	color.rgb.push (r.value);
	        	this.fMethod (color.rgb);
    			return eMsgStatus.kProcessed;
	        }
	        else return eMsgStatus.kBadParameters;
	    }
    	this.fMethod (color.rgb); 
    	return eMsgStatus.kProcessed;
    }
}

// ------------------------------------------------------------------------------
// an array message handler: passes an array to the client object
// accepte any type as parameters
// ------------------------------------------------------------------------------
class TMsgHandlerAnyArray extends SetMsgHandler<SetAnyArrayMethod> {
    constructor(method: SetAnyArrayMethod) { super(method); }     
    handle(msg: IMessage): eMsgStatus { 
        return this.fMethod (msg.params()); 
    }
}

// ------------------------------------------------------------------------------
// an array message handler: passes an array to the client object
// accepte only numbers as parameters
// ------------------------------------------------------------------------------
class TMsgHandlerNumArray extends SetMsgHandler<SetNumArrayMethod> {
    constructor(method: SetNumArrayMethod) { super(method); }     
    protected getnums(msg: IMessage): { err: boolean, numbers?: Array<number> } {
        let out: Array<number> = [];
        for (let i=1; i<msg.size(); i++) {
        	let val = msg.paramNum(i);
        	if (!val.correct) return { err: true };
        	out.push (val.value);
        }
        return { err: false, numbers: out };        
    }
    handle(msg: IMessage): eMsgStatus { 
        let nums = this.getnums(msg);
        if ( nums.err ) { return eMsgStatus.kBadParameters; } 
        
        return this.fMethod (nums.numbers); 
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
class TMsgHandlerTime extends SetMsgHandler<SetTimeMethod> {
    constructor(method: SetTimeMethod) { super(method); }     
    handle(msg: IMessage): eMsgStatus { 
		let n = msg.size();
		if ( n > 3 ) return eMsgStatus.kBadParameters;
		if (n == 3) {
	        let num = msg.paramNum(1);
	        let denum = msg.paramNum(2);
			if (!num.correct || !denum.correct) return eMsgStatus.kBadParameters;
    		this.fMethod (new Fraction(num.value, denum.value)); 
		}
		else if (n == 2) {
	        let d = msg.paramNum(1);
	        let dstr = msg.paramStr(1);
	        if (d.correct)
	        	this.fMethod (new Fraction(d.value));
	        else if (dstr.correct)
	        	this.fMethod (new Fraction(dstr.value));
		    else return eMsgStatus.kBadParameters;
		}
		return eMsgStatus.kProcessed;
    }
}
