
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IHtml.ts"/>

class VHtmlHtmlView extends VHtmlView {

    constructor(parent: VHtmlView) {
		super( document.createElement('div'), parent); 
    	let div = this.getDiv();
        div.className = "inscore-html";
    }    

	getText	( obj: IText) : string { return obj.getText(); }

	getScale (obj: IObject): number { return 1;  }
	updateColor (obj: IObject): void {
        if (obj.fColor.modified())
	        this.fDiv.style.color = obj.fColor.getRGBString();
	}

	updateView	( obj: IObject) : void {
		let t = <IText>obj;
    	let div = this.getDiv();
        div.innerHTML  = this.getText(t);
        div.style.height = "auto";
        div.style.width = "auto";
		this.updateObjectSize (obj);
		super.updateView(obj);
	}

	getTransform (obj: IObject): string {
		let scale 	= obj.fPosition.getScale();
		return super.getTransform(obj) + ` scale(${scale})`;
	}
}