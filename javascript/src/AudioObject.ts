interface AudioObject {
    fAudioNode : AudioNode;

    getNumInputs() : number
    getNumOutputs() : number
    getAudioNode() : AudioNode

    connect(to: AudioObject) : boolean

    disconnect(obj: AudioObject) : boolean
}