
"use strict";

//----------------------------------------------------------------------------
// INScore interface
//----------------------------------------------------------------------------
class INScore {
    constructor() {
        this.fInscore = 0;
        this.fInscoreGlue = 0;
        this.fJSGlue = 0;
    }
    
    //------------------------------------------------------------------------
    // async initialization
    initialize (lib) {
        if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
            var inscoremodule = require (lib);
            return new Promise ( (success) => {
                    inscoremodule().then ( (instance) => {
                    this.moduleInit (instance);
                    success ( this ); 
                });
            });
        }
        else {
            var module = INScoreModule();
            return new Promise ( (success, failure) => {
                module['onRuntimeInitialized'] = () => {
                this.moduleInit (module);
                success ( this ); 
                }
            });
        }
    }
    
    //------------------------------------------------------------------------
    // async initialization
    moduleInit ( module ) {
        this.fInscore 		= new module.INScoreAdapter();
        this.fJSGlue 		= new module.INScoreJSGlue();
    }
        
    //------------------------------------------------------------------------
    // INScore interface
	start(udpport, outport, errport) 	{ this.fInscoreGlue = this.fInscore.start (udpport, outport, errport); }
	stop() 								{ this.fInscore.stop ( this.fInscoreGlue ); }
// 	restartNetwork ()					{ this.fInscore.restartNetwork(); }
// 	stopNetwork ()						{ this.fInscore.stopNetwork(); }

	postMessage	(adr, msg)				{ this.fInscore.postMessage (adr, msg); }
	postMessageStr (adr, meth)			{ this.fInscore.postMessageStr (adr, meth); }
	postMessageStrI	(adr, meth, val)	{ this.fInscore.postMessageStrI (adr, meth, val); }
	postMessageStrF	(adr, meth, val)	{ this.fInscore.postMessageStrF (adr, meth, val); }
	postMessageStrStr(adr, meth, val)	{ this.fInscore.postMessageStrStr (adr, meth, val); }

	delayMessage (adr, msg)				{ this.fInscore.delayMessage (adr, msg); }
	newMessage ()						{ return this.fInscore.newMessage(); }
	newMessageM (meth)					{ return this.fInscore.newMessageM(meth); }
	delMessage (msg)					{ return this.fInscore.delMessage(msg); }

	msgAddStr (msg, str)				{ return this.fInscore.msgAddStr (msg, str); }
	msgAddF (msg, val)					{ return this.fInscore.msgAddF (msg, val); }
	msgAddI (msg, val)					{ return this.fInscore.msgAddI (msg, val); }

	version ()				{ return this.fInscore.version(); }
	versionStr ()			{ return this.fInscore.versionStr(); }
	guidoversion ()			{ return this.fInscore.guidoversion(); }
	musicxmlversion ()		{ return this.fInscore.musicxmlversion(); }
        
    //------------------------------------------------------------------------
    // INScore glue interface
	getRate() 				{ return this.fInscoreGlue.getRate(); } 
	timeTask ()				{ this.fInscoreGlue.timeTask(); }
	sorterTask()			{ this.fInscoreGlue.sorterTask(); } 
 }


if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
    module.exports = INScore;
}
