class JSAudioioView extends JSObjectView implements AudioObject {
    fAudioNode : AudioNode;

    constructor(parent: JSObjectView) {
		super(document.createElement('div'), parent); 
    }

    getNumInputs() : number {
        return this.fAudioNode.numberOfInputs;
    } 
    getNumOutputs() : number {
        return this.fAudioNode.numberOfOutputs;
    }
    getAudioNode() : AudioNode {
        return this.fAudioNode;
    }
    connect(to: AudioObject) : boolean {
        this.fAudioNode.connect(to.fAudioNode);
        return true;
    }
    disconnect(obj: AudioObject) : boolean {
        this.fAudioNode.disconnect(obj.fAudioNode);
        return true;
    }

    clone (parent: JSObjectView) : JSObjectView {
        return new JSAudioioView(parent);
    }
}