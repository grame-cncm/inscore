///<reference path="VHtmlSvg.ts"/>
///<reference path="SvgFactory.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

interface RefreshMethod 	{ (): void; }

class VHtmlGMNView extends VHtmlSvg {
	static fGMNScale = 2.6;		// scaling applied to get homogeneous size with inscore app
    
    constructor(parent: VHtmlView) {
        super(parent); 
        this.getHtml().className = "inscore-gmn";
    }

	getSize (obj: IObject):  {w: number, h: number } {
		let strokeWidth = obj.fPenControl.getPenWidth();
        let w = this.fSVG.clientWidth + strokeWidth;
        let h = this.fSVG.clientHeight + strokeWidth;
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
        let w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        let h = this.scene2RelativeHeight(this.fSVG.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}
}
