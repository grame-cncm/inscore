
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlSvg.ts"/>

class VHtmlSvgView extends VHtmlSvg {

    constructor(parent: VHtmlView) {
        super(parent); 
    	this.getHtml().className = "inscore-svg";
    } 
    
    updateView	(obj: IObject) : void {           	
        // si le code gmn a changé, on le charge
        let svg = this.updateSVG(obj);
        if (svg.modif) {
            this.fSVG.innerHTML = svg.svgCode;  
            this.updateObjectSize(obj);
            let svgContain = this.fSVG.querySelectorAll('svg')[0].getBoundingClientRect();
            this.updateSvgSize (svgContain.width, svgContain.height);            
            this.updateSvgPos(svgContain.left, svgContain.top);
        }
		super.updatePos(obj);
        super.updatePenControl(obj);
	}   
 
    updateSVG(obj: IObject) : { svgCode: string, modif: boolean } {
        if (obj.isNewData()) {
            let svg = <ISVG>obj;
            return { svgCode: svg.getSvg(), modif: true }    
        } 
    
        return { svgCode: null, modif: false };     
    }
    
	_updateView	( obj: IObject) : RefreshMethod { return () => this.updateView (obj); }
    
    updatePos (obj: IObject): void {
		let pos 	= obj.getPosition();
		let size 	= obj.getSize();
		let scale 	= this.getScale(obj);
		let z		= obj.fPosition.getZOrder();
        let w  		= this.relative2SceneWidth (size.w) * scale;
        let h 		= this.relative2SceneHeight (size.h) * scale;
        let left  	= this.relative2SceneX (pos.x) - w/2.0;
        let top 	= this.relative2SceneY (pos.y) - h/2.0;

    	let elt = this.getHtml();
        //elt.style.left = left + 'px';
        //elt.style.top = top + 'px';

        //elt.style.width  = w +"px";
        //elt.style.height = h +"px";
        //elt.style.left 	=  left + "px";
        //elt.style.top 	=  top + "px";
        //elt.style.zIndex = z.toString();
		//elt.style.transform  = this.getTransform(obj);
        //elt.style.visibility  = obj.fPosition.getVisible() ? "inherit" : "hidden";
        //this.setPos( top, left, w, h);
	}
    
	updateObjectSize ( obj: IObject) : void {
        let svgContain = this.fSVG.querySelectorAll('svg')[0].getBoundingClientRect();
        console.log(svgContain);
        let w = this.scene2RelativeWidth(svgContain.width);
        let h = this.scene2RelativeHeight(svgContain.height);
        let x = this.scene2RelativeX(svgContain.left) - w/2;
        let y = this.scene2RelativeY(svgContain.top) - h/2;
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		//obj.fPosition.setXPos (x);
		//obj.fPosition.setYPos (y);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}

	getTransform (obj: IObject): string {
		let scale 	= this.autoScale(obj) * VHtmlGMNView.fGMNScale;
		return super.getTransform(obj) + ` scale(${scale})`;
	}  

    updateSvgSize (w: number, h: number): void { 
    	let elt = this.getHtml();
		this.fPixWidth = w ? w : 1; 
		this.fPixHeight = h ? h : 1; 		
		elt.style.height = this.fPixHeight +"px";
        elt.style.width  = this.fPixWidth +"px";
		this.fSVG.style.height = this.fPixHeight +"px";
        this.fSVG.style.width  = this.fPixWidth +"px";
	} 

	updateSvgPos (x: number, y: number): void { 
    	let elt = this.getHtml();		
		elt.style.left = x +"px";
        elt.style.top  = y +"px";
		this.fSVG.style.left = x +"px";
        this.fSVG.style.top  = y +"px";
	}              
}