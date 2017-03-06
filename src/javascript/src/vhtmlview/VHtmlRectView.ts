
///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/IRect.ts"/>

class VHtmlRectView extends VHtmlSvg {
    protected fRect: SVGRectElement;
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fRect = document.createElementNS('http://www.w3.org/2000/svg','rect'); 
        this.getHtml().className = "inscore-rect";
    	this.fSVG.appendChild(this.fRect)
    }    

	updateView	( obj: IObject) : void {
		super.updateView(obj);
		let size = this.getInnerSize(obj);
        let rect = <IRect>obj;
        let radius = rect.getRadius();
        this.updateSizeAndBrush(<IRectShape>obj, this.fRect, size.w, size.h);
        //     this.fRect.setAttribute('width', size.w.toString());
        //     this.fRect.setAttribute('height', size.h.toString());
       // this.fRect.style.fill = obj.fColor.getRGBString();
        this.fRect.setAttribute('rx', radius[0].toString());
        this.fRect.setAttribute('ry', radius[1].toString());
        this.fRect.style.transform = this.strokeTranslate(obj);
    }
}