
///<reference path="../controller/IMessage.ts"/>
///<reference path="../externals/fraction.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="TEnv.ts"/>

//-------------------------------------------------------------- 
// Message evaluation:
// consists in:
// 	- evaluation of mouse position variables ($x, $y, $absx, $absy, $sx, $sy)
//	  supports scaling using a [x,y] suffix (position values are expected in the range [-1, 1])
// 	- evaluation of time variables ($date, $rdate)
//	  supports quantification using a [n,d] suffix 
//	  supports output control using a %f suffix 
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
	private dateVar (env: TEnv, scale: TPosition, relative: boolean, float: boolean) : number | number[] {
		let d = env.fTimePos;
		if (relative) d = d.add (env.fDate);
		return (float) ? d.toNum() : d.toArray();
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
			let float =  str.replace(/..*%/, "%") == "%f";	// get the float option from the variable
			str = str.replace(/[\[%].*/, "");				// get the variable name only
			switch (str) {
				case "absx": 	return env.fMouse.ax * scale.x;
				case "absy": 	return env.fMouse.ax * scale.y;
				case "sx": 		return env.fMouse.sx * scale.x;
				case "sy": 		return env.fMouse.sy * scale.y;
				case "x": 		return env.fMouse.x * scale.x;
				case "y":		return env.fMouse.y * scale.y;
				case "date":	return this.dateVar (env, scale, false, float);
				case "rdate":	return this.dateVar (env, scale, true, float);
			}
		}
		return p;
	}

	//----------------------------------------
	private getScaling (param) : TPosition {
		let m = param.replace(/.*\[/, "").replace(/\](%f)?/, "")	// extract the part enclosed in []
		if (m.match (/[^0-9.,]/)) return { x: 1, y: 1 }; 			// check for non numeric chars
	
		let t = m.split(',');
		let a = parseFloat (t[0]);
		let b = parseFloat (t[1]);
		if (!isNaN(a) && !isNaN(b)) return { x: -a, y: b };
		return { x: 1, y: 1 };
	}

	//----------------------------------------
	private evalParams (params: Array<any>, env: TEnv) : Array<any> {
		let out: Array<any> = [];
		for (var i=0; i < params.length; i++) {
			let p = params[i];
			if (p instanceof Array) 	out.push(p);
			
			p = this.evalParam (p, env);
			if (p instanceof Array)
				out.concat(p);
			else out.push (p);
		}
		return out;
	}
	
	//----------------------------------------
	private getOSCName (addr: string) : string 		{ return addr.replace(/^..*\//, ""); }
	private getOSCScene (addr: string) : string 	{ return addr.replace(/\/[^\/]*\//, "").replace(/\/..*/, ""); }
};
