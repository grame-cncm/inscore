
///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>

class VHtmlEllipseView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( SvgFactory.createSvg('ellipse'), parent); 
    }    
}