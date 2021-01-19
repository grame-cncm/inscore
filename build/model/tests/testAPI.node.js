
"use strict";

const fs 		= require ("fs");
const INScore 	= require ("./inscore");
const run 		= require ("./testAPI");

console.log("start inscore test")

var inscore = new INScore;
inscore.initialize ("./libINScore").then (doit);

function log(str) 		{ console.log (str); }

function showlog (status) {}

function doit (engine) {
	console.log( "INscore version " + inscore.versionStr());
	run (inscore, log);
}
