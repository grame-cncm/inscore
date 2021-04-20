
///<reference path="JSObjectView.ts"/>

abstract class JSAutoSize extends JSObjectView 
{
    constructor(elt: HTMLElement, parent: JSObjectView) 	{ 
        super (elt, parent);
    }

    getAutoSize() : Point {
        let elt = this.getElement();
        return { x: elt.clientWidth, y: elt.clientHeight };
    }

    updateSizeSync (obj: INScoreObject) : boolean {
        let p = this.getAutoSize();
        this.updateObjectSize (obj, p.x, p.y);
        obj.ready();
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