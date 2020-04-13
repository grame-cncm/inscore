
///<reference path="JSObjectView.ts"/>


abstract class JSAutoSize extends JSObjectView 
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

    getAutoSize() : Point {
        let elt = this.getElement();
        return { x: elt.clientWidth, y: elt.clientHeight };
    }

    waitForSize (objid: number) : boolean {
        if (!this.fSizeSynced) {
            let size = this.getAutoSize();
            if (!size.x || !size.y)  setTimeout (() => this.waitForSize (objid), 50) ;
            else {
                this.updateObjectSize (objid, size.x, size.y);
                this.fSizeSynced = true;
                JSObjectView.updateObjectView (this.getId(), objid, true);
            }    
        }
        return this.fSizeSynced;
	}
}