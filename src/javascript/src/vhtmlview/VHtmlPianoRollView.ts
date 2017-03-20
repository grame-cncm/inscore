
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlGMNView.ts"/>

class VHtmlPianoRollView extends VHtmlGMNView {
    
    constructor(parent: VHtmlView) {
        super(parent); 
        this.getHtml().className = "inscore-pianoroll";
    }        

	// avoid the VHtmlGMNView specific scaling
	getViewScale (obj: IObject): number 	{ return obj.fPosition.getScale() * this.getParentsScale(obj); }

	updateObjectSize ( obj: IObject) : void {}  // do nothing, the size is user defined
}