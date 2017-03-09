///<reference path="VHtmlAutoSize.ts"/>
///<reference path="../model/IVideo.ts"/>

//interface RefreshMethod 	{ (): void; }

class VHtmlVideoView extends VHtmlAutoSize {
    fVideo: HTMLVideoElement;
    
    constructor(parent: VHtmlView) {
		let video = document.createElement('video');
        super(video, parent); 
        this.fVideo = video;
        this.getHtml().className = "inscore-video";
    }     
    
	updateView	( obj: IObject) : void {
		let video = <IVideo>obj;
        this.fVideo.src  = video.getFile();
        super.autoSizeEffects(obj);
        super.updateView(obj);
	}  
    
	getAutoElement() : HTMLElement 	{ return this.fVideo; }
}
