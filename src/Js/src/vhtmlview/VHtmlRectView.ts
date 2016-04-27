
///<reference path="VHtmlView.ts"/>

class VHtmlRectView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( SvgFactory.createSvg('rect'), parent); 
    }    
}