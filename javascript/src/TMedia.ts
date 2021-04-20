
///<reference path="lib/libINScore.d.ts"/>
///<reference path="JSAutoSize.ts"/>

abstract class TMedia extends JSAutoSize implements AudioObject {
	private fReady : boolean = false;
	private fListen : boolean = false;
	fAudioNode : AudioNode = null;

	constructor(elt: HTMLMediaElement, parent: JSObjectView) {
        super(elt, parent);
		this.fAudioNode = AIOScanner.fAudioContext.createMediaElementSource(elt);
    }     

	abstract clone (parent: JSObjectView) : JSObjectView;

	addHandlers (elt: HTMLMediaElement, obj: INScoreObject)	: void {
		if (!this.fListen) {
			elt.addEventListener ("ended", (event) => { this.end(obj); });
			elt.addEventListener ("error", (event) => { this.error(event, obj); });
			elt.addEventListener ("canplay", (event) => { this.ready(obj, elt); });
			this.fListen = true;
		}
		this.fReady = false;
	}

	ready ( obj: INScoreObject, elt: HTMLMediaElement)	: void {
		if (!this.fReady) {
			obj.updateDuration (elt.duration * 1000);
			obj.event ("ready");
			this.fReady = true;
		}
	}
	end ( obj: INScoreObject)	: void { obj.event ("end"); }
	error ( event: ErrorEvent, obj: INScoreObject)	: void {
		console.log (obj.getOSCAddress() + ": " + event.message);
		obj.event ("error");
	}

	toAudioObject() : AudioObject { return this; }
	getNumInputs() : number     { return this.fAudioNode ? this.fAudioNode.channelCount : 0; } 
    getNumOutputs() : number    { return this.fAudioNode ? this.fAudioNode.channelCount : 0; }
    getAudioNode() : AudioNode  { return this.fAudioNode; }
}
