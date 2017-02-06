
///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>

class VHtmlCurveView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( SvgFactory.createSvg('curve'), parent);
        let div = this.getHtml();
        div.className = "inscore-curve";  
    }    
}