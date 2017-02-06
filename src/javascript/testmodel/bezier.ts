
///<reference path="src/controller/IGlue.ts"/>
///<reference path="src/model/ICurve.ts"/>
///<reference path="node.d.ts"/>

"use strict";
declare function print(arg: string);

//function debugmsg(str: string){ typeof console !== 'undefined' ? console.log(str) : print(str); }


function checkbezier () : void {
	let a = new BezierCurve (1, 1, 2, 2, 3, 3, 4, 4);
	let b = new BezierCurve (1, 1, 2, 2, 3, 3, 4, 4);
	let c = new BezierCurve (0, 1, 2, 2, 3, 3, 4, 4);
	let d = new BezierCurve (0, 1, 2, 2, 3, 3, 5, 4);
	if ( !a.equal(b) ) 
		debugmsg ( "erreur a != b ");
	if ( a.equal(c) ) 
		debugmsg ( "erreur a == c ");
	if ( d.equal(c) ) 
		debugmsg ( "erreur d == c ");
}
