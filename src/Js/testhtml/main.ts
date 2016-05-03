
///<reference path="src/controller/IGlue.ts"/>
///<reference path="src/globals.ts"/>

"use strict";
declare function print(arg: string);

function debugmsg(str: string){
	typeof console !== 'undefined' ? console.log(str) : print(str);
}

gCreateView = true;
var gGlue = new IGlue();
gGlue.initEventHandlers();
gGlue.start();

