///<reference path="VObjectView.ts"/>
///<reference path="../model/SvgFactory.ts"/>

class VCurveView extends VObjectView {
    
    constructor(object: IObject, motherScene: HTMLDivElement) {
        var scene = SvgFactory.createSvg('curve'); 

        super(object, scene, motherScene);  
    }    
}