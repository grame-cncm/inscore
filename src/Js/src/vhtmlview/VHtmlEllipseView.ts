
///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>

class VHtmlEllipseView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( SvgFactory.createSvg('ellipse'), parent); 
        this.getHtml().className = "inscore-ellipse";
    }    

	updateView	( obj: IObject) : void {
		this.updatePos (obj);
		this.updateColor (obj);
	}
}