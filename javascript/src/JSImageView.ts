
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
    clone (parent: JSObjectView) : JSObjectView { return new JSImageView(parent); }

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
        this.fImage.src  = obj.getFile();
		return super.updateSpecial (obj, objid );
	}
    
	setShadow(elt: HTMLElement, val: OShadow): void {
		this.fImage.style.boxShadow = `${val.xOffset}px ${val.yOffset}px ${val.blur}px ${val.color}`
	}
}