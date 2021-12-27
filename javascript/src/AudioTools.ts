
///<reference path="lib/libINScore.d.ts"/>
///<reference path="JSObjectView.ts"/>
///<reference path="AudioObject.ts"/>

interface cnxFunction { (src: AudioObject, dest: AudioObject, srcchan: number, destchan: number) : boolean };

class AudioTools {

    static updateConnections(cnx: OAudioNodeInfos, view: JSObjectView) {
        AudioTools.doit(view, cnx.connect, AudioTools.connectSrcDest, "connect");
        AudioTools.doit(view, cnx.disconnect, AudioTools.disconnectSrcDest, "disconnect");
    }

    static connectSrcDest(src: AudioObject, dest: AudioObject, srcchan: number, destchan: number) : boolean {
        if (src && dest) {
            try {
                if (srcchan || destchan) {
                    let splitter = src.getSplitter();
                    let merger   = dest.getMerger();
                    if (srcchan) {
                        if (destchan) splitter.connect(merger, srcchan - 1, destchan - 1);
                        else splitter.connect(dest.getAudioNode(), srcchan - 1);
                    }
                    else src.getAudioNode().connect(merger, srcchan, destchan - 1);
                }
                else src.getAudioNode().connect(dest.getAudioNode());
            }
            catch (error) {
                console.log ("Exception while calling AudioNode connect: " + error);
            }
            return true;
        }
        console.log ("AudioTools error: trying to connect null AudioNode (" + src + " " + dest + ")");
        return false;
    }
    
    static disconnectSrcDest(src: AudioObject, dest: AudioObject, srcchan: number, destchan: number) : boolean {
        if (src && dest) {
            try {
                if (srcchan || destchan) {
                    let splitter = src.getSplitter();
                    let merger   = dest.getMerger();
                    if (srcchan) {
                        if (destchan) splitter.disconnect(merger, srcchan-1, destchan-1);
                        else splitter.disconnect(dest.getAudioNode(), srcchan-1);
                    }
                    else src.getAudioNode().disconnect(merger, srcchan, destchan-1);
                }
                else src.getAudioNode().disconnect(dest.getAudioNode());
            }
            catch (error) {
                console.log ("Exception while calling AudioNode disconnect (", srcchan, destchan, ")", error);
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
                    cnx (src, dest, cdesc.from, cdesc.to);
                }
                else console.log ("AudioTools " + op + " error: not an audio object: " + view + " -> " + tmp);
            }
            else console.log ("AudioTools error: incorrect view received by " + op + " method: " + cdesc.objid);
        }
    }
}