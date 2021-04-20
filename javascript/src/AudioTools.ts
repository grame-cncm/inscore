
///<reference path="lib/libINScore.d.ts"/>
///<reference path="JSObjectView.ts"/>

class AudioTools {
    static updateConnections(obj: INScoreObject, view: JSObjectView) {
        let cnx = obj.getAudioInfos();
        AudioTools.connect(view, cnx.connect);
        AudioTools.disconnect(view, cnx.disconnect);
    }

    static connect(view: JSObjectView, list: IntVector) {
        let n = list.size();
        for (let i = 0; i < n; i++) {
            let tmp = JSObjectView.getObjectView(list.get(i));
            if (tmp) {
                let dest = tmp.toAudioObject();
                let src = view.toAudioObject();
                if (src && dest)
                    src.connect(dest);
                else {
                    console.log ("AudioTools connect error: not an audio object: " + view + " -> " + tmp);
                }
            }
            else {
                console.log ("AudioTools error: incorrect view received by connect method: " + list.get(i));
            }
        }
    }

    static disconnect(view: JSObjectView, list : IntVector) {
        let n = list.size();
        for (let i = 0; i < n; i ++) {
           let tmp = JSObjectView.getObjectView(list.get(i));
            if (tmp) {
                let dest = tmp.toAudioObject();
                let src = view.toAudioObject();
                if (src && dest)
                    src.disconnect(dest);
                else {
                    console.log ("AudioTools disconnect error: not an audio object: " + view + " -> " + tmp);
                }
            }
            else {
                console.log ("AudioTools error: incorrect view received by connect method: " + list.get(i));
            }
        }
    }
}