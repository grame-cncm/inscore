

class JSAutoSize extends JSObjectView 
{

    constructor(elt, parent) 	{ 
        super (elt, parent); 
        elt.style.height = "auto";
        elt.style.width  = "auto";
        this.fSizeSynced = false;
    }

	updateObjectSize (objid) {
        if (!this.fSizeSynced) {
            let elt = this.getElement();
            let w = elt.clientWidth;
            let h = elt.clientHeight;
            if (!w || !h)  setTimeout (() => this.updateObjectSize (objid), 50) ;
        }
        else {
            super.updateObjectSize (objid);
            this.fSizeSynced = true;
            JSObjectView.updateObjectView (this.getId(), objid);
        }
	}
}