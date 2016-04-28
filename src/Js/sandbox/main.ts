
///<reference path="classA.ts"/>
///<reference path="classB.ts"/>

var v = new A();
console.log( v.fN);
var ac = new ACaller(v, v.fX);
ac.handle(10);
console.log( v.fN);
