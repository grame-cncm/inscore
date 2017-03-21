
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

interface RefreshMethod 	{ (): void; }

class VHtmlGMNView extends VHtmlView {
	static fGMNScale = 2.3;		// scaling applied to get homogeneous size with inscore app
	protected fClientWidth = 0;
	protected fClientHeight = 0;
    
    constructor(parent: VHtmlView) {
        super(document.createElement('div'), parent); 
        this.getHtml().className = "inscore-gmn";
    }

	getViewScale (obj: IObject): number {
		// apply scaling to get a size similar to native application
		return super.getViewScale(obj) * VHtmlGMNView.fGMNScale;
	}

	getClientSize (obj: IObject):  {w: number, h: number } {
		if (!this.fClientWidth) {
	        let svg = this.getsvg(this.getHtml());
	        let box = svg.viewBox.baseVal;
        	this.fClientWidth = box.width;
        	this.fClientHeight = box.height;
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
            this.getHtml().innerHTML = gmn.getSVG();    
        }   
    	this.updateObjectSize (obj);     
    	super.updateView(obj);
	}
	
	getsvg (root: Node): SVGSVGElement {
		let g : Node;
	    let childs = root.childNodes;
		for (let i = 0; i < childs.length && !g; i++) {
			if (childs[i].nodeName == 'svg') {
				g = childs[i];
				break;
			}
        }
        return <SVGSVGElement>g;
	}
	
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
		let color = obj.fColor.getRGBString();
		let alpha = obj.fColor.getSVGA();
		let g = this.getFirstSVGGroup (this.getHtml());
		if (g) {
			g.style.stroke = color; 
			g.style.strokeOpacity = alpha.toString(); 
			g.style.fill = color; 
			g.style.fillOpacity = alpha.toString(); 
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
