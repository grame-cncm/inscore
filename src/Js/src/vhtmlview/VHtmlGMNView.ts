///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/guido/libGUIDOEngine.d.ts"/>

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
        let div = this.getHtml();
        let gmn = obj.getGMN();
        
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

/*
 constructor(parent: VHtmlView) {
        super(parent); 
        //this.fSVGContainer = document.createElementNS('http://www.w3.org/2000/svg','svg');
        this.getHtml().className = "inscore-gmn";
        //this.getHtml().appendChild(this.fSVGContainer);
    }
      
    updateView	(obj: IGuidoCode) : void {           	
        let scale = obj.fPosition.getScale();
		let w = this.relative2SceneWidth( obj.fPosition.getWidth() ) * scale;
		let h = this.relative2SceneHeight( obj.fPosition.getHeight() ) * scale;
    	this.updateSvgSize (w, h);   
        //this.fSVGContainer.setAttribute('width', w.toString());
        //this.fSVGContainer.setAttribute('height', h.toString()); 
		//let rx = w/2;
		//let ry = h/2;
        //this.fSVGContainer.setAttribute('cx', rx.toString());
        //this.fSVGContainer.setAttribute('cy', ry.toString());
        //this.fSVGContainer.setAttribute('rx', rx.toString());
        //this.fSVGContainer.setAttribute('ry', ry.toString());
        let elt = this.getHtml();
        elt.style.height = "auto";
        elt.style.width = "auto";                

		this.updateObjectSize (obj);
		super.updateView(obj);
        this.updateGMN(obj);
        
     
        //this.fSVGContainer.style.fill = obj.fColor.getRGBString();
*/