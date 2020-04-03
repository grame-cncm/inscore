///<reference path="guidoengine.ts"/>
///<reference path="libmusicxml.ts"/>

//----------------------------------------------------------------------------
class libraries {
	private fGuido  : GuidoEngine;
	private fXMLLib : libmusicxml;

	constructor() {
    	this.fGuido  = new GuidoEngine;
    	this.fXMLLib = new libmusicxml;
    }

	async initialise():Promise<any> { 
		return this.guidoinit().then ( 
		() => { return this.xmlinit(); }
		);
	}
		

	async guidoinit():Promise<any> { 
		return new Promise( (success: any, failure: any) => {
			this.fGuido.initialise().then (
				() => { console.log("GuidoEngine version " + this.fGuido.getFloatVersion()); 
						success(this); },
				() => { this.fGuido = null; success(this); });
		});
	}

	async xmlinit():Promise<any> { 
		return new Promise( (success: any, failure: any) => {
			this.fXMLLib.initialise().then (
				() => { console.log("libMusicXML version " + this.fXMLLib.libVersionStr()); 
						success(this); },
				() => { this.fXMLLib = null; success(this); });
		});
	}

	guido()  : GuidoEngine { return this.fGuido; }
	xmllib() : libmusicxml { return this.fXMLLib; }
}
