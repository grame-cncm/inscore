
///<reference path="lib/inscore.d.ts"/>


class AIOScanner {
    static fOutput: AudioNode = null;
    static readonly kInputName : string = "audioInput";
    static readonly kOutputName : string = "audioOutput";
    static fAudioContext : AudioContext = null;
    static fUnlockEvents = ["touchstart", "touchend", "mousedown", "keydown"];

    static init()
    {
       if (!AIOScanner.fAudioContext) {
            AIOScanner.fAudioContext = new (window.webkitAudioContext || window.AudioContext)({ latencyHint: 0.00001 });
            AIOScanner.unlockAudioContext(AIOScanner.fAudioContext); 
            // document.onreadystatechange = function() {
            //     if (document.readyState === 'interactive') {
            //         AIOScanner.unlockAudioContext(AIOScanner.fAudioContext); 
            //     }
            // }
        }
    }

    static scan (address: string) {
        AIOScanner.init();
        AIOScanner.fOutput = AIOScanner.fAudioContext.destination;
        AIOScanner.create (address, AIOScanner.kOutputName, AIOScanner.fOutput);
        AIOScanner.create (address, AIOScanner.kInputName, null);
    }

    static send (address: string, inputs: number, outputs: number) {
        let msg = inscore.newMessageM ("set");
        inscore.msgAddStr (msg, "audioio");
        inscore.msgAddI (msg, inputs);
        inscore.msgAddI (msg, outputs); 
        inscore.postMessage (address, msg);
    }

    private static create (address: string, name: string, node: AudioNode) {
        let inputs = node ? (node.numberOfInputs  ? node.channelCount : 0) : 0;
        let outputs = node ? (node.numberOfOutputs ? node.channelCount : 0) : 0;
        let prefix = address.substring (0, address.lastIndexOf("/"));
        AIOScanner.send (prefix + "/" + name, inputs, outputs);
    }

    private static unlock ()       { 
        AIOScanner.fAudioContext.resume();
        console.log ("unlock", AIOScanner.fAudioContext);
        if (AIOScanner.fAudioContext.state === "running")
            AIOScanner.fUnlockEvents.forEach(e => document.body.removeEventListener(e, AIOScanner.unlock)); 
    } 
    private static unlockAudioContext(audioCtx: AudioContext) {
        console.log ("unlockAudioContext", audioCtx.state);
        if (audioCtx.state !== "suspended") return;
        AIOScanner.fUnlockEvents.forEach(e => document.body.addEventListener(e, AIOScanner.unlock, false));
    }
}

