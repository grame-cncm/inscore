///<reference path="lib/guidoengine.ts"/>
///<reference path="lib/libmusicxml.ts"/>
///<reference path="faust.ts"/>

//----------------------------------------------------------------------------
class libraries {
	private fGuido  : GuidoEngine;
	private fXMLLib : libmusicxml;
	private fFaust : faust;

	constructor() {
    	this.fGuido  = new GuidoEngine;
		this.fXMLLib = new libmusicxml;
		this.fFaust = new faust;
    }

	async initialise():Promise<any> { 
		// return this.guidoinit().then ( 
		// 	() => { return this.xmlinit().then (); }
		// 	);
		await this.guidoinit();
		await this.xmlinit();
		return this.faustinit();
	}
		

	async guidoinit():Promise<any> { 
		return new Promise( (success: any, failure: any) => {
			this.fGuido.initialise().then (
				() => { console.log("GuidoEngine version " + this.fGuido.getFloatVersion()); success(this); },
				() => { this.fGuido = null; success(this); });
		});
	}

	async xmlinit():Promise<any> { 
		return new Promise( (success: any, failure: any) => {
			this.fXMLLib.initialise().then (
				() => { console.log("libMusicXML version " + this.fXMLLib.libVersionStr()); success(this); },
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

	guido()  : GuidoEngine { return this.fGuido; }
	xmllib() : libmusicxml { return this.fXMLLib; }
	faust() 			{ return this.fFaust; }
}

var inscorelibs = new libraries();