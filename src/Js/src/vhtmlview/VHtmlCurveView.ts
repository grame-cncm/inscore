
///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>

class VHtmlCurveView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( SvgFactory.createSvg('curve'), parent);
        let div = this.getDiv();
        div.className = "inscore-curve";  
    }    
}