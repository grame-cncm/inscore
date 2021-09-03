
///<reference path="JSObjectView.ts"/>
///<reference path="AudioObject.ts"/>
///<reference path="AIOScanner.ts"/>
///<reference path="AudioTools.ts"/>

class JSAudioioView extends JSObjectView implements AudioObject {
    fAudioNode : AudioNode = null;
    protected fRouter : AudioRouting = null;

    constructor(parent: JSObjectView) {
		super(document.createElement('div'), parent); 
    }

	toString() { return "JSAudioioView"; }
	toAudioObject() : AudioObject { return this; }
    getNumInputs() : number     { return this.fAudioNode ? this.fAudioNode.numberOfInputs : 0; } 
    getNumOutputs() : number    { return this.fAudioNode ? this.fAudioNode.numberOfOutputs : 0; }
    getNumChans() : number      { return this.fAudioNode ? this.fAudioNode.channelCount : 0; }
    getAudioNode() : AudioNode  { return this.fAudioNode; }
    getSplitter() : AudioNode   { return this.fRouter.getSplitter(); }
    getMerger() : AudioNode     { return this.fRouter.getMerger(); }

    clone (parent: JSObjectView) : JSObjectView {
        return new JSAudioioView(parent);
    }

    updateSpecific(obj: INScoreObject)	: void {
        AudioTools.updateConnections(obj, this);
    }

    initView (obj: INScoreObject) : boolean {
        let infos = obj.getIOInfos();
        if (infos.inputs && infos.outputs) {
            console.log ("Warning: JSAudioioView created with " + infos.inputs + " inputs and " + infos.outputs + " outputs."  );
        }
        if (infos.inputs )
            this.fAudioNode = AIOScanner.fOutput;
        else if (infos.outputs)
            this.fAudioNode = AIOScanner.fInput;
        if (this.fAudioNode) this.fRouter  = new AudioRouting (this.fAudioNode, this.fAudioNode.channelCount, this.toString());
        return true;    
    }
    
    updateSpecial(obj: INScoreObject) : boolean {
        return true;
    }
}