///<reference path="IText.ts"/>

class IHtml extends IText {

    //protected kHtmlType: string;
        
    constructor(name: string, parent: IObject) {
        super(name, parent);
        //this.kHtmlType = 'html';
        this.fTypeString = kHtmlType;
    }
}