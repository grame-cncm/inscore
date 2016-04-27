///<reference path="IRectShape.ts"/>

class IScene extends IRectShape {
    
    protected kSceneType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kSceneType = 'scene';
        this.fTypeString = this.kSceneType;
    }

    getScene(): IObject 			{ return this; }
}