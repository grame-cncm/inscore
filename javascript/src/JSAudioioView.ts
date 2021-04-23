
///<reference path="JSObjectView.ts"/>
///<reference path="AudioObject.ts"/>
///<reference path="AIOScanner.ts"/>
///<reference path="AudioTools.ts"/>

class JSAudioioView extends JSObjectView implements AudioObject {
    fAudioNode : AudioNode = null;

    constructor(parent: JSObjectView) {
		super(document.createElement('div'), parent); 
    }

	toAudioObject() : AudioObject { return this; }
    getNumInputs() : number     { return this.fAudioNode ? this.fAudioNode.channelCount : 0; } 
    getNumOutputs() : number    { return this.fAudioNode ? this.fAudioNode.channelCount : 0; }
    getAudioNode() : AudioNode  { return this.fAudioNode; }

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
        if (infos.inputs ) {
            this.fAudioNode = AIOScanner.fOutput;
            if (this.getNumInputs() != infos.inputs )
                console.log ("JSAudioioView Warning: device has not the requested number of inputs: " + this.getNumInputs() + " instead of "  + infos.inputs);
            }
        else if (infos.outputs) {
            this.fAudioNode = AIOScanner.fInput;
            if (this.getNumOutputs() != infos.outputs )
                console.log ("JSAudioioView Warning: device has not the requested number of outputs: " + this.getNumOutputs() + " instead of "  + infos.outputs);
        }
        return true;    
    }
    
    updateSpecial(obj: INScoreObject) : boolean {
        return true;
    }
}