

class JSAutoSize extends JSObjectView 
{

    constructor(elt, parent) 	{ 
        super (elt, parent); 
        elt.style.height = "auto";
        elt.style.width  = "auto";
        this.fSizeSynced = false;
    }

    updateSpecial (obj, objid)	{
        this.fSizeSynced = false;
        return this.waitForSize (objid);

    }

	waitForSize (objid) {
        if (!this.fSizeSynced) {
            let elt = this.getElement();
            let w = elt.clientWidth;
            let h = elt.clientHeight;
            if (!w || !h)  setTimeout (() => this.waitForSize (objid), 50) ;
            return false;
        }
        else {
            super.updateObjectSize (objid);
            this.fSizeSynced = true;
            JSObjectView.updateObjectView (this.getId(), objid);
            return true;
        }
	}
}