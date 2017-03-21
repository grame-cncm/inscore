
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
        super.updateView(obj);
	}

	setShadow (params: Array<number>) : void {
		let color = new IColor( params.slice(2,6) );
		this.getHtml().style.filter = "drop-shadow(" + color.getCSSRGBAString() + " "+ params[0] +"px " + params[1] +"px " + params[6] +"px)";
	}

	getAutoElement() : HTMLElement 	{ return this.fImage; }
}
