
///<reference path="JSObjectView.ts"/>

abstract class JSAutoSize extends JSObjectView 
{
    private fSetSize = true;    // a flag to control automatic size setting

    constructor(elt: HTMLElement, parent: JSObjectView) 	{ 
        super (elt, parent);
    }

    sizePending() : void  { this.fSetSize = true; }

    getAutoSize() : Point {
        let elt = this.getElement();
        return { x: elt.clientWidth, y: elt.clientHeight };
    }

    updateSizeSync (obj: INScoreObject) : boolean {
        if (!this.fSetSize) return true;
        let p = this.getAutoSize();
        this.updateObjectSize (obj, p.x, p.y);
        obj.ready();
        this.fSetSize = false;
        return true;
    }

    updateSizeASync (obj: INScoreObject) : boolean {
        let size = this.getAutoSize();
        if (!size.x || !size.y)  setTimeout (() => this.updateSizeASync (obj), 20) ;
        else {
            return this.updateSizeSync (obj);
        }
        return false;
	}
}