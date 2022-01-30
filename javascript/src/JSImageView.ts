
///<reference path="JSAutoSize.ts"/>

class JSImageView extends JSAutoSize 
{
    fImage: HTMLImageElement;

    constructor(parent: JSObjectView) {
		let div = document.createElement('div');
        let img = document.createElement('img');
        // an additional div to cope with synchronisation issue:
        // broswers don't support div in image div
        div.appendChild (img);
        super(div, parent); 
        this.fImage = img;
        this.fImage.style.width = 100+"%";
        this.fImage.style.height = 100+"%";
    }

    clone (parent: JSObjectView) : JSObjectView { 
        let img = new JSImageView(parent);
        img.fImage.src = this.fImage.src;
        return img; 
    }

	toString() : string			{ return "JSImageView"; }
    getAutoSize() : Point       { return { x: this.fImage.naturalWidth, y: this.fImage.naturalHeight }; }
    getScale(scale: number) : number {  return scale; }

	updateSpecial ( obj: INScoreObject)	: boolean {
        this.fImage.src  = obj.getFile();
        this.fImage.id = obj.getID();
        return this.updateSizeASync (obj);
	}
    
	setShadow(elt: HTMLElement, val: OShadow): void {
		this.fImage.style.boxShadow = `${val.xOffset}px ${val.yOffset}px ${val.blur}px ${val.color}`
	}
}