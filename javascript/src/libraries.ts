///<reference path="lib/guidoengine.ts"/>
///<reference path="lib/libmusicxml.ts"/>
///<reference path="faust.ts"/>

//----------------------------------------------------------------------------
class libraries {
	private fGuido  : GuidoEngine;
	private fXMLLib : libmusicxml;
	private fFaust : faust;

	static fGuidoVersion = 0;
	static fXMLVersion = 0;
	static fFaustVersion = 0;

	constructor() {
    	this.fGuido  = new GuidoEngine;
		this.fXMLLib = new libmusicxml;
		this.fFaust = new faust;
    }

	async initialise():Promise<any> { 
		await this.guidoinit();
		await this.xmlinit();
		return this.faustinit();
	}
		

	async guidoinit():Promise<any> { 
		return new Promise( (success: any, failure: any) => {
			this.fGuido.initialise().then (
				() => { libraries.fGuidoVersion = this.fGuido.getFloatVersion();
						console.log("GuidoEngine version " + this.fGuido.getVersionStr() + " '" + this.fGuido.getVersion() + "'"); 
						success(this); },
				() => { this.fGuido = null; success(this); });
		});
	}

	async xmlinit():Promise<any> { 
		return new Promise( (success: any, failure: any) => {
			this.fXMLLib.initialise().then (
				() => { libraries.fXMLVersion = this.fXMLLib.libVersion();
						console.log("libMusicXML version " + this.fXMLLib.libVersionStr()); 
						success(this); },
				() => { this.fXMLLib = null; success(this); });
		});
	}

	async faustinit():Promise<any> { 
		return new Promise( (success: any, failure: any) => {
			this.fFaust.initialise().then (
				() => { console.log("Faust version " + this.fFaust.version()); success(this); },
				() => { this.fFaust = null; success(this); });
		});
	}

	guido()  : GuidoEngine  { return this.fGuido; }
	xmllib() : libmusicxml  { return this.fXMLLib; }
	faust()  : faust		{ return this.fFaust; }
}

var inscorelibs = new libraries();

function getGuidoVersion() : number 		{ return libraries.fGuidoVersion; }
function getMusicXMLVersion() : number 		{ return libraries.fXMLVersion; }
function getFaustVersion() : number 		{ return libraries.fFaustVersion; }
