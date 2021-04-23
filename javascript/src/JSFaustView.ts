
///<reference path="JSSVGBase.ts"/>
///<reference path="faust.ts"/>
///<reference path="AIOScanner.ts"/>
///<reference path="AudioTools.ts"/>
///<reference path="AudioObject.ts"/>

interface FaustSVG extends SVGSVGElement {
    diagram: Faust.SVGDiagrams;
}

class JSFaustView extends JSSvgBase implements AudioObject {
    private fFaust : faust;
    private fAudioNode : Faust.FaustMonoNode | Faust.FaustPolyNode = null;
    private fVoices = 0;
    static fCompilerLock = false;
    static readonly kFailed  = 0;
    static readonly kSuccess = 1;
    static readonly kPending = 2;
    
    constructor(parent: JSObjectView, compiler: faust) {
        super(parent);
        this.fFaust = compiler;
        this.getElement().className = "inscore-svg";
    }

    toAudioObject() : AudioObject { return this; }
    getNumInputs() : number     { return this.fAudioNode ? this.fAudioNode.getNumInputs() : 0; }
    getNumOutputs() : number    { return this.fAudioNode ? this.fAudioNode.getNumOutputs() : 0; }
    getAudioNode() : AudioNode  { return this.fAudioNode; }

    clone (parent: JSObjectView) : JSObjectView { return new JSFaustView(parent, this.fFaust); }
    toString() : string		                    { return "JSFaustView"; }
    osc2svgname (name: string) : string         { return name.replace (/\//g, "_"); }

    getSVGTarget() : SVGShape   { return this.fSVG; }
	updateSVGDimensions(w: number, h: number) : void { }
	updatePenControl(pen: OPen) : void {	this.updateRegularPen (pen); }

    delete() : void { 
        if (this.fAudioNode) {
            this.fAudioNode.disconnect();
            this.fAudioNode = null;
        }
        super.delete();
	}

    error(address: string, msg : string)	: void {
        let imsg = inscore.newMessageM ('set');
        inscore.msgAddStr (imsg, 'txt');
        inscore.msgAddStr (imsg, msg);
        inscore.postMessage (address, imsg);
    }

    // Creates the javascript callback to handle user navigation with the generated svg diagram
    makeLinkHandler (name: string, svg: Faust.SVGDiagrams) {
        let FSVG = this.fSVG as FaustSVG;
        this.fSVG.id = name;
        FSVG.diagram = svg;
        let code = name + "svg =  function (path) { \
            let elt= document.getElementById ('" + name + "'); \
            elt.innerHTML = elt.diagram.getSVG(path); \
            let p = elt.parentElement; \
            let bb = elt.getBBox(); \
            p.style.width = elt.style.width = bb.width; \
            p.style.height = elt.style.height = bb.height; \
        }";
        eval (code);
    }

    dsp2Svg (code: string, name: string) : { svg: string, error: string|null} { 
        let svg = Faust.createSVGDiagrams (this.fFaust.lib(), name, code, "");
        if (svg.success()) {
            this.makeLinkHandler (name, svg);
            return { svg: svg.getSVG(), error: null };
        }
        return {svg: "", error: "While generating Faust svg diagram :" + svg.error()};
    }

    updateSpecific(obj: INScoreObject)	: void {
        if (this.fAudioNode) {
            AudioTools.updateConnections(obj, this);
            let data = obj.getFaustInfos(true, false);
            // if (data.playing)
            //     this.fAudioNode.connect (AIOScanner.fAudioContext.destination);
            // else
            //     this.fAudioNode.disconnect();
            
            let val = data.values;
            let n = val.size();
            for (let i=0; i < n; i++) {
                let v = val.get(i);
// console.log ("JSFaustView.updateSpecific setParamValue " + v.address + " " +v.value);
                this.fAudioNode.setParamValue (v.address, v.value);
                if ((v.type == 0) && v.value)   // schedule the button off value
                    setTimeout (() => { this.fAudioNode.setParamValue (v.address, 0); }, 100);
            }
            if (this.fVoices && data.playing) {
                let node = this.fAudioNode as Faust.FaustPolyNode;
                let keys = data.keys;
                n = keys.size();
                for (let i=0; i < n; i++) {
                    let v = keys.get(i);
                    if (v.type == 0)
                        node.keyOn (v.chan, v.pitch, v.vel);
                    else if (v.type == 1)
                        node.keyOff (v.chan, v.pitch, v.vel);
                    else if (v.type == -1)
                        node.allNotesOff (true);
                }
            }
        }
		// else console.log ("Faust audio node is not available");
    }

    makeNode (obj: INScoreObject, code: string, voices: number) : number {
        // prevent building several objects in parallel
        if (JSFaustView.fCompilerLock) {
            setTimeout ( () => { this.makeNode (obj, code, voices)}, 50);
            return JSFaustView.kPending;
        }
        JSFaustView.fCompilerLock = true;
        Faust.compileAudioNode(AIOScanner.fAudioContext, this.fFaust.module(), code, null, voices, 0).then ( node => {
            JSFaustView.fCompilerLock = false;
            if (this.fAudioNode) this.fAudioNode.disconnect(); 
            this.fAudioNode = node;
            this.fVoices = voices;
            // let obj = INScore.objects().create(oid);
            if (!node) {
                let address = obj.getOSCAddress();
                this.error (address, "Cannot compile " + address + ".");
                return JSFaustView.kFailed;
            }

            obj.setAudioInOut (node.getNumInputs(), node.getNumOutputs());
            let ui = node.getDescriptors();
             ui.forEach ( (elt) => { 
//  console.log ("JSFaustView.makeNode elt " + elt.type + " " + elt.label + " " + elt.address + " " + elt.init + " " + elt.min + " " + elt.max + " " + elt.step );
                if ((elt.type == "button") || (elt.type == "checkbox"))
                    obj.setFaustUI (elt.type, elt.label, elt.address, 0, 0, 1, 1)
                else
                    obj.setFaustUI (elt.type, elt.label, elt.address, elt.init, elt.min, elt.max, elt.step) 
             });
            this.updateSpecific (obj);
            let bb = this.fSVG.getBBox();
            this.updateObjectSize (obj, bb.width + bb.x, bb.height + bb.y);
            obj.ready();
            // INScore.objects().del (obj);
            return JSFaustView.kSuccess;
        });
        return JSFaustView.kSuccess;
    }
    
    getCode(code: string) : Promise <string | null>	{ 
        return new Promise( function (resolve) {
            resolve (code);
        })
    }

    updateSpecial(obj: INScoreObject)	: boolean {
        if (!this.fFaust) {
            console.log ("Faust engine is not available");
            return false;
        }
        AIOScanner.scan (obj.getOSCAddress());
        let data = obj.getFaustInfos (false, true);
        this.getCode (data.code).then ( (code) => {
			if (code) {
                let diagram = this.dsp2Svg(code, this.osc2svgname(obj.getOSCAddress()));
                if (diagram.error)
                    this.error (obj.getOSCAddress(), diagram.error);
                else {
                    // success: display the svg diagram and build the audio node
                    this.fSVG.innerHTML = diagram.svg;
                    this.makeNode (obj, code, data.voices);
                }
                let ret = super.updateSpecial (obj /*, oid*/);
                return ret;
            }
            else return false;
        });
        return false;
    }
}
