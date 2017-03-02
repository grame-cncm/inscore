
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlSvg.ts"/>
///<reference path="VHtmlGMNView.ts"/>
///<reference path="../model/ISvg.ts"/>

class VHtmlSvgView extends VHtmlSvg {

    constructor(parent: VHtmlView) {
        super(parent); 
    	this.getHtml().className = "inscore-svg";
    } 
    
    updateView	(obj: IObject) : void {           	
        // si le code gmn a changé, on le charge
        if (obj.isNewData()) {
            let svg = <ISVG>obj;
            this.fSVG.innerHTML = svg.getSvg();
            this.updateObjectSize(obj);
        }
    	super.updateView(obj);
	}   

	getSize (obj: IObject):  {w: number, h: number } {
        let svgsize = this.fSVG.querySelectorAll('svg')[0].getBoundingClientRect();
		let strokeWidth = obj.fPenControl.getPenWidth();
        let w = svgsize.width + strokeWidth;
        let h = svgsize.height + strokeWidth;
		return { w: (w ? w : 1), h: (h ? h : 1) };
	}
}