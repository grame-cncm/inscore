///<reference path="VObjectView.ts"/>

class VRectView extends VObjectView {
    
    constructor(object: IObject, motherScene: HTMLDivElement) {
        var scene = SvgFactory.createSvg('rect'); 
       
        super(object, scene, motherScene);      
    }    
}