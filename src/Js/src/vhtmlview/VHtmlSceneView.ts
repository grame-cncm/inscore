
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IObject.ts"/>

class VHtmlSceneView extends VHtmlView {
        
    constructor() {
    	super (document.createElement('div'));
    	let div = this.getDiv();
        div.className = "scene";
        document.getElementsByTagName('body')[0].appendChild (div);
    }

	updateView	( obj: IObject) : void {
		let pos = obj.getPosition();
        let wsize = TWindow.getSize();
        let w = Math.min(wsize.w, wsize.h);
    	let div = this.getDiv();
        div.style.width  = w.toString()+"px";
        div.style.height = div.style.width;
        div.style.left =  ((wsize.w - w) /2).toString() + "px"  ;
        div.style.top =   ((wsize.h - w) /2).toString() + "px"  ;
	}
}

        