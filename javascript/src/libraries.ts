///<reference path="lib/guidoengine.ts"/>
///<reference path="lib/libmusicxml.ts"/>

//----------------------------------------------------------------------------
class libraries {
	private fGuido  : GuidoEngine;
	private fXMLLib : libmusicxml;
	private fFaust : any;

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

	// async faustinit():Promise<any> { 
	// 	return new Promise( (success: any, failure: any) => {
	// 		fFaust = new Faust2WebAudio.Faust({ debug: true, wasmLocation: "lib/faust/libfaust-wasm.wasm", dataLocation: "lib/faust/libfaust-wasm.data" });
	// 		this.fFaust.ready.then ( 
	// 			() => { console.log ("Faust version: " + fFaust.getLibFaustVersion()); success (this); },
	// 		() => { this.fFaust = null; success(this); });
	// 	}); 
	// }

	guido()  : GuidoEngine { return this.fGuido; }
	xmllib() : libmusicxml { return this.fXMLLib; }
}

var inscorelibs = new libraries();