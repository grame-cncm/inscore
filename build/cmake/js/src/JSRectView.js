
class JSRectView extends JSSvgElement {
    
    constructor(parent) {
		super(parent);
        this.fRect = document.createElementNS('http://www.w3.org/2000/svg','rect'); 
        this.getElement().className = "inscore-rect";
    	this.fSVG.appendChild(this.fRect)
    }    

    getSVGTarget()  { return this.fRect; }

	updateView	( obj ) {
		super.updateView(obj);
		let size = this.getInnerSize(obj);
//        this.updateCommonSVG(obj, size.w, size.h);

        // let radius = obj.getRadius();
        // if (radius) {
	    //     this.fRect.setAttribute('rx', radius[0].toString());
	    //     this.fRect.setAttribute('ry', radius[1].toString());
	    // }
    }
}