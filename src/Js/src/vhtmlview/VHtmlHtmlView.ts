
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IHtml.ts"/>

class VHtmlHtmlView extends VHtmlView {

    constructor(parent: VHtmlView) {
		super( document.createElement('div'), parent); 
        this.getHtml().className = "inscore-html";
    }    

	getText	( obj: IText) : string { return obj.getText(); }

	getScale (obj: IObject): number { return obj.getRScale();  }
	updateColor (obj: IObject): void {
        if (obj.fColor.modified())
	        this.getHtml().style.color = obj.fColor.getRGBString();
	}

	updateView	( obj: IObject) : void {
		let t = <IText>obj;
    	let elt = this.getHtml();
        elt.innerHTML  = this.getText(t);
        elt.style.height = "auto";
        elt.style.width = "auto";
		this.updateObjectSize (obj);
		super.updateView(obj);
	}

	getTransform (obj: IObject): string {
		let scale 	= obj.getRScale();
		return super.getTransform(obj) + ` scale(${scale})`;
	}

}