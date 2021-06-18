///<reference types="@types/webmidi"/>
///<reference path="lib/libINScore.d.ts"/>


class MidiSetup {
    static midiClients : Array<INScoreObject> = [];
    static accessSetup : WebMidi.MIDIAccess;
    
  
    static midiTest(status: number, data1: number, data2: number) {
        MidiSetup.midiClients.forEach((client) => {
            client.midiEvent (status, data1, data2);
        });
    }

    static midiInput(event: WebMidi.MIDIMessageEvent) {
        MidiSetup.midiClients.forEach((client) => {
            client.midiEvent (event.data[0], event.data[1], event.data[2]);
        });
        // var cmd = event.data[0] >> 4;
        // var channel = event.data[0] & 0xf;
        // var pitch = event.data[1];
        // var press = event.data[2];
        // MidiSetup.midiClients.forEach((addr) => {

        //     let msg = inscore.newMessageM("event");
        //     inscore.msgAddStr(msg, "midi");
        //     inscore.msgAddStr(msg, "keyDown");
        //     inscore.msgAddI(msg, pitch);
        //     inscore.postMessage(addr, msg);

        //     console.log(pitch, press, channel, cmd);
        //     console.log("msg", msg);
        //     console.log(addr, "event midi", pitch, cmd);
        // });
    }

    static onErrorCallback() {
        console.log("connection error");
    }

    static onConnectionCallback(access : WebMidi.MIDIAccess) {
        MidiSetup.accessSetup = access;
        console.log("in callback");
        access.onstatechange = function(e: WebMidi.MIDIConnectionEvent) {
            if (e.port.type === "input") {
                let port = e.port as WebMidi.MIDIInput;
                if (e.port.state === "connected") {
                    console.log(e.port.name + " is connected");
                    port.onmidimessage = MidiSetup.midiInput;
                } else if (e.port.state  === "disconnected") {
                    console.log(e.port.name + " is disconnected");
                    port.onmidimessage = null;
                }
            }
        }
        access.inputs.forEach((input: WebMidi.MIDIInput) => {
            input.onmidimessage = MidiSetup.midiInput;
            console.log(input.name + " is connected");
        }) 
    }

    static addListener(obj : INScoreObject) {
        MidiSetup.midiClients.push(obj);
        if (typeof(navigator.requestMIDIAccess) !== "undefined" && MidiSetup.accessSetup !== null) {
            navigator.requestMIDIAccess({"sysex": true}).then(
                (access : WebMidi.MIDIAccess) => {
                    MidiSetup.onConnectionCallback(access);
                }, this.onErrorCallback
            );
        } else {
            alert("MIDI input cannot be activated, either your browser still does't have it, or you need to explicitly activate it.");
        }
    }
    
    static removeListener(addr : string) {

    }
}
// find a way to store what to filter
// exemple watch midi 30: post le message seulement si la touche 30 a été pressée

// inscore.postMessageStr ?
// 
// MIDIConnectionEvent -> created after succes requestMIDIAccess
// MIDIPort -> can close the connection

