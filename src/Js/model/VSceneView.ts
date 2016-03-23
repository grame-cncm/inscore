///<reference path="VObjectView.ts"/>

class VSceneView extends VObjectView {
        
    constructor(motherScene: HTMLDivElement, object: IObject) {
        var scene: HTMLDivElement = document.createElement('div'); 
        
        scene.style.border = '1px black solid';
        scene.style.boxShadow = '2px 2px 4px black';
        scene.style.borderRadius = '8px';
        scene.style.width = '300px';
        scene.style.height = "500px";
        
        super(motherScene, object, scene); 
    }   
}


        
         
        
        