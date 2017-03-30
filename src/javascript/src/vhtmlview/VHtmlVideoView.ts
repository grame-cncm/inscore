///<reference path="VHtmlAutoSize.ts"/>
///<reference path="../model/IVideo.ts"/>

//interface RefreshMethod 	{ (): void; }

class VHtmlVideoView extends VHtmlAutoSize {
    fVideo: HTMLVideoElement;
	fFile : string;
    
    constructor(parent: VHtmlView) {
		let video = document.createElement('video');
        super(video, parent); 
        this.fVideo = video;
		this.fFile = "";
        this.getHtml().className = "inscore-video";
    }     
    
	updateView	( obj: IObject) : void {
		let video = <IVideo>obj;
        if (this.fFile != video.getFile() || this.fFile == "") {
			this.fVideo.src = video.getFile();
			this.fFile = video.getFile();
		}
        super.updateView(obj);
		this.updateVideoControl(video);
	}
 
	setShadow (params: Array<number>) : void {
		let color = new IColor( params.slice(2,6) );
		this.getHtml().style.filter = "drop-shadow(" + color.getCSSRGBAString() + " "+ params[0] +"px " + params[1] +"px " + params[6] +"px)";
	}
   
	getAutoElement() : HTMLElement 	{ return this.fVideo; }

	updateVideoControl(video: IVideo) : void {
		if (video.modified()){
			video.fPlay ? this.fVideo.play() : this.fVideo.pause();
			this.fVideo.volume = video.fVolume;
			this.fVideo.playbackRate = video.fRate;
			this.fVideo.currentTime += video.fVDate;
		}
	}
}
