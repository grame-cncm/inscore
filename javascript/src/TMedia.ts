
///<reference path="lib/libINScore.d.ts"/>
///<reference path="JSAutoSize.ts"/>

abstract class TMedia extends JSAutoSize {
	private fReady : boolean = false;
	private fListen : boolean = false;

	constructor(elt: HTMLElement, parent: JSObjectView) {
        super(elt, parent); 
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
}
