///<reference path="JSImageView.ts"/>

class JSSVGfView extends JSImageView 
{
    constructor(parent: JSObjectView) {
        super(parent); 
        this.getElement().className = "inscore-svg";
    }    
}