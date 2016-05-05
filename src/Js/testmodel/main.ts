
///<reference path="src/inscore.ts"/>
///<reference path="src/controller/IGlue.ts"/>
///<reference path="src/model/TILoader.ts"/>
///<reference path="bezier.ts"/>
///<reference path="node.d.ts"/>

"use strict";
declare function print(arg: string);
declare var INScoreParser;

function debugmsg(str: string){
	typeof console !== 'undefined' ? console.log(str) : print(str);
}

var gGlue = new IGlue();
gGlue.start();

function readfile (file: string) : string {
    let fs = require('fs');
	return fs.readFileSync(file);
}

function processfile ( file: string) : void {
	let content = readfile(file);
	if (content.length) {
		debugmsg ("processfile content: \n" +content);
		let loader = new TILoader;
		loader.process (content, INScore.getRoot());
		debugmsg (INScore.getRoot().toString());
	}
}

function main (args: Array<string>) {
 	var n = args.length;
	if (n < 3) {
		debugmsg ("Usage: node main.ts <files>");
	}
	else for (var i=2; i<n; i++) {
		let file = args[i];
		debugmsg ("Processing file " + file);
		debugmsg ("------------------------------------");
		processfile (file);
	}
//	debug();
//	debugmsg ("check bezier diff");
	checkbezier();

	process.exit();
}

main( process.argv );
