
///<reference path="VHtmlAutoSize.ts"/>
///<reference path="../model/IImage.ts"/>

class VHtmlImageView extends VHtmlAutoSize 
{
    fImage: HTMLImageElement;

    constructor(parent: VHtmlView) {
		let img = document.createElement('img');
        super(img , parent); 
        this.fImage = img;
        this.getHtml().className = "inscore-img";
    }    

	updateView	( obj: IObject) : void {
		let img = <IImage>obj;
        this.fImage.src  = img.getFile();
        super.autoSizeEffects(obj);
        super.updateView(obj);
	}

	getAutoElement() : HTMLElement 	{ return this.fImage; }
}
