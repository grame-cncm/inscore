///<reference path="VObjectView.ts"/>

class VRectView extends VObjectView {
    
    constructor(motherScene: HTMLDivElement, object: IObject) {
        var scene = SvgFactory.createRect(); 
       
        super(motherScene, object, scene);      
    }    
}