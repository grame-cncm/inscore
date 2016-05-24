///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

class VHtmlGMNView extends VHtmlSvg {
    //fSVGContainer: SVGElement;
    
    constructor(parent: VHtmlView) {
        super(parent); 
        //this.fSVGContainer = document.createElementNS('http://www.w3.org/2000/svg','svg');
        this.getHtml().className = "inscore-gmn";
        //this.getHtml().appendChild(this.fSVGContainer);
    }
      
    updateView	(obj: IGuidoCode) : void {           	
        this.fSVG.innerHTML = this.updateGMN(obj);
        let elt = this.getHtml();
    	this.updateSvgSize (elt.clientWidth*2, elt.clientHeight*2);   
		this.updateObjectSize (obj);
/*
        elt.style.height = "auto";
        elt.style.width = "auto";                
*/
/*
        let scale = obj.fPosition.getScale();
		let w = this.relative2SceneWidth( obj.fPosition.getWidth() ) * scale;
		let h = this.relative2SceneHeight( obj.fPosition.getHeight() ) * scale;
        console.log('w : ' + w + ' / h : ' + h + ' / scale : ' + scale);
*/        
		super.updateView(obj);
	}
       
    updateGMN(obj: IGuidoCode) : string {
        if (obj.isNewData()) {
            return obj.getGMNsvg();    
        } 
               
 /*     
        let div = this.getHtml();
        let gmn = obj.getGMNsvg();
   
        let guidoEngine = new Module.GuidoEngineAdapter;
        guidoEngine.init();        
        let p = guidoEngine.openParser();
	    let ar = guidoEngine.string2AR(p, gmn);
	    guidoEngine.closeParser(p);
        
        let gr = guidoEngine.ar2gr(ar);
	    let result = guidoEngine.gr2SVG(gr, 1, false, 0);
        
	    guidoEngine.freeGR(gr);
	    guidoEngine.freeAR(ar);
        return result;
*/       
    return null;     
    }  

	_updateView	( obj: IGuidoCode) : RefreshMethod { return () => this.updateView (obj); }

	updateObjectSize ( obj: IGuidoCode) : void {
        let w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        let h = this.scene2RelativeHeight(this.fSVG.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}
}
