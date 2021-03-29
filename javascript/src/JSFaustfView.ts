///<reference path="JSFaustView.ts"/>
///<reference path="TASyncUpdate.ts"/>
///<reference path="TFileLoader.ts"/>


class JSFaustfView extends JSFaustView {

    toString() : string	{ return "JSFaustfView"; }

    // getData(obj: INScoreObject) : OFaustInfos {
    //     let newObj = obj.getFaustInfos(false, true);
    //     //open
    //     newObj.code = obj.getFile();
    //     return newObj;
    // }
 
    getCode(code: string) : Promise <string | null>	{ 
		return TFileLoader.load (this.getElement(), code);
    }

}
