class AIOScanner {
    private fInput: AudioNode;
    private fOutput: AudioNode;
    private context: AudioContext;

    constructor (context: AudioContext) {
        this.context = context;
    } // have the audio context upon creation

    scan () {
        this.fOutput = this.context.destination;
        navigator.mediaDevices.getUserMedia({audio: true, video: false}).then(function(mediaStream) {
            console.log("activated input");
        });
    } // Get All Physical in/out and populate finput & foutput

    send (address: string) { } // can send a set audioio message for each physical input/output
    create(inNode: AudioNode, outNode: AudioNode) : AudioObject { // Create AudioObject
        return new AudioObject;
    }

}