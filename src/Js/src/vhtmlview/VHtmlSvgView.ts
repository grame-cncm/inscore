
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
        if (svg.modif) this.fSVG.innerHTML = svg.svgCode;
              
        // on récupère la taille de fSVG pour l'écrire dans le modele
        this.updateObjectSize (obj);
        
        // update de la couleur et de la position => on récupère dans le modèle pour
        // pour changer les propriétés de la div
		super.updatePos(obj);
        super.updatePenControl(obj);

        // mis à jour de fSVG        
        let elt = this.getHtml(); 
        this.updateSvgSize (elt.clientWidth, elt.clientHeight);

        this.fSVG.style.fill = obj.fColor.getRGBString();

	}   
 
    updateSVG(obj: IObject) : { svgCode: string, modif: boolean } {
        if (obj.isNewData()) {
            let svg = <ISVG>obj;
            return { svgCode: svg.getSvg(), modif: true }    
        } 
    
        return { svgCode: null, modif: false };     
    }
    
	_updateView	( obj: IObject) : RefreshMethod { return () => this.updateView (obj); }

	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        let h = this.scene2RelativeHeight(this.fSVG.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}

	getTransform (obj: IObject): string {
		let scale 	= this.autoScale(obj) * VHtmlGMNView.fGMNScale;
		return super.getTransform(obj) + ` scale(${scale})`;
	}            
}