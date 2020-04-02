///<reference path="guidoengine.ts"/>

//----------------------------------------------------------------------------
class libraries {
	private fGuido : GuidoEngine;

	constructor() {
    	this.fGuido = new GuidoEngine;
    }

	async initialise():Promise<any> { 
        return this.guidoinit();
    }


	async guidoinit():Promise<any> { 
		return new Promise( (success: any, failure: any) => {
			this.fGuido.initialise().then (
				() => { console.log("GuidoEngine version " + this.fGuido.getFloatVersion()); 
						success(this); },
				() => { this.fGuido = null; 
						failure(this) });
		});
	}

	guido() : GuidoEngine { return this.fGuido; }
}
