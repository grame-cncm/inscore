
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlSvg.ts"/>
///<reference path="VHtmlGMNView.ts"/>
///<reference path="../model/ISvg.ts"/>

interface RefreshMethod 	{ (): void; }

class VHtmlSvgView extends VHtmlSvg {

    constructor(parent: VHtmlView) {
        super(parent); 
    	this.getHtml().className = "inscore-svg";
    } 
    
    updateView	(obj: IObject) : void {           	
        // si le code gmn a changé, on le charge
        if (obj.isNewData()) {
            let svg = <ISVG>obj;
            this.fSVG.innerHTML = svg.getSvg();
            this.updateObjectSize(obj);
        }
    	super.updateView(obj);
	}   

	getSize (obj: IObject):  {w: number, h: number } {
        let svgsize = this.fSVG.querySelectorAll('svg')[0].getBoundingClientRect();
		let strokeWidth = obj.fPenControl.getPenWidth();
        let w = svgsize.width + strokeWidth;
        let h = svgsize.height + strokeWidth;
		return { w: (w ? w : 1), h: (h ? h : 1) };
	}
 
	_updateView	( obj: IObject) : RefreshMethod { return () => this.updateView (obj); }
	updateObjectSize ( obj: IObject) : void {
		let size = this.getInnerSize (obj);
        let w = this.scene2RelativeWidth(size.w);
        let h = this.scene2RelativeHeight(size.h);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}
}