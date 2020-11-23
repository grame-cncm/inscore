
///<reference path="JSSVGBase.ts"/>
///<reference path="faust.ts"/>

interface FaustSVG extends SVGSVGElement {
    diagram: Faust.SVGDiagrams;
}

class JSFaustView extends JSSvgBase {
    private fFaust : faust;
    static fAudioContext : AudioContext = null;
    private fAudioNode : Faust.FaustMonoNode | Faust.FaustPolyNode = null;
    private fVoices = 0;
    static fUnlockEvents = ["touchstart", "touchend", "mousedown", "keydown"];
    
    constructor(parent: JSObjectView, compiler: faust) {
        super(parent);
        this.fFaust = compiler;
        if (!JSFaustView.fAudioContext) {
            JSFaustView.fAudioContext = new (window.AudioContext || window.webkitAudioContext)();
            this.unlockAudioContext(JSFaustView.fAudioContext);
        }
        this.getElement().className = "inscore-svg";
    }

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
            console.log('link handler called : ' + elt + ' ' + bb.x + ' ' + bb.y); \
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
        return {svg: "", error: svg.error() + " (svg diagram generation)"};
    }

    unlockclean ()  { JSFaustView.fUnlockEvents.forEach(e => document.body.removeEventListener(e, this.unlock)); } 
    unlock ()       { JSFaustView.fAudioContext.resume().then(this.unlockclean) } 
    unlockAudioContext(audioCtx: AudioContext) {
        if (audioCtx.state !== "suspended") return;
        JSFaustView.fUnlockEvents.forEach(e => document.body.addEventListener(e, this.unlock, false));
    }

    updateSpecific(obj: INScoreObject)	: void {
        if (this.fAudioNode) {
            let data = obj.getFaustInfos(true, false);
            if (data.playing)
                this.fAudioNode.connect (JSFaustView.fAudioContext.destination);
            else
                this.fAudioNode.disconnect();
            
            let val = data.values;
            let n = val.size();
            for (let i=0; i < n; i++) {
                let v = val.get(i);
                this.fAudioNode.setParamValue (v.address, v.value);
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
                }
            }
        }
		// else console.log ("Faust audio node is not available");
    }

    makeNode (oid: number, code: string, voices: number) : boolean {
        if (this.fAudioNode) this.fAudioNode.disconnect(); 
        Faust.compileAudioNode(JSFaustView.fAudioContext, this.fFaust.module(), code, null, voices).then ( node => {
            this.fAudioNode = node;
            this.fVoices = voices;
            let obj = INScore.objects().create(oid);
            if (!node) {``
                let address = obj.getOSCAddress();
                this.error (address, "Cannot compile " + address + ".");
                return false;
            }

            obj.setFaustInOut (node.getNumInputs(), node.getNumOutputs());
            let ui = node.getDescriptors();
            ui.forEach ( (elt) => { 
                if (elt.type == "button")
                    obj.setFaustUI (elt.type, elt.label, elt.address, 0, 0, 1, 1)
                else
                    obj.setFaustUI (elt.type, elt.label, elt.address, elt.init, elt.min, elt.max, elt.step) 
            });
            this.updateSpecific(obj);
            INScore.objects().del (obj);
        });
        return false;
    }
    
    updateSpecial(obj: INScoreObject, oid: number)	: boolean {
        if (!this.fFaust) {
            console.log ("Faust engine is not available");
            return false;
        }
        let data = obj.getFaustInfos (false, true);
        let diagram = this.dsp2Svg(data.code, this.osc2svgname(obj.getOSCAddress()));
        if (diagram.error)
            this.error (obj.getOSCAddress(), diagram.error);
        else {
            this.fSVG.innerHTML = diagram.svg;
            this.makeNode (oid, data.code, data.voices);
            let bb = this.fSVG.getBBox();
            this.updateObjectSizeSync (obj, bb.width + bb.x, bb.height + bb.y);
        }
        return super.updateSpecial (obj, oid);
    }
}
