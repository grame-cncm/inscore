class AIOScanner {
    private fInput: AudioNode;
    private fOutput: AudioNode;
    private context: AudioContext;

    constructor (context: AudioContext) {
        this.context = context;
        this.scan();
    } // have the audio context upon creation

    scan () {
        this.fOutput = this.context.destination;
        navigator.mediaDevices.getUserMedia({audio: true, video: false})
        .then((stream: MediaStream) => {
            this.fInput = this.context.createMediaStreamSource(stream);
            this.fInput.connect(this.fOutput);
        })
        .catch(function(err) {
            console.log("the following error occured: " + err);
        });
    } // Get All Physical in/out and populate finput & foutput

    send (scene: string, audioInput: string) {
        let msg = inscore.newMessageM ("set");
        inscore.msgAddStr (msg, "audio");
        inscore.msgAddI (msg, 1); // nb inpuit
        inscore.msgAddI (msg, 0); // nb output
        inscore.postMessage ("/ITL/" + scene + "/" + audioInput + "", msg);
    } // can send a set audioio message for each physical input/output
    create(inNode: AudioNode, outNode: AudioNode) : AudioObject { // Create AudioObject
        var aObject = new AudioObject;
        return aObject;
    }

}