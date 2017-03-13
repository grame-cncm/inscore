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
        super.updateView(obj);
	}  
 
	setShadow (params: Array<number>) : void {
		let color = new IColor( params.slice(2,6) );
		this.getHtml().style.filter = "drop-shadow(" + color.getCSSRGBAString() + " "+ params[0] +"px " + params[1] +"px " + params[6] +"px)";
	}
   
	getAutoElement() : HTMLElement 	{ return this.fVideo; }
}
