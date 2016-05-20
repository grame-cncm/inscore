
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IImage.ts"/>

interface RefreshMethod 	{ (): void; }

class VHtmlImageView extends VHtmlView {
    
    fImage: HTMLImageElement;
    constructor(parent: VHtmlView) {
		let img = document.createElement('img');
        super( img, parent); 
        this.fImage = img;
        this.getHtml().className = "inscore-img";
    }    

	updateView	( obj: IObject) : void {
		let img = <IImage>obj;
    	let elt = this.getHtml();
        this.fImage.src  = img.getFile();
        elt.style.height = "auto";
        elt.style.width = "auto";
		this.updateObjectSize (obj);
		super.updateView(obj);
	}
	_updateView	( obj: IObject) : RefreshMethod { return () => this.updateView (obj); }

	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fImage.clientWidth);
        let h = this.scene2RelativeHeight(this.fImage.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}

	getTransform (obj: IObject): string {
		let scale 	= this.autoScale(obj);
		return super.getTransform(obj) + ` scale(${scale})`;
	}
}
