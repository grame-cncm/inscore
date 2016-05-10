
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IImage.ts"/>

class VHtmlImageView extends VHtmlView {
    
    fImage: HTMLImageElement;
    constructor(parent: VHtmlView) {
        super( document.createElement('div'), parent); 
    	let div = this.getDiv();
        div.className = "inscore-img";
    }    

	getScale (obj: IObject): number { return obj.getRScale();  }
	updateView	( obj: IObject) : void {
		let img = <IImage>obj;
    	let div = this.getDiv();
    	if (!this.fImage) {
	    	this.fImage = document.createElement('img');
	    	this.fImage.className = "inscore-img";
	    	div.appendChild(this.fImage);
	    }
        this.fImage.src  = img.getFile();
        div.style.height = "auto";
        div.style.width = "auto";
		this.updateObjectSize (obj);
		super.updateView(obj);
	}

	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fImage.clientWidth);
        let h = this.scene2RelativeHeight(this.fImage.clientHeight);

//console.log("VHtmlImageView updateObjectSize " + w + " " + h);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
	}

	getTransform (obj: IObject): string {
		let scale 	= obj.getRScale();
		return super.getTransform(obj) + ` scale(${scale})`;
	}
}
