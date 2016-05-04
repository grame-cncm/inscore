
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IText.ts"/>

class VHtmlTextView extends VHtmlView {

    constructor(parent: VHtmlView) {
		super( document.createElement('div'), parent); 
    	let div = this.getDiv();
        div.className = "txt";
        div.style.verticalAlign = "middle";
        parent.getDiv().appendChild (div);
    }    

	updateView	( obj: IObject) : void {
		let t = <IText>obj;
    	let div = this.getDiv();
        div.innerHTML  = "<pre>" + t.getText() +"</pre>";
        div.style.height = "auto";
        div.style.width = "auto";
        let w = this.scene2RelativeWidth(div.clientWidth);
        let h = this.scene2RelativeHeight(div.clientHeight);

		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		this.updatePos (obj);
		this.updateColor (obj);
	}

	getScale (obj: IObject): number { return 1;  }
	updateColor (obj: IObject): void {
        if (obj.fColor.modified())
	        this.fDiv.style.color = obj.fColor.getRGBString();
	}

	getTransform (obj: IObject): string {
		let scale 	= obj.fPosition.getScale();
		return super.getTransform(obj) + ` scale(${scale})`;
	}
}