
///<reference path="../controller/IMessage.ts"/>
///<reference path="../externals/fraction.ts"/>
///<reference path="../model/Methods.ts"/>
///<reference path="../inscore-interface.ts"/>
///<reference path="../parser/MessageInterface.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="TEnv.ts"/>

interface ScalingFunction 			{ (n: number): number; }

//-------------------------------------------------------------- 
// Message evaluation:
// consists in:
// 	- evaluation of mouse position variables ($x, $y, $absx, $absy, $sx, $sy)
//	  supports scaling using a [x,y] suffix (position values are expected in the range [-1, 1])
// 	- evaluation of time variables ($date, $rdate)
//	  supports quantification using a [n,d] suffix 
//	  supports date output control using a %f suffix 
// 	- evaluation of the target variables : $name, $scene, $address
// 	- evaluation of variables inside the msg address: $self, $scene)
//-------------------------------------------------------------- 
class TMessageEvaluator
{
	fEnv : TEnv;				// the evaluation environment
	fTargetName: string;
	fTargetScene: string;
	
	constructor (env: TEnv) 	{ 
		this.fEnv = env;
		this.fTargetName = this.getOSCName (env.fTarget);
		this.fTargetScene = this.getOSCScene (env.fTarget);
	}

	//----------------------------------------
	eval (msgs: IMessageList) : IMessageList {
		let out = new IMessageList();
		for (var i=0; i < msgs.length; i++) {
			let msg = msgs[i];
			let addr = this.evalOSCAddr (msg.address(), this.fEnv);
			let params = this.evalParams (msg.params(), this.fEnv);
//console.log ("eval: " + msg);
			let outmsg = new IMessage (addr, params);
//console.log (" => : " + outmsg); 
			out.push (outmsg);
		}
		return out;
	}

	//----------------------------------------
	// private methods
	//----------------------------------------
	private evalOSCAddr (addr: string, env: TEnv) : string {
		return addr.replace ("$self", this.fTargetName).replace ("$scene", this.fTargetScene);
	}

	//----------------------------------------
	private evalIndexedVar (p: string, env: TEnv) : any {
		if (p.match (/[^0-9]/)) return null; 			// check for non numeric chars
		let i = parseInt (p) - 1;
		return ((i >= 0 ) && (i < env.fUser.length)) ? env.fUser[i] : null;
	}

	//----------------------------------------
	private dateVar (env: TEnv, scale: TPair<number>, relative: boolean, float: boolean) : number | number[] {
		let d = env.fTimePos;
		if (relative) 	d = d.add (env.fDate);
		if (scale)		d = d.quantize (scale.first, scale.second);
		return float ? d.toNum() : d.toArray();
	}

	//----------------------------------------
	private evalParam (p: any, env: TEnv) : any {
		if (typeof p === "string") {
			let str = <string>p;
			if ((str.length < 2) || str[0] != '$') return p;
			
			str = str.slice(1); 							// remove the '$' char
			let user = this.evalIndexedVar (str, env);
			if (user) return user;

			let scale = this.getScaling (str);				// get scaling option
			let f = this.getScalingFunction (scale);
			let float =  str.match(/..*%f/) != null;		// get the float option from the variable
			str = str.replace(/[\[%].*/, "");				// get the variable name only
			switch (str) {
				case "absx": 	return f (env.fMouse.abs.x);
				case "absy": 	return f (env.fMouse.abs.y);
				case "sx": 		return f (env.fMouse.parent.x);
				case "sy": 		return f (env.fMouse.parent.y);
				case "x": 		return f (env.fMouse.rel.x);
				case "y":		return f (env.fMouse.rel.y);
				case "date":	return this.dateVar (env, scale, false, float);
				case "rdate":	return this.dateVar (env, scale, true, float);
			}
		}
		else if (p.address) {		// this is a message based parameter
			return this.evalGetMsg (<Message>p, env);
		}
		return p;
	}

	//----------------------------------------
	private getScaling (param: string) : TPair<number> {
		let m = param.replace(/.*\[/, "").replace(/\](%f)?/, "")	// extract the part enclosed in []
		if (m.match (/[^0-9.,-]/)) return null; 					// check for non numeric chars
	
		let t = m.split(',');
		let a = parseFloat (t[0]);
		let b = parseFloat (t[1]);
		if (!isNaN(a) && !isNaN(b)) return { first: a, second: b };
		return null;
	}

	//----------------------------------------
	private getScalingFunction (p: TPair<number>) : ScalingFunction {
		let identity = function (n: number): number { return n; }
		if (p) return function (n: number): number { return p.first + (n + 1)/2 * (p.second-p.first) };
		return identity;
	}

	//----------------------------------------
	private evalGetMsg (msg: Message, env: TEnv) : Array<any> {
		let out: Array<any> = [];
		let params = msg.params;
		if ((params.length > 0) && (params[0] === kget_SetMethod)) {
			let addr = this.evalOSCAddr (msg.address.osc, this.fEnv);
			let msgs = INScore.getMessage (addr, params.slice(1));
			msgs.forEach ( function(msg: IMessage) {
				let p = msg.params();
				if (p.length > 1) out = out.concat ( p.slice( (p[0] == kset_SetMethod) ? 2 : 1) )
				} );
		}
		return out;
	}

	//----------------------------------------
	private evalParams (params: Array<any>, env: TEnv) : Array<any> {
		let out: Array<any> = [];
		for (var i=0; i < params.length; i++) {
			let p = params[i];
			if (p instanceof Array) 	out.push(p);
			
			p = this.evalParam (p, env);
			if (p instanceof Array) out = out.concat(p);
			else out.push (p);
		}
		return out;
	}
	
	//----------------------------------------
	private getOSCName (addr: string) : string 		{ return addr.replace(/^..*\//, ""); }
	private getOSCScene (addr: string) : string 	{ return addr.replace(/\/[^\/]*\//, "").replace(/\/..*/, ""); }
};
