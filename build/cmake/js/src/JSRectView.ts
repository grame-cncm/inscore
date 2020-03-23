
///<reference path="JSSVGView.ts"/>

class JSRectView extends JSSvgView {
    protected fRect: SVGRectElement;
    
    constructor(parent: JSObjectView) {
		super(parent);
        this.fRect = document.createElementNS('http://www.w3.org/2000/svg','rect'); 
        this.getElement().className = "inscore-rect";
    	this.fSVG.appendChild(this.fRect)
    }    

    getSVGTarget() : SVGShape  { return this.fRect; }


    updateDimensions(pos: OPosition, elt: HTMLElement) : void {
		this.fRect.style.width = this.relative2SceneWidth(pos.width) + "px";
        this.fRect.style.height = this.relative2SceneHeight(pos.height) + "px";
        super.updateDimensions (pos, elt);
	}
    // getSVGTarget() : SVGSVGElement  { return this.fRect; }

	// updateView	( obj: IObject) : void {
	// 	super.updateView(obj);
	// 	let size = this.getInnerSize(obj);
    //     this.updateCommonSVG(obj, size.w, size.h);

    //     let rect = <IRect>obj;
    //     let radius = rect.getRadius();
    //     if (radius) {
	//         this.fRect.setAttribute('rx', radius[0].toString());
	//         this.fRect.setAttribute('ry', radius[1].toString());
	//     }
    // }
}