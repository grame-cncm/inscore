
///<reference path="./controler/IMessage.ts"/>
///<reference path="./controler/TSetMessageHandlers.ts"/>
///<reference path="./controler/TGetMessageHandlers.ts"/>
///<reference path="./externals/fraction/fraction.ts"/>

"use strict";
declare function print(arg: string);

function debugmsg(str: string){
	typeof console !== 'undefined' ? console.log(str) : print(str);
}

class color {
	protected fColor: Array<number>;
    constructor(r: number, g: number, b: number, a?: number) { 
    	this.set(r, g, b, (a ? a: 255));
	}
	get() : Array<number>  { return this.fColor; }
	set(r: number, g: number, b: number, a?: number)  { return this.fColor = [r, g, b, (a ? a: 255)]; }
	toString() : string  { return this.fColor.toString(); }
}

class msgCaller {
    protected fMsgHandlers: Array<SetMsgHandler>;
    protected fGetMsgHandlers: Array<GetMsgHandler>;
	protected fX: number;
	protected fTxt: string;
	protected fColor: color;
	protected fDate: Fraction;

    constructor() { 
    	this.fMsgHandlers 		= new Array<SetMsgHandler>(); 
    	this.fGetMsgHandlers 	= new Array<GetMsgHandler>(); 
    	this.fDate = new Fraction(0,1); 
    	this.fX = 0; 
    	this.fTxt = "none"; 
    	this.fColor = new color (1,1,1); 
    	this.init();
    }

    init () {
   		this.fMsgHandlers["x"]   	= new TMsgHandlerNum(this, "setx");
   		this.fMsgHandlers["txt"] 	= new TMsgHandlerText(this, "settxt");
   		this.fMsgHandlers["watch"] 	= new TMethodHandler(this, "set");
   		this.fMsgHandlers["color"] 	= new TMsgHandlerColor(this, "setcolor");
   		this.fMsgHandlers["date"] 	= new TMsgHandlerTime(this, "setdate");
   		this.fMsgHandlers["get"] 	= new TMethodHandler(this, "get");
   		
   		this.fGetMsgHandlers["x"]		= new TGetMessageHandler(this, "getx");
   		this.fGetMsgHandlers["color"]	= new TGetMessageHandler(this, "getcolor");
    }
    
    handle (msg: IMessage): msgStatus {
		let ret = msg.message();
		if (ret.correct) {
			var h = this.fMsgHandlers[ret.value];
			if (typeof h === "object")
				return h.handle(msg);
		}
		return msgStatus.kBadParameters;
    }

    getAll (msg: IMessage): IMessage {
    	let outmsg = new IMessage (msg.address());
    	outmsg.add ("set");
    	outmsg.add (this.fTxt);
    	return outmsg;
    }
    get1param (msg: IMessage, p: string): IMessage {
    	let outmsg: IMessage;
 		var h = this.fGetMsgHandlers[p];
		if (typeof h === "object")
			outmsg = h.print(msg);
    	return outmsg;
    }
    get (msg: IMessage): msgStatus {
		let outmsg: IMessage;
		let n = msg.size();
		if (n == 1) outmsg = this.getAll(msg);
		else for (let i=1; i<n; i++) {
		}
		return msgStatus.kBadParameters;
    }
	setx(x: number)   : void 	{ this.fX = x; }
	setcolor(r: number, g: number, b: number, a?: number) : void 	{ this.fColor.set(r, g, b, a);  }
	settxt(str: string) : void 	{ this.fTxt = str; }
	setdate(d: Fraction) : void { this.fDate = d; }

	getx()   	: number 		{ return this.fX; }
	getcolor() 	: Array<number> { return this.fColor.get();  }
	gettxt() 	: string 		{ return this.fTxt; }

	set(msg: IMessage) : msgStatus 	{ 
		debugmsg( "msgCaller handle msg " + msg.toString()); 
		return  msgStatus.kBadParameters;
	}
	toString() : string 	{ return "msgCaller x: " + this.fX + " txt: " + this.fTxt + " color: " + this.getcolor() + " date: " +this.fDate; }
}

var msg1: IMessage = new IMessage ("/ITL/scene", ["x", 1]);
var msg2: IMessage = new IMessage ("/ITL/scene", ["color", 0, 1, 2]);
var msg3: IMessage = new IMessage ("/ITL/scene", ["txt", "hello world"]);
var msg4: IMessage = new IMessage ("/ITL/scene", ["toto", "hello world"]);
var msg5: IMessage = new IMessage ("/ITL/scene", ["date", .25]);
var msg6: IMessage = new IMessage ("/ITL/scene", ["get", "x"]);
var msg7: IMessage = new IMessage ("/ITL/scene", ["get", "color"]);
var args: Array<IMessage> = [msg1, msg2];
var msg = new IMessage ("/ITL/scene", ["watch", "mouse", args]);
debugmsg( msg + ";" );

var c = new msgCaller();
debugmsg( "c: " + c );
c.handle (msg1);
c.handle (msg3);
c.handle (msg);
debugmsg( "c handle => " + c );
c.handle (msg2);
debugmsg( "c handle => " + c );
var ret = c.handle (msg5);
debugmsg( "c handle => ret: " + ret + " => "+ c );

ret = c.handle (msg4);
debugmsg ( "==> handle " + msg4 + " returns: " + ret);

debugmsg ( "get1param => " + c.get1param (msg6, "x"));
debugmsg ( "get1param => " + c.get1param (msg7, "color"));

let s: SetMsgHandler;
if (s)
	debugmsg( "var true");
else
	debugmsg( "var false");
