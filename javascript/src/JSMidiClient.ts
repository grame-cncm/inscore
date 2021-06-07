///<reference types="@types/webmidi"/>

class MidiSetup {
    static midiClients : Array<string>;
    static accessSetup : WebMidi.MIDIAccess;
    
    static midiInput(event: WebMidi.MIDIMessageEvent) {
        var cmd = event.data[0] >> 4;
        var channel = event.data[0] & 0xf;
        var data1 = event.data[1];
        var data2 = event.data[2];
        MidiSetup.midiClients.forEach((addr) => {
            let msg = inscore.newMessageM("event");
            inscore.msgAddStr(msg, "midi");
            if (cmd === 8)
                inscore.msgAddStr(msg, "keyUp");
            else if (cmd === 9)
                inscore.msgAddStr(msg, "keyDown");
            inscore.msgAddI(msg, data1);
            // create msg
            //send using postMesssage
            console.log(data1, data2, channel, cmd);
            console.log("msg", msg);
            console.log(addr, "event midi", data1, cmd);
            inscore.postMessage(addr, msg);
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

    static addListener(addr : string) {
        if (typeof(navigator.requestMIDIAccess) !== "undefined" && MidiSetup.accessSetup !== null) {
            navigator.requestMIDIAccess({"sysex": true}).then(
                (access : WebMidi.MIDIAccess) => {
                    if (!MidiSetup.midiClients) {
                        MidiSetup.midiClients = [];
                    }
                    MidiSetup.midiClients.push(addr);
                    MidiSetup.onConnectionCallback(access);
                }, this.onErrorCallback
            );
        } else {
            alert("MIDI input cannot be activated, either your browser still does't have it, or you need to 						explicitly activate it.");
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

// class MidiIn {
//     addClient(client: MidiClient) {}
//     remove(client: MidiClient) {}

//     midiMessageReceived(ev: WebMidi.MIDIMessageEvent)
//             {
//                 var cmd = ev.data[0] >> 4;
//                 var channel = ev.data[0] & 0xf;
//                 var data1 = ev.data[1];
//                 var data2 = ev.data[2];

//                 if (channel === 9) {
//                     return;
//                 } else if (cmd === 8 || ((cmd === 9) && (data2 === 0))) {
//                     keyOff(channel, data1, data2);
//                 } else if (cmd === 9) {
//                     keyOn(channel, data1, data2);
//                 } else if (cmd === 11) {
//                     ctrlChange(channel, data1, data2);
//                 } else if (cmd === 14) {
//                     pitchWheel(channel, (data2 * 128.0 + data1));
//                 }
                
//                 /*
//                 // Direct message
//                 if (DSP && isPoly) {
//                     DSP.midiMessage(ev.data);
//                 }
//                 */
//             }
// 		onerrorcallback(error: string)
// 		{
// 			console.log(error);
// 		}
					
// 		onsuccesscallbackStandard(access)
// 		{
// 			access.onstatechange = function(e: WebMidi.MIDIConnectionEvent) {
// 				if (e.port.type === "input") {
// 					if (e.port.state === "connected") {
// 						console.log(e.port.name + " is connected");
// 						e.port.onmidimessage = midiMessageReceived;
// 					} else if (e.port.state  === "disconnected") {
// 						console.log(e.port.name + " is disconnected");
// 						e.port.onmidimessage = null;
// 					}
// 				}
// 			}
// 			for (var input of access.inputs.values()) {
// 				input.onmidimessage = midiMessageReceived;
// 				console.log(input.name + " is connected");
// 			}
// 		}
// 		activateMIDIInput()
// 		{
// 			console.log("activateMIDIInput");
// 			console.log(navigator);
// 			if (typeof(navigator.requestMIDIAccess) !== "undefined") {
// 			    navigator.requestMIDIAccess().then(this.onsuccesscallbackStandard, this.onerrorcallback);
// 			} else {
//     			alert("MIDI input cannot be activated, either your browser still does't have it, or you need to explicitly activate it.");
// 			}
// 		}
// }