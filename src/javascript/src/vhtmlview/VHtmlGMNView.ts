///<reference path="VHtmlView.ts"/>
///<reference path="SvgFactory.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

class VHtmlGMNView extends VHtmlSvg {
	static fGMNScale = 2.6;		// scaling applied to get homogeneous size with inscore app
    
    constructor(parent: VHtmlView) {
        super(parent); 
        this.getHtml().className = "inscore-gmn";
    }
      
	getScale (obj: IObject): number 	{ return 1;  }
    updateView	(obj: IObject) : void {           	
        // si le code gmn a changé, on le charge
        let gmn = this.updateGMN(obj);
        if (gmn.modif) this.fSVG.innerHTML = gmn.gmnCode;
              
        // on récupère la taille de fSVG pour l'écrire dans le modele
        this.updateObjectSize (obj);
        
        // update de la couleur et de la position => on récupère dans le modèle pour
        // pour changer les propriétés de la div
		super.updateView(obj);

        // mis à jour de fSVG        
        let elt = this.getHtml(); 
        this.updateSvgSize (elt.clientWidth, elt.clientHeight);
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

	getTransform (obj: IObject): string {
		let scale 	= this.autoScale(obj) * VHtmlGMNView.fGMNScale;
		return super.getTransform(obj) + ` scale(${scale})`;
	}
}
