
///<reference path="lib/libINScore.d.ts"/>
///<reference path="JSObjectView.ts"/>
///<reference path="AudioObject.ts"/>

interface cnxFunction { (src: AudioNode, dest: AudioNode, srcchan: number, destchan: number) : boolean };

class AudioTools {
 
    static updateConnections(obj: INScoreObject, view: JSObjectView) {
        let cnx = obj.getAudioInfos();
// console.log ("AudioTools: updateConnections connect: " + obj.getOSCAddress() + " " + cnx.connect.size() + " disconnect: " + cnx.disconnect.size())
        AudioTools.doit(view, cnx.connect, AudioTools.connectSrcDest, "connect");
        AudioTools.doit(view, cnx.disconnect, AudioTools.disconnectSrcDest, "disconnect");
    }

    static connectSrcDest(src: AudioNode, dest: AudioNode, srcchan: number, destchan: number) : boolean {
        if (src && dest) {
            try {
                // if (srcchan) {
// console.log ("AudioTools:connectSrcDest src: " + src.numberOfInputs + " " + src.numberOfOutputs + ":" + src.channelCount  + " mode: " + src.channelCountMode + " - dest: " + dest.numberOfInputs + " " + dest.numberOfOutputs + " chans: " + dest.channelCount + " mode: " + dest.channelCountMode);
// console.log( "src.connect " + dest + "  " + srcchan + ", " + destchan);
// console.log(dest);
// console.log(src);
                    src.connect(dest, srcchan, destchan);

                // }
                // else
                //     src.connect(dest);
            }
            catch (error) {
                console.log ("Exception while calling AudioNode connect: " + error);
            }
            return true;
        }
        console.log ("AudioTools error: trying to connect null AudioNode (" + src + " " + dest + ")");
        return false;
    }
    static disconnectSrcDest(src: AudioNode, dest: AudioNode, srcchan: number, destchan: number) : boolean {
        if (src && dest) {
            try {
                // if (srcchan)
                    src.disconnect(dest, srcchan, destchan);
                // else
                //     src.disconnect(dest);
            }
            catch (error) {
                console.log ("Exception while calling AudioNode disconnect: " + error);
            }
            return true;
        }
        console.log ("AudioTools error: trying to disconnect null AudioNode (" + src + " " + dest + ")");
        return false;
    }

    static doit (view: JSObjectView, list: AudioCnxVector, cnx: cnxFunction, op: string) {
        let n = list.size();
        for (let i = 0; i < n; i++) {
            let cdesc = list.get(i);
            let tmp = JSObjectView.getObjectView(cdesc.objid);
            if (tmp) {
                let dest = tmp.toAudioObject();
                let src = view.toAudioObject();
                if (src && dest) {
                    cnx (src.getAudioNode(), dest.getAudioNode(), cdesc.from, cdesc.to);
                }
                else {
                    console.log ("AudioTools " + op + " error: not an audio object: " + view + " -> " + tmp);
                }
            }
            else {
                console.log ("AudioTools error: incorrect view received by " + op + " method: " + cdesc.objid);
            }
        }
    }
}