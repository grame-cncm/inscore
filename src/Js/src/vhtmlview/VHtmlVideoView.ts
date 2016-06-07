///<reference path="VHtmlView.ts"/>
///<reference path="../model/IVideo.ts"/>

interface RefreshMethod 	{ (): void; }

class VHtmlVideoView extends VHtmlView {
    fVideo: HTMLVideoElement;
    
    constructor(parent: VHtmlView) {
		let video = document.createElement('video');
        super(video, parent); 
        this.fVideo = video;
        this.getHtml().className = "inscore-video";
    }     
    
	// getScale is intended to catch the div using auto height and width (like text, html...)
	getScale (obj: IObject): number 	{ return 1;  }    

	updateView	( obj: IObject) : void {
		let video = <IVideo>obj;
    	let elt = this.getHtml();
        elt.setAttribute("controls","");
        
        this.fVideo.src  = video.getFile();
        elt.style.height = "auto";
        elt.style.width = "auto";
		this.updateObjectSize (obj);
		super.updateView(obj);
	}  
    
	_updateView	( obj: IObject) : RefreshMethod { return () => this.updateView (obj); }

	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fVideo.clientWidth);
        let h = this.scene2RelativeHeight(this.fVideo.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}

	getTransform (obj: IObject): string {
		let scale 	= this.autoScale(obj);
		return super.getTransform(obj) + ` scale(${scale})`;
	}      
}