
///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/IEllipse.ts"/>

class VHtmlEllipseView extends VHtmlSvg {
    protected fEllipse: SVGEllipseElement;
    protected fPixWidth: number;		// the element width in pixels
    protected fPixHeight: number;		// the element height in pixels
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fEllipse = document.createElementNS('http://www.w3.org/2000/svg','ellipse'); 
        this.getHtml().className = "inscore-ellipse";
    	this.fSVG.appendChild(this.fEllipse)
    }    

	updateView	( obj: IObject) : void {
		let scale = obj.fPosition.getScale();
		let w = this.relative2SceneWidth( obj.fPosition.getWidth() ) * scale;
		let h = this.relative2SceneHeight( obj.fPosition.getHeight() ) * scale;
    	this.updateSvgSize (w, h);
        this.fEllipse.setAttribute('width', w.toString());
        this.fEllipse.setAttribute('height', h.toString());
        this.fEllipse.style.fill = obj.fColor.getRGBString();
		let rx = 4;
		let ry = 4;
        this.fEllipse.setAttribute('cx', rx.toString());
        this.fEllipse.setAttribute('cy', ry.toString());
        this.fEllipse.setAttribute('rx', rx.toString());
        this.fEllipse.setAttribute('ry', ry.toString());
		this.updatePos(obj);
	}
}