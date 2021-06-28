
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
        if (JSFaustView.fCompilerLock) {
            setTimeout ( () => { this.buildNodeFromWasm (obj, wasm, json, voices)}, 50);
            return JSFaustView.kPending;
        }
        JSFaustView.fCompilerLock = true;
        const name = "inscore";
        this.fFactory = await Faust.createGenerator().loadDSPFactory(wasm, json);
        if (!this.fFactory) return JSFaustView.kFailed;
        let result = await this.makeAudioNode (obj, name, voices);
        JSFaustView.fCompilerLock = false;
        return result;
    }
  
    updateSpecial(obj: INScoreObject)	: boolean {
        if (!this.fFaust) {
            console.log ("Faust engine is not available");
            return false;
        }
        AIOScanner.scan (obj.getOSCAddress());
        let data = obj.getFaustInfos (false, true);
        this.buildNodeFromWasm (obj, data.code, data.json, data.voices);
        obj.ready();
        return true;
    }
}
