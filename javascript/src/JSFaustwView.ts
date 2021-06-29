
///<reference path="JSFaustView.ts"/>

interface FaustSVG extends SVGSVGElement {
    diagram: Faust.SVGDiagrams;
}

class JSFaustwView extends JSFaustView {
    
    constructor(parent: JSObjectView, compiler: faust) {
        super(parent, compiler);
    }

    clone (parent: JSObjectView) : JSObjectView { return new JSFaustwView(parent, this.fFaust); }
    toString() : string		                    { return "JSFaustwView"; }
  
    async buildNodeFromWasm (obj: INScoreObject, wasm: string, json: string, voices: number) : Promise<number> {
        this.fFactory = await Faust.createGenerator().loadDSPFactory(wasm, json);
        if (!this.fFactory) return JSFaustView.kFailed;
        let result = await this.makeAudioNode (obj, "inscore", voices);
        return result;
    }
  
    updateSpecial(obj: INScoreObject)	: boolean {
        AIOScanner.scan (obj.getOSCAddress());
        let data = obj.getFaustInfos (false, true);
        this.buildNodeFromWasm (obj, data.code, data.json, data.voices);
        return true;
    }
}
