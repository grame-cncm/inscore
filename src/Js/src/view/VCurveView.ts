///<reference path="VObjectView.ts"/>
///<reference path="../lib/SvgFactory.ts"/>

class VCurveView extends VObjectView {
    
    constructor(object: IObject, motherScene: HTMLDivElement) {
        var scene = SvgFactory.createSvg('curve'); 

        super(object, scene, motherScene);  
    }    
}