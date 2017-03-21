
///<reference path="VHtmlView.ts"/>
///<reference path="../model/ISvg.ts"/>

class VHtmlSvgView extends VHtmlView {

    constructor(parent: VHtmlView) {
        super(document.createElement('div'), parent); 
    	this.getHtml().className = "inscore-svg";
    } 
    
    updateView	(obj: IObject) : void {           	
        if (obj.isNewData()) {
            let svg = <ISVG>obj;
            this.getHtml().innerHTML = svg.getSvg();
            this.updateObjectSize(obj);
        }
    	super.updateView(obj);
	}   

	getSize (obj: IObject):  {w: number, h: number } {
		let strokeWidth = obj.fPenControl.getPenWidth();
        let w = this.getHtml().clientWidth + strokeWidth;
        let h = this.getHtml().clientHeight + strokeWidth;
		return { w: (w ? w : 1), h: (h ? h : 1) };
	}
}