///<reference path="VHtmlImageView.ts"/>
///<reference path="../model/ISVGf.ts"/>

class VHtmlSVGfView extends VHtmlImageView 
{
    constructor(parent: VHtmlView) {
        super(parent); 
        this.getHtml().className = "inscore-svgf";
    }    
}