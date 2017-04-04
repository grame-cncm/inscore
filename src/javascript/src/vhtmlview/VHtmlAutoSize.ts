
///<reference path="../model/IObject.ts"/>
///<reference path="VHtmlView.ts"/>

interface RefreshMethod 	{ (): void; }

abstract class VHtmlAutoSize extends VHtmlView {

	protected fClientWidth = 0;
    protected fClientHeight = 0;

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
		let size = this.getClientSize(obj);
		let w = this.scene2RelativeWidth(size.w);
		let h = this.scene2RelativeHeight(size.h);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		if (!w || !h)  setTimeout (this._updateView(obj), 50) ;		
	}

	getClientSize(obj: IObject): { w: number, h: number } {
        if (!this.fClientWidth) {
            let target = this.getAutoElement();
            this.fClientWidth = target.clientWidth;
            this.fClientHeight = target.clientHeight;
        }
        return { w: this.fClientWidth, h: this.fClientHeight };
    }
	abstract getAutoElement() : HTMLElement;
}