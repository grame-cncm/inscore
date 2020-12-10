
///<reference path="JSAutoSize.ts"/>

class JSImageView extends JSAutoSize 
{
    fImage: HTMLImageElement;
    fScale: number;

    constructor(parent: JSObjectView) {
		let div = document.createElement('div');
        let img = document.createElement('img');
        // an additional div to cope with synchronisation issue:
        // broswers don't support div in image div
        div.appendChild (img);
        super(div, parent); 
        this.fImage = img;
        this.fScale = 1;
        this.getElement().className = "inscore-img";
    }

    clone (parent: JSObjectView) : JSObjectView { 
        let img = new JSImageView(parent);
        img.fImage.src = this.fImage.src;
        return img; 
    }

	updateDimensions(pos: OPosition) : void {}  // don't update image dimensions (use scale)
    // image scale is relative to the parent, by default fill the parent element (scale 1) 
    getScale(scale: number) : number {  
		let elt = this.getElement().parentElement;
        let rw = this.fImage.clientWidth / elt.clientWidth;
        let rh = this.fImage.clientHeight / elt.clientHeight;
        this.fScale = scale / Math.max(rw, rh);
        return this.fScale;
    }

	toString() : string			{ return "JSImageView"; }
	getSyncRatio()	: number    { return 1; }   // no scaling for images, appearance is already preserved 
    getAutoSize() : Point       { return { x: this.fImage.clientWidth, y: this.fImage.clientHeight }; }

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
        this.fImage.src  = obj.getFile();
        return this.updateSizeASync (objid);
	}
    
	setShadow(elt: HTMLElement, val: OShadow): void {
		this.fImage.style.boxShadow = `${val.xOffset}px ${val.yOffset}px ${val.blur}px ${val.color}`
	}
}