
"use strict";

//----------------------------------------------------------------------------
class VSceneView {

    constructor() {
    	this.fInscore = new INScore;
    	this.fTimeTask = 0;
    	this.fInscore.initialize ().then (() => { this.initialize(); });
    }
	
 }

var gGlue = new INScoreGlue;


