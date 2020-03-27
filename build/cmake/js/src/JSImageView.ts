
///<reference path="JSAutoSize.ts"/>

class JSImageView extends JSAutoSize 
{
    fImage: HTMLImageElement;

    constructor(parent: JSObjectView) {
		let img = document.createElement('img');
        super(img , parent); 
        this.fImage = img;
        this.getElement().className = "inscore-img";
    }    

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
        this.fImage.src  = obj.getFile();
		return super.updateSpecial (obj, objid );
	}

	// setShadow (params: Array<number>) : void {
	// 	let color = new IColor( params.slice(2,6) );
	// 	this.getHtml().style.filter = "drop-shadow(" + color.getCSSRGBAString() + " "+ params[0] +"px " + params[1] +"px " + params[6] +"px)";
	// }

	// getAutoElement() : HTMLElement 	{ return this.fImage; }
}