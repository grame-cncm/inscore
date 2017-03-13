
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

	abstract getAutoElement() : HTMLElement;
}