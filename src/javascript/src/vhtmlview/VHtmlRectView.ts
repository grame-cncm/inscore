
///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/IRect.ts"/>

class VHtmlRectView extends VHtmlSvg {
    protected fRect: SVGRectElement;
    protected fPixWidth: number;		
    protected fPixHeight: number;	
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fRect = document.createElementNS('http://www.w3.org/2000/svg','rect'); 
        this.getHtml().className = "inscore-rect";
    	this.fSVG.appendChild(this.fRect)
    }    

	updateView	( obj: IObject) : void {
		super.updateView(obj);
        let rect = <IRect>obj;
		let scale = rect.fPosition.getScale();
		let w = this.relative2SceneWidth( rect.fPosition.getWidth() ) * scale;
		let h = this.relative2SceneHeight( rect.fPosition.getHeight() ) * scale;
    	this.updateSvgSize (w, h);
        this.fRect.setAttribute('width', w.toString());
        this.fRect.setAttribute('height', h.toString());
        this.fRect.style.fill = obj.fColor.getRGBString();
        let radius = rect.getRadius();
		let rx = radius[0];
        let ry = radius[1];    
        this.fRect.setAttribute('rx', rx.toString());
        this.fRect.setAttribute('ry', ry.toString());
	}
}