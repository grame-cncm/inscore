///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

class VHtmlGMNView extends VHtmlSvg {
    
    constructor(parent: VHtmlView) {
        super(parent); 
        this.getHtml().className = "inscore-gmn";
    }
      
    updateView	(obj: IObject) : void {           	
        let gmn = this.updateGMN(obj);
        if (gmn.modif) this.fSVG.innerHTML = gmn.gmnCode;
        
        let elt = this.getHtml();
    	//this.updateSvgSize (elt.clientWidth, elt.clientHeight);   
		this.updateObjectSize (obj);
		super.updateView(obj);



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
	}
       
    updateGMN(obj: IObject) : { gmnCode: string, modif: boolean } {
        if (obj.isNewData()) {
            let gmn = <IGuidoCode>obj;
            return { gmnCode: gmn.getGMNsvg(), modif: true }    
        } 
    
        return { gmnCode: null, modif: false };     
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