
///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

interface RefreshMethod 	{ (): void; }

class VHtmlGMNView extends VHtmlSvg {
	static fGMNScale = 2.3;		// scaling applied to get homogeneous size with inscore app
    
    constructor(parent: VHtmlView) {
        super(parent); 
        this.getHtml().className = "inscore-gmn";
    }
    getSVGTarget() : SVGShape  { return this.fSVG; }

	getViewScale (obj: IObject): number {
		// this is to ensure a size similar to the native app version
		return super.getViewScale(obj) * VHtmlGMNView.fGMNScale; 
	}

	getSize (obj: IObject):  {w: number, h: number } {
        let bbox = this.fSVG.getBoundingClientRect();
		var cw = bbox.right - bbox.left;
		var ch = bbox.bottom - bbox.top;

		let strokeWidth = obj.fPenControl.getPenWidth();
        let w = cw + strokeWidth;
        let h = ch + strokeWidth;
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
	
	private getFirstSVGGroup (root: Node): SVGSVGElement {
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
        if (obj.fColor.modified()) {
	        let color = obj.fColor.getRGBString();
	        let alpha = obj.fColor.getSVGA();
	        let g = this.getFirstSVGGroup (this.fSVG);
	        if (g) {
   	       		g.style.stroke = color; 
   	       		g.style.strokeOpacity = alpha.toString(); 
    	        g.style.fill = color; 
    	        g.style.fillOpacity = alpha.toString(); 
	        }
        }
    }

	_updateView	( obj: IObject) : RefreshMethod { return () => this.updateView (obj); }

	updateObjectSize ( obj: IObject) : void {
//		let cw = this.fSVG.clientWidth;
//		let ch = this.fSVG.clientHeight;

        let bbox = this.fSVG.getBoundingClientRect();
		var cw = bbox.right - bbox.left;
		var ch = bbox.bottom - bbox.top;
        let w = this.scene2RelativeWidth (cw);
        let h = this.scene2RelativeHeight(ch);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}
}
