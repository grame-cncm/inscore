///<reference types="@types/webmidi"/>
///<reference path="lib/libINScore.d.ts"/>


class MidiSetup {
    static midiClients : Array<INScoreObject> = [];
    static accessSetup : WebMidi.MIDIAccess;
    static verboseMode : boolean;
    
  
    static midiTest(status: number, data1: number, data2: number) {
        MidiSetup.midiClients.forEach((client) => {
            client.midiEvent (status, data1, data2);
        });
    }

    static midiInput(event: WebMidi.MIDIMessageEvent) {
        MidiSetup.midiClients.forEach((client) => {
            // filter msg from 240 to 255 (system msg)
            if (MidiSetup.verboseMode) {
                console.log(event.data[0], event.data[1], event.data[2]);
            } if (event.data[2] === undefined) {
                client.midiEvent (event.data[0], event.data[1], 0);
            } else 
                client.midiEvent (event.data[0], event.data[1], event.data[2]);
        });
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

    static toggleVerboseMode() {
        if (MidiSetup.verboseMode)
            MidiSetup.verboseMode = false;
        else 
            MidiSetup.verboseMode = true;
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
            console.log("MIDI input cannot be activated...");
        }
    }
    
    static removeListener(client : INScoreObject) {
        const index = MidiSetup.midiClients.indexOf(client);
        if (index > -1) {
            MidiSetup.midiClients.splice(index, 1);
        }
    }
}