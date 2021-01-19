
///<reference path="JSObjectView.ts"/>
///<reference path="TASyncUpdate.ts"/>


abstract class JSAutoSize extends JSObjectView 
{
    constructor(elt: HTMLElement, parent: JSObjectView) 	{ 
        super (elt, parent); 
        // elt.style.height = "auto";
        // elt.style.width  = "auto";
    }

    getAutoSize() : Point {
        let elt = this.getElement();
        return { x: elt.clientWidth, y: elt.clientHeight };
    }

    updateSizeSync (obj: INScoreObject) {
        let p = this.getAutoSize();
        this.updateObjectSizeSync (obj, p.x, p.y);
        obj.ready();
        return true;
    }

    updateSizeASync (objid: number) : boolean {
        let size = this.getAutoSize();
        if (!size.x || !size.y)  setTimeout (() => this.updateSizeASync (objid), 20) ;
        else {
            return TASyncUpdate.update (objid, (obj) => this.updateSizeSync(obj) );
        }
        return false;
	}
}