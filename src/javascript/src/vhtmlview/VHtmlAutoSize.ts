
///<reference path="../model/IObject.ts"/>
///<reference path="VHtmlView.ts"/>

interface RefreshMethod 	{ (): void; }

abstract class VHtmlAutoSize extends VHtmlView {

    constructor(elt: HTMLElement, parent: VHtmlView) 	{ super (elt, parent); }

	updateView	( obj: IObject) : void {
    	let elt = this.getHtml();
        elt.style.height = "auto";
        elt.style.width = "auto";
		this.updateObjectSize (obj);
		super.updateView(obj);
	}
	_updateView	( obj: IObject) : RefreshMethod { return () => this.updateView (obj); }

	updateObjectSize ( obj: IObject) : void {
		let target = this.getAutoElement();
        let w = this.scene2RelativeWidth (target.clientWidth);
        let h = this.scene2RelativeHeight(target.clientHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}

	autoSizeEffects(obj: IObject): void {
		if(obj.fEffect.fEffectModified){
			switch(obj.fEffect.fEffectName){
				case effect.kNone : this.getHtml().style.boxShadow = "(0px 0px)";
									this.getHtml().style.filter = "blur(0px)";
									break;
				case effect.kShadow : this.getHtml().style.boxShadow = VHtmlView.getEffects(obj);
					console.log("VHtmlAutoSize autoSizeEffects box-shadow: " + VHtmlView.getEffects(obj));
					break;
				case  effect.kBlur : this.getHtml().style.filter = VHtmlView.getEffects(obj);
				break;
			}
		}
	}

	abstract getAutoElement() : HTMLElement;
}