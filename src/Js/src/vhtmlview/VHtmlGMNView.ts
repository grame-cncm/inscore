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
        this.updateGMN(obj);
		this.updateObjectSize (obj);

        let scale = obj.fPosition.getScale();
		let w = this.relative2SceneWidth( obj.fPosition.getWidth() ) * scale;
		let h = this.relative2SceneHeight( obj.fPosition.getHeight() ) * scale;
    	this.updateSvgSize (w, h);   
        
        console.log('w : ' + w + ' / h : ' + h + ' / scale : ' + scale);
        //console.log(obj.fPosition.getWidth());
        
        this.fSVG.setAttribute('width', w.toString());
        this.fSVG.setAttribute('height', h.toString()); 
		let rx = w/2;
	    let ry = h/2;
        this.fSVG.setAttribute('cx', rx.toString());
        this.fSVG.setAttribute('cy', ry.toString());
        this.fSVG.setAttribute('rx', rx.toString());
        this.fSVG.setAttribute('ry', ry.toString());
        let elt = this.getHtml();
        elt.style.height = "auto";
        elt.style.width = "auto";                

		super.updateView(obj);
	}
       
    updateGMN(obj: IGuidoCode) {
        let div = this.getHtml();
        let gmn = obj.getGMN();
        
        let guidoEngine = new Module.GuidoEngineAdapter;
        guidoEngine.init();        
        let p = guidoEngine.openParser();
	    let ar = guidoEngine.string2AR(p, gmn);
	    guidoEngine.closeParser(p);
        
        let gr = guidoEngine.ar2gr(ar);
	    let result = guidoEngine.gr2SVG(gr, 1, true, 0);
        
	    guidoEngine.freeGR(gr);
	    guidoEngine.freeAR(ar);    
          
        this.fSVG.innerHTML = result;
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