
///<reference path="src/controller/IGlue.ts"/>
///<reference path="src/model/TILoader.ts"/>

"use strict";
declare function print(arg: string);
declare var process;

var gGlue = new IGlue();

function debugmsg(str: string){
	typeof console !== 'undefined' ? console.log(str) : print(str);
}

function processfile ( file: string) {
	let loader = new TILoader;
	loader.load(file, gGlue.getRoot());
}

var n = process.argv.length;
if (n < 3) {
	debugmsg ("Usage: node main.ts <files>");
}
else for (var i=2; i<n; i++) {
	let file = process.argv[i];
	debugmsg ("Processing file " + file);
	debugmsg ("------------------------------------");
	processfile (file);
}

process.exit();