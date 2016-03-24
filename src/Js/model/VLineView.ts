///<reference path="VObjectView.ts"/>
///<reference path="SvgFactory.ts"/>

class VLineView extends VObjectView {
    
    constructor(object: IObject, motherScene: HTMLDivElement) {
        var scene = SvgFactory.createSvg('line'); 

        super(object, scene, motherScene);  
    }    
}