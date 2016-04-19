///<reference path="IRectShape.ts"/>

class IScene extends IRectShape {
    
    protected kSceneType: string;
    protected fDivElement: HTMLDivElement;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kSceneType = 'scene';
        this.fTypeString = this.kSceneType;
        this.fDivElement = document.createElement('div');
    }
}