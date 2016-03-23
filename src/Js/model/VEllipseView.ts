///<reference path="VObjectView.ts"/>
///<reference path="SvgFactory.ts"/>

class VEllipseView extends VObjectView {
    
    constructor(motherScene: HTMLDivElement, object: IObject) {
        var scene = SvgFactory.createEllipse(); 

        super(motherScene, object, scene);  
    }    
}