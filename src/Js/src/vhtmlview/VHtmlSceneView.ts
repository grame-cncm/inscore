
///<reference path="VHtmlView.ts"/>

class VHtmlSceneView extends VHtmlView {
        
    constructor() {
    	super (document.createElement('div'));
    	let div = this.getDiv();
        div.style.border = '1px black solid';
        div.style.boxShadow = '2px 2px 4px black';
        div.style.borderRadius = '8px';
        div.style.width = '300px';
        div.style.height = "500px";
    }   
}


        
         
        
        