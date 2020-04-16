
///<reference path="JSSVGView.ts"/>
///<reference path="TFileLoader.ts"/>

// class JSSVGfView extends JSImageView 
class JSSVGfView extends JSSVGView 
{
    fContent = "";

    constructor(parent: JSObjectView) {
        super(parent); 
    }


    // constructor(parent: JSObjectView) {
    //     super(parent); 
    //     this.getElement().className = "inscore-svg";
    // }

    toString() : string			{ return "JSSVGfView"; }

	getSvg (obj: INScoreObject) : string { 
        let content = this.fContent; 
        this.fContent = "";
        return content;
    }

    updateSpecial ( obj: INScoreObject, oid: number)	: boolean {		
        if (this.fContent) return super.updateSpecial (obj, oid);
        let file = obj.getFile();
        let address = obj.getOSCAddress();
        TFileLoader.load (this.getElement(), file).then ((text: string) => { 
            this.fContent = text;
            gGlue.inscore().postMessageStr (address, "refresh");
        });
        return false;
    }

	// updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
    //     this.fImage.src  = obj.getFile();
    //     return super.updateSpecial (obj, objid );
    // }
        
}