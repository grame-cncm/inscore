
///<reference path="JSAutoSize.ts"/>

class JSVideoView extends JSAutoSize {
    fVideo: HTMLVideoElement;
	fFile : string;
    
    constructor(parent: JSObjectView) {
		let video = document.createElement('video');
        super(video, parent); 
        this.fVideo = video;
		this.fFile = "";
        this.getElement().className = "inscore-video";
    }     
	clone (parent: JSObjectView) : JSObjectView { return new JSVideoView(parent); }

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
        this.fVideo.src  = obj.getFile();
		return super.updateSpecial (obj, objid );
	}
 
	setShadow(elt: HTMLElement, val: OShadow): void {
		this.fVideo.style.filter = `drop-shadow(${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px)`;
	}

	// setShadow (params: Array<number>): void {
	// 	let color = new IColor( params.slice(2,6) );
	// 	this.getHtml().style.filter = "drop-shadow(" + color.getCSSRGBAString() + " "+ params[0] +"px " + params[1] +"px " + params[6] +"px)";
	// }

	updateSpecific(obj: INScoreObject)	: boolean {
		let media = obj.getMediaInfos();
		if (media.playing) this.fVideo.play();
		else this.fVideo.pause();
		this.fVideo.volume = media.volume;
		if (media.rate >= 0) 	this.fVideo.playbackRate = media.rate;
		if (media.mdate >= 0)	this.fVideo.currentTime = media.mdate;
		// video.fMLS       = this.fVideo.duration * 1000;
		// video.fVDuration = this.fVideo.duration / this.fVideo.playbackRate;
		return true;
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