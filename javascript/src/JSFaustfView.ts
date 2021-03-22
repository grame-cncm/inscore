///<reference path="JSSVGBase.ts"/>
///<reference path="faust.ts"/>

class JSFaustfView extends JSFaustView {

    toString() : string	{ return "JSFaustfView"; }

    getData(obj: INScoreObject) : OFaustInfos {
        let newObj = obj.getFaustInfos(false, true);
        //open
        newObj.code = obj.getFile();
        return newObj;
    }
}