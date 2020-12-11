
///<reference path="lib/libINScore.d.ts"/>

class TJavascript {

	static run (script: string ) : number {
		let out = eval (script);
		if (out) {
			if (typeof out === 'string') {
				inscore.loadInscore (out);
			}
			else {
				console.log ("Unexpected value returned by " + script);
				return 0;
			}
		}
		return 1;
	}
}
