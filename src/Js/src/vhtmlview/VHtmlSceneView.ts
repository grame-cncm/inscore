
///<reference path="VHtmlView.ts"/>

class VHtmlSceneView extends VHtmlView {
        
    constructor() {
    	super (document.createElement('div'));
    	let div = this.getDiv();
        div.style.border = '1px black solid';
        div.style.boxShadow = '2px 2px 4px black';
        div.style.borderRadius = '8px';
        let wsize = this.getWindowSize();
        div.style.width  = Math.min(wsize.w, wsize.h).toString();
        div.style.height = div.style.width;
    }   

	getWindowSize() : { w: number, h: number} {
		let w = 0, h = 0;
  		if( typeof( window.innerWidth ) == 'number' ) {
		    //Non-IE
			w = window.innerWidth;
			h = window.innerHeight;
		} 
		else if ( document.documentElement && ( document.documentElement.clientWidth || document.documentElement.clientHeight ) ) {
			//IE 6+ in 'standards compliant mode'
			w = document.documentElement.clientWidth;
			h = document.documentElement.clientHeight;
		} 
		else if( document.body && ( document.body.clientWidth || document.body.clientHeight ) ) {
			//IE 4 compatible
			w = document.body.clientWidth;
			h = document.body.clientHeight;
		}
		return { w: w, h: h };
	}
}


        
         
        
        