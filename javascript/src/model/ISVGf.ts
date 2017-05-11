///<reference path="IImage.ts"/>

class ISVGf extends IImage {
    
    protected fFile: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kSvgfType;
    }
}