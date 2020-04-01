
///<reference path="../externals/fraction.ts"/>
///<reference path="../lib/TTypes.ts"/>

//-------------------------------------------------------------- 
// Environment for a message evaluation
//-------------------------------------------------------------- 
class TEnv
{
	fMouse : TMouseEnv;		// for mouse events evaluation
	fDate :	Fraction;		// the target object date
	fTimePos: Fraction;		// the time position inside the object
	fUser : Array<any>;		// for user events evaluation
	fSystem: Array<any>;	// system information
	fTarget: string;		// the target object OSC address
	
	constructor (target: string, mouse?: TMouseEnv, date?: Fraction, timepos?: Fraction, user?:  Array<any>) {
		this.fTarget = target; 
		this.fMouse = mouse ? mouse : {rel: {x:0, y:0}, abs: {x:0, y:0}, parent: {x:0, y:0}}; 
		this.fDate = date ? date : new Fraction(0, 1);
		this.fTimePos = timepos ? timepos : new Fraction(0, 1);
		this.fUser = user ? user : [];
		this.fSystem = [];		// add the following keys: 
								//	OSName: "MacOS", "Windows", "Linux", "Android" or "iOS".
								//	OSId: 1 for Android, 2 for iOS, 3 for Linux, 4 for MacOS, 5 for Windows.
	}

	toString() : string {
		let out = "Env: " + this.fTarget;
		out += "\n	mouse: " + this.fMouse;
		out += "\n	date: " + this.fDate;
		out += "\n	timepos: " + this.fTimePos;
		out += "\n	user: " + this.fUser;
		out += "\n	system: " + this.fSystem;
		return out;
	}
};
