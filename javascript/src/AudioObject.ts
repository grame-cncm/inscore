
///<reference path="AIOScanner.ts"/>

interface AudioObject {
    getNumInputs() : number
    getNumOutputs() : number
    getNumChans() : number
    getAudioNode() : AudioNode
    getSplitter() : AudioNode
    getMerger() : AudioNode
}


class AudioRouting {
    protected fSplitter : AudioNode = null;
    protected fMerger : AudioNode = null;
    private fAudioNode : AudioNode = null;
    
    // depending on the channels and the number of inputs / outputs
    // encapsulates an audio node in a splitter and a merger 
    // the merger is connected to the node input and the splitter to the node output
    constructor(node: AudioNode, chans: number, caller: string) {
        this.fAudioNode = node;
		if (chans > 1) {
		    if (node.numberOfOutputs) {
                this.fSplitter  = AIOScanner.fAudioContext.createChannelSplitter (chans);
                node.connect (this.fSplitter);
            }
		    if (node.numberOfInputs) {
                this.fMerger	= AIOScanner.fAudioContext.createChannelMerger (chans);
                this.fMerger.connect (node);
            }
        }
// console.log (caller, "create AudioRouting with", chans, "channels", "i/o", node.numberOfInputs, node.numberOfOutputs )
    }

    getSplitter()   { return this.fSplitter ? this.fSplitter : this.fAudioNode; }
    getMerger()     { return this.fMerger ? this.fMerger : this.fAudioNode; }
}