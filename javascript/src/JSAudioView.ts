
///<reference path="JSAutoSize.ts"/>

class JSAudioView extends JSAutoSize {
    fAudio: HTMLAudioElement;
	fFile : string;
    
    constructor(parent: JSObjectView) {
		let audio = document.createElement('audio');
        super(audio, parent); 
        this.fAudio = audio;
		this.fFile = "";
        this.getElement().className = "inscore-audio";
    }     
	clone (parent: JSObjectView) : JSObjectView { return new JSAudioView(parent); }

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
		this.fAudio.src  = obj.getFile();
		return this.updateSizeASync (objid );
	}
 
	setShadow(elt: HTMLElement, val: OShadow): void {
		this.fAudio.style.filter = `drop-shadow(${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px)`;
	}

	updateSpecific(obj: INScoreObject)	: void {
		let media = obj.getMediaInfos();
		if (media.playing) this.fAudio.play();
		else this.fAudio.pause();
		this.fAudio.volume = media.volume;
		if (media.rate >= 0) 	this.fAudio.playbackRate = media.rate;
		if (media.mdate >= 0)	this.fAudio.currentTime = media.mdate;
    }
}