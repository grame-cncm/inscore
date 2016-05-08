
///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>

class VHtmlEllipseView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( SvgFactory.createSvg('ellipse'), parent); 
//        super( document.createElement('div'), parent); 
    	let div = this.getDiv();
        div.className = "inscore-ellipse";
    }    

	updateView	( obj: IObject) : void {
		this.updatePos (obj);
		this.updateColor (obj);
	}
}