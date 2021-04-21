
///<reference path="JSAutoSize.ts"/>
///<reference path="TMedia.ts"/>
///<reference path="AIOScanner.ts"/>
///<reference path="AudioObject.ts"/>
///<reference path="AudioTools.ts"/>

class JSVideoView extends TMedia {
    fVideo: HTMLVideoElement;
	fFile : string;
    
    constructor(parent: JSObjectView) {
		let video = document.createElement('video');
        super(video, parent); 
        this.fVideo = video;
		this.fFile = "";
    }     
	clone (parent: JSObjectView) : JSObjectView { return new JSVideoView(parent); }
	toString() : string			{ return "JSVideoView"; }

	updateSpecial ( obj: INScoreObject )	: boolean {		
        AIOScanner.scan (obj.getOSCAddress());
		this.addHandlers( this.fVideo, obj);
        this.fVideo.src  = obj.getFile();
		return this.updateSizeASync (obj );
	}
 
	setShadow(elt: HTMLElement, val: OShadow): void {
		this.fVideo.style.filter = `drop-shadow(${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px)`;
	}

	updateSpecific(obj: INScoreObject)	: void {
		AudioTools.updateConnections (obj, this);
		let media = obj.getMediaInfos();
		if (media.playing) this.fVideo.play();
		else this.fVideo.pause();
		this.fVideo.volume = media.volume;
		if (media.rate >= 0) 	this.fVideo.playbackRate = media.rate;
		if (media.mdate >= 0)	this.fVideo.currentTime = media.mdate / 1000;
    }

	// updateVideoControl(video: IVideo): void {
	// 	if (video.modified()){
	// 		video.fPlay ? this.fVideo.play() : this.fVideo.pause();
	// 		this.fVideo.volume = video.fVolume;
	// 		this.fVideo.playbackRate = video.fRate;
	// 		this.fVideo.currentTime += video.fVDate.getNumerator() / video.fVDate.getDenominator();
	// 		video.fMLS       = this.fVideo.duration * 1000;
	// 		video.fVDuration = this.fVideo.duration / this.fVideo.playbackRate;
	// 	}
	// }

	// 	getClientSize(video: IVideo): { w: number, h: number } {
    //   	  if (!this.fClientWidth) {
    //         this.fClientWidth  = this.fVideo.videoWidth;
    //         this.fClientHeight = this.fVideo.videoHeight;
    //  	   }
    //    	 return { w: this.fClientWidth, h: this.fClientHeight };
    // }
}