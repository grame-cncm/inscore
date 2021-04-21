
///<reference path="JSAutoSize.ts"/>
///<reference path="TMedia.ts"/>
///<reference path="AIOScanner.ts"/>
///<reference path="AudioTools.ts"/>

class JSAudioView extends TMedia { 
    fAudio: HTMLAudioElement;
	fFile : string;
    
    constructor(parent: JSObjectView) {
		let audio = document.createElement('audio');
        super(audio, parent); 
        this.fAudio = audio;
		this.fFile = "";
    }     
	clone (parent: JSObjectView) : JSObjectView { return new JSAudioView(parent); }
	toString() : string			{ return "JSAudioView"; }

	updateSpecial ( obj: INScoreObject)	: boolean {	
        AIOScanner.scan (obj.getOSCAddress());
		this.addHandlers( this.fAudio, obj);
		this.fAudio.src  = obj.getFile();
		this.fAudio.currentTime = 0;
		return this.updateSizeASync (obj);
	}
 
	setShadow(elt: HTMLElement, val: OShadow): void {
		this.fAudio.style.filter = `drop-shadow(${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px)`;
	}

	updateSpecific(obj: INScoreObject)	: void {
		AudioTools.updateConnections (obj, this);
		let media = obj.getMediaInfos();
		if (media.playing) this.fAudio.play();
		else this.fAudio.pause();
		this.fAudio.volume = media.volume;
		if (media.rate >= 0) 	this.fAudio.playbackRate = media.rate;
		if (media.mdate >= 0)	this.fAudio.currentTime = media.mdate / 1000;
	}
}