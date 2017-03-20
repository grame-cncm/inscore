
///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

interface RefreshMethod 	{ (): void; }

class VHtmlGMNView extends VHtmlSvg {
	static fGMNScale = 2.3;		// scaling applied to get homogeneous size with inscore app
	protected fClientWidth = 0;
	protected fClientHeight = 0;
    
    constructor(parent: VHtmlView) {
        super(parent); 
        this.getHtml().className = "inscore-gmn";
    }
    getSVGTarget() : SVGShape  { return this.fSVG; }

	getViewScale (obj: IObject): number {
		// apply scaling to get a size similar to native application
		return super.getViewScale(obj) * VHtmlGMNView.fGMNScale;
	}

	getClientSize (obj: IObject):  {w: number, h: number } {
//		let cw = this.fSVG.clientWidth;		// works on Chrome but not on Firefox
//		let ch = this.fSVG.clientHeight;
		if (!this.fClientWidth) {
        	let bbox = this.fSVG.getBoundingClientRect();
        	this.fClientWidth = bbox.right - bbox.left;
        	this.fClientHeight = bbox.bottom - bbox.top;
        }
		return  { w: this.fClientWidth, h: this.fClientHeight };
	}

	getSize (obj: IObject):  {w: number, h: number } {
        let size = this.getClientSize (obj);
		let strokeWidth = obj.fPenControl.getPenWidth();
        let w = size.w + strokeWidth;
        let h = size.h + strokeWidth;
		return { w: (w ? w : 1), h: (h ? h : 1) };
	}
      
    updateView	(obj: IObject) : void {           	
        // si le code gmn a changé, on le charge
		if (obj.isNewData()) {
            let gmn = <IGuidoCode>obj;
            this.fSVG.innerHTML = gmn.getSVG();    
        }   
    	this.updateObjectSize (obj);     
    	super.updateView(obj);
	}

	updatePenControl(obj:IObject): void 	{ this.basePenControl (obj); }
	
	getFirstSVGGroup (root: Node): SVGSVGElement {
		let g : Node;
	    let childs = root.childNodes;
		for (let i = 0; i < childs.length && !g; i++) {
			if (childs[i].nodeName == 'g') {
				g = childs[i];
				break;
			}
			g = this.getFirstSVGGroup (childs[i]);
        }
        return <SVGSVGElement>g;
	}
	
	updateColor (obj: IObject): void {
//        if (obj.fColor.modified()) {
	        let color = obj.fColor.getRGBString();
	        let alpha = obj.fColor.getSVGA();
	        let g = this.getFirstSVGGroup (this.fSVG);
	        if (g) {
   	       		g.style.stroke = color; 
   	       		g.style.strokeOpacity = alpha.toString(); 
    	        g.style.fill = color; 
    	        g.style.fillOpacity = alpha.toString(); 
//	        }
        }
    }

	_updateView	( obj: IObject) : RefreshMethod { return () => this.updateView (obj); }

	updateObjectSize ( obj: IObject) : void {
		if (obj.fPosition.getWidth()) return;

        let size = this.getClientSize (obj);
        let w = this.scene2RelativeWidth (size.w);
        let h = this.scene2RelativeHeight(size.h);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}
}
