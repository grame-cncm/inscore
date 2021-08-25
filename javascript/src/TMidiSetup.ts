///<reference types="@types/webmidi"/>
///<reference path="lib/libINScore.d.ts"/>


class MidiSetup {
    static fClients : Array<INScoreObject> = [];
    static fMIDIAccess : WebMidi.MIDIAccess;
    static fVerbose : number;
    static fMidiStatus : Map<number, string>;

    // static midiTest(status: number, data1: number, data2: number) {
    //     MidiSetup.fClients.forEach((client) => {
    //         client.midiEvent (status, data1, data2);
    //     });
    // }

    static initmap()
    {
        MidiSetup.fMidiStatus = new Map();
        MidiSetup.fMidiStatus.set(0x80, 'Note Off');
        MidiSetup.fMidiStatus.set(0x90, 'Note On');
        MidiSetup.fMidiStatus.set(0xa0, 'Polyphonic AfterTouch');
        MidiSetup.fMidiStatus.set(0xb0, 'Control Change');
        MidiSetup.fMidiStatus.set(0xc0, 'Program Change');
        MidiSetup.fMidiStatus.set(0xd0, 'Channel Aftertouch');
        MidiSetup.fMidiStatus.set(0xe0, 'Pitch Bend');

        MidiSetup.fMidiStatus.set(0xf0, "SysRealTime");
        MidiSetup.fMidiStatus.set(0xf0, "SysEx");
        MidiSetup.fMidiStatus.set(0xf1, "QFrame");
        MidiSetup.fMidiStatus.set(0xf2, "SongPos");
        MidiSetup.fMidiStatus.set(0xf3, "SongSel");
        MidiSetup.fMidiStatus.set(0xf6, "Tune");
        MidiSetup.fMidiStatus.set(0xf7, "EndSysX");
        MidiSetup.fMidiStatus.set(0xf8, "Clock");
        MidiSetup.fMidiStatus.set(0xfa, "Start");
        MidiSetup.fMidiStatus.set(0xfb, "Continue");
        MidiSetup.fMidiStatus.set(0xfc, "Stop");
        MidiSetup.fMidiStatus.set(0xfe, "Active Sensing");
        MidiSetup.fMidiStatus.set(0xff, "Reset");
    }
 
    static print (event: WebMidi.MIDIMessageEvent)
    {
        let status = event.data[0];
        if ((MidiSetup.fVerbose === 1) && (status >= 0xf0)) return;
        if (status >= 0xf0)     // system events: displays only the status
            console.log (MidiSetup.fMidiStatus.get(status >> 4));
        else
            console.log("Chan ", status & 0xf, MidiSetup.fMidiStatus.get(status >> 4), event.data[1], event.data[2] ? event.data[2] : "");
    }

    static midiInput(event: WebMidi.MIDIMessageEvent) {
        if (MidiSetup.fVerbose) MidiSetup.print (event);
        MidiSetup.fClients.forEach((client) => {
            // filter msg from 240 to 255 (system msg)
            if (event.data[0] >= 240)
                return;
            if (event.data[2] === undefined) {
                client.midiEvent (event.data[0], event.data[1], 0);
            } else
                client.midiEvent (event.data[0], event.data[1], event.data[2]);
        });
    }

    static onErrorCallback() {
        console.log("Failed to initialise MIDI input...");
        MidiSetup.event ("error");
    }

    static onConnectionCallback(access : WebMidi.MIDIAccess) {
        MidiSetup.fMIDIAccess = access;
        access.onstatechange = function(e: WebMidi.MIDIConnectionEvent) {
            if (e.port.type === "input") {
                let port = e.port as WebMidi.MIDIInput;
                if (e.port.state === "connected") {
                    port.onmidimessage = MidiSetup.midiInput;
                } else if (e.port.state  === "disconnected") {
                    port.onmidimessage = null;
                }
            }
        }
        MidiSetup.event ("ready");
        access.inputs.forEach((input: WebMidi.MIDIInput) => {
            input.onmidimessage = MidiSetup.midiInput;
        }) 
    }

    static verbose (mode: number)           { MidiSetup.fVerbose = mode; }
    static event( type: string)             { inscore.postMessageStrStr ("/ITL/midi", "event", type); }

    static init() {
        MidiSetup.initmap();
        if (typeof(navigator.requestMIDIAccess) !== "undefined" && MidiSetup.fMIDIAccess !== null) {
            navigator.requestMIDIAccess({"sysex": true}).then( (access : WebMidi.MIDIAccess) => {
                    MidiSetup.onConnectionCallback (access);
                }, this.onErrorCallback
            );
        } else {
            console.log("Failed to initialise MIDI input...");
            MidiSetup.event ("error");
        }
    }

    static addListener(obj : INScoreObject) {
        MidiSetup.fClients.push(obj);
    }
    
    static removeListener(client : INScoreObject) {
        const index = MidiSetup.fClients.indexOf(client);
        if (index > -1) {
            MidiSetup.fClients.splice(index, 1);
        }
    }
}