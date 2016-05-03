
///<reference path="SvgFactory.ts"/>
///<reference path="VHtmlView.ts"/>

class VHtmlRectView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
//      super( SvgFactory.createSvg('rect'), parent); 
        super( document.createElement('div'), parent); 
    	let div = this.getDiv();
        div.className = "rect";
        parent.getDiv().appendChild (div);
    }    

	updateView	( obj: IObject) : void {
		this.updatePos (obj);
		this.updateColor (obj);
	}
}