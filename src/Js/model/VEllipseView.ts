///<reference path="VObjectView.ts"/>
///<reference path="SvgFactory.ts"/>

class VEllipseView extends VObjectView {
    
    constructor(object: IObject, motherScene: HTMLDivElement) {
        var scene = SvgFactory.createEllipse(); 

        super(object, scene, motherScene);  
    }    
}