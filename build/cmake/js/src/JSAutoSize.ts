
///<reference path="JSObjectView.ts"/>


class JSAutoSize extends JSObjectView 
{
    private fSizeSynced = false;

    constructor(elt: HTMLElement, parent: JSObjectView) 	{ 
        super (elt, parent); 
        elt.style.height = "auto";
        elt.style.width  = "auto";
    }

    updateSpecial (obj: INScoreObject, objid: number)	: boolean {
        return this.waitForSize (objid);
    }

	waitForSize (objid: number) : boolean {
        if (!this.fSizeSynced) {
            let elt = this.getElement();
            let w = elt.clientWidth;
            let h = elt.clientHeight;
// console.log("JSAutoSize::waitForSize " + this + " " + w + " -> " + h);
            if (!w || !h)  setTimeout (() => this.waitForSize (objid), 50) ;
            else {
                super.updateObjectSize (objid);
                this.fSizeSynced = true;
                JSObjectView.updateObjectView (this.getId(), objid);
            }    
        }
        return this.fSizeSynced;
	}
}