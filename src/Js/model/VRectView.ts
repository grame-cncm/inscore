///<reference path="VObjectView.ts"/>

class VRectView extends VObjectView {
    
    constructor(object: IObject, motherScene: HTMLDivElement) {
        var scene = SvgFactory.createRect(); 
       
        super(object, scene, motherScene);      
    }    
}