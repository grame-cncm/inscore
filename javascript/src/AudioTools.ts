
///<reference path="lib/libINScore.d.ts"/>
///<reference path="JSObjectView.ts"/>
///<reference path="AudioObject.ts"/>

interface cnxFunction { (src: AudioNode, dest: AudioNode) : boolean };

class AudioTools {
 
    static updateConnections(obj: INScoreObject, view: JSObjectView) {
        let cnx = obj.getAudioInfos();
        AudioTools.doit(view, cnx.connect, AudioTools.connectSrcDest, "connect");
        AudioTools.doit(view, cnx.disconnect, AudioTools.disconnectSrcDest, "disconnect");
    }

    static connectSrcDest(src: AudioNode, dest: AudioNode) : boolean {
        if (src && dest) {
            try {
                src.connect(dest);
            }
            catch (error) {
                console.log ("Exception while calling AudioNode connect: " + error);
            }
            return true;
        }
        console.log ("AudioTools error: trying to connect null AudioNode");
        return false;
    }
    static disconnectSrcDest(src: AudioNode, dest: AudioNode) : boolean {
        if (src && dest) {
            try {
                src.disconnect(dest);
            }
            catch (error) {
                console.log ("Exception while calling AudioNode disconnect: " + error);
            }
            return true;
        }
        console.log ("AudioTools error: trying to disconnect null AudioNode");
        return false;
    }

    static doit (view: JSObjectView, list: IntVector, cnx: cnxFunction, op: string) {
        let n = list.size();
        for (let i = 0; i < n; i++) {
            let tmp = JSObjectView.getObjectView(list.get(i));
            if (tmp) {
                let dest = tmp.toAudioObject();
                let src = view.toAudioObject();
                if (src && dest)
                    cnx (src.getAudioNode(), dest.getAudioNode());
                else {
                    console.log ("AudioTools " + op + " error: not an audio object: " + view + " -> " + tmp);
                }
            }
            else {
                console.log ("AudioTools error: incorrect view received by " + op + " method: " + list.get(i));
            }
        }
    }
}