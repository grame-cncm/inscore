class AIOScanner {
    static fInput: AudioNode = null;
    static fOutput: AudioNode = null;
    static readonly kInputName : string = "audioInput";
    static readonly kOutputName : string = "audioOutput";
    static fAudioContext : AudioContext = null;
    static fUnlockEvents = ["touchstart", "touchend", "mousedown", "keydown"];

    static init()
    {
        if (!AIOScanner.fAudioContext) {
            AIOScanner.fAudioContext = new (window.AudioContext || window.webkitAudioContext)();
            AIOScanner.unlockAudioContext(AIOScanner.fAudioContext);
        }
    }

    static scan (address: string) {
        AIOScanner.fOutput = AIOScanner.fAudioContext.destination;
        AIOScanner.send (address, AIOScanner.kOutputName, AIOScanner.fOutput);
        navigator.mediaDevices.getUserMedia({audio: true, video: false})
        .then((stream: MediaStream) => {
            AIOScanner.fInput = AIOScanner.fAudioContext.createMediaStreamSource(stream);
            AIOScanner.send (address, AIOScanner.kInputName, AIOScanner.fInput);
            // AIOScanner.fInput.connect(this.fOutput);
        })
        .catch(function(err) {
            AIOScanner.send (address, AIOScanner.kInputName, null);
            console.log("AIOScanner can't get input device: " + err);
        });
    } // Get All Physical in/out and populate finput & foutput

    private static send (address: string, name: string, node: AudioNode) {
        let msg = inscore.newMessageM ("set");
        let prefix = address.substring (0, address.lastIndexOf("/"));
        inscore.msgAddStr (msg, "audioio");
        inscore.msgAddI (msg, node ? (node.numberOfInputs  ? node.channelCount : 0) : 0);     // nb input
        inscore.msgAddI (msg, node ? (node.numberOfOutputs ? node.channelCount : 0) : 0);    // nb output
        // inscore.msgAddI (msg, node ? node.numberOfInputs : 0);     // nb input
        // inscore.msgAddI (msg, node ? node.numberOfOutputs : 0);    // nb output
        inscore.postMessage (prefix + "/" + name + "", msg);
    } // can send a set audioio message for each physical input/output

    // create(inNode: AudioNode, outNode: AudioNode) : AudioObject { // Create AudioObject
    //     var aObject = new AudioObject;
    //     return aObject;
    // }

    static unlockclean ()  { AIOScanner.fUnlockEvents.forEach(e => document.body.removeEventListener(e, this.unlock)); } 
    static unlock ()       { AIOScanner.fAudioContext.resume().then(AIOScanner.unlockclean) } 
    static unlockAudioContext(audioCtx: AudioContext) {
        if (audioCtx.state !== "suspended") return;
        AIOScanner.fUnlockEvents.forEach(e => document.body.addEventListener(e, AIOScanner.unlock, false));
    }

}

document.addEventListener("DOMContentLoaded", (event) => {
    AIOScanner.init();
    console.log('DOM is ready.')
});
