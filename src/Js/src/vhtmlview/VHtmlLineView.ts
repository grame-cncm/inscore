
///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>

class VHtmlLineView extends VHtmlView {
    
    constructor(parent: VHtmlView) {
        super( SvgFactory.createSvg('line'), parent); 
    }    
}