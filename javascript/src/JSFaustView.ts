
///<reference path="JSSVGBase.ts"/>
///<reference path="faust.ts"/>

interface FaustSVG extends SVGSVGElement {
    diagram: Faust.SVGDiagrams;
}

class JSFaustView extends JSSvgBase {
    private fFaust : faust;
    private fAudioContext : AudioContext;
    private fAudioNode : Faust.FaustMonoNode | Faust.FaustPolyNode;
    private fVoices = 0;
    
    constructor(parent: JSObjectView, compiler: faust) {
        super(parent);
        this.fFaust = compiler;
        this.getElement().className = "inscore-svg";
    }

    clone (parent: JSObjectView) : JSObjectView { return new JSFaustView(parent, this.fFaust); }
    toString() : string		                    { return "JSFaustView"; }
    osc2svgname (name: string) : string         { return name.replace (/\//g, "_"); }

    getSVGTarget() : SVGShape   { return this.fSVG; }
	updateSVGDimensions(w: number, h: number) : void { }
	updatePenControl(pen: OPen) : void {	this.updateRegularPen (pen); }

    // Creates the javascript callback to handle user navigation with the generated svg diagram
    makeLinkHandler (name: string, svg: Faust.SVGDiagrams) {
        let FSVG = this.fSVG as FaustSVG;
        this.fSVG.id = name;
        FSVG.diagram = svg;
        let code = name + "svg =  function (path) { let elt= document.getElementById ('" + name + "'); elt.innerHTML = elt.diagram.getSVG(path); }";
        eval (code);
    }

    display (msg: string) { 
        let svg = "<svg> <text>" + msg + "</text></svg>"
        this.getElement().innerHTML = svg;
    }

    dsp2Svg (code: string, name: string) : string { 
        let svg = Faust.createSVGDiagrams (this.fFaust.lib(), name, code, "");
        if (!svg.success()) console.log(svg.error());
        else {
            this.makeLinkHandler (name, svg);
            return svg.getSVG();
        }
        return "";
    }

    unlockAudioContext(audioCtx: AudioContext) {
        if (audioCtx.state !== "suspended") return;
        const b = document.body;
        const events = ["touchstart", "touchend", "mousedown", "keydown"];
        const unlock : any = () => audioCtx.resume().then(clean);
        const clean = () => events.forEach(e => b.removeEventListener(e, unlock));
        events.forEach(e => b.addEventListener(e, unlock, false));
    }

    updateSpecific(obj: INScoreObject)	: void {
        if (this.fAudioNode) {
            let data = obj.getFaustInfos(true, false);
            if (data.playing)
                this.fAudioNode.connect (this.fAudioContext.destination);
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

    makeNode (oid: number, code: string, voices: number) {
        try {
        Faust.compileAudioNode(this.fAudioContext, this.fFaust.module(), code, null, voices).then ( node => {
            this.fAudioNode = node;
            this.fVoices = voices;
            let obj = INScore.objects().create(oid);
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
        }
        catch (error) {
            console.log ("Faust compilation error: " + error);
        }
    }
    
    updateSpecial(obj: INScoreObject, oid: number)	: boolean {
        if (!this.fFaust) {
            console.log ("Faust engine is not available");
            return false;
        }
        let data = obj.getFaustInfos (false, true);
		this.fSVG.innerHTML = this.dsp2Svg(data.code, this.osc2svgname(obj.getOSCAddress()));
		let bb = this.fSVG.getBBox();
        this.updateObjectSizeSync (obj, bb.width + bb.x, bb.height + bb.y);
        
        this.fAudioContext = new (window.AudioContext || window.webkitAudioContext)();
        this.makeNode (oid, data.code, data.voices);
        this.unlockAudioContext(this.fAudioContext);
        return super.updateSpecial (obj, oid);
    }
}
