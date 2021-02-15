
///<reference path="lib/libINScore.d.ts"/>
///<reference path="inscore.ts"/>

class TJavascript {

	static run (script: string ) : number {
		let out = window.eval (script);
		if (out) {
			if (typeof out === 'string') {
				inscore.loadInscore (out);
			}
			else if (Array.isArray(out)) {
				let outsum = "";
				out.forEach ( (value) => outsum += value);
				inscore.loadInscore (outsum);
			}
			else {
				console.log ("Unexpected value returned by " + script + ": " + out);
				return 0;
			}
		}
		return 1;
	}
}
