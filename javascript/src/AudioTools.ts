class AudioTools {
    static updateConnections(obj: JSObjectView) {
        let cnx = obj.getAudioInfos();
        AudioTools.connect(obj, cnx.connect);
        AudioTools.disconnect(obj, cnx.disconnect);
    }

    static connect(obj: AudioObject, list: IntVector) {
        let n = list.size();
        for (let i = 0; i < n; i++) {
            let view = JSObjectView.fObjects[list[i]];
            let node = view.toAudioObject();
            if (node) {
                obj.getAudioNode().connect(node);
            }
            else {
                // TODO: proper error handling
            }
        }
    }

    static disconnect(obj: AudioObject, list : IntVector) {
        let n = list.size();
        for (let i = 0; i < n; i ++) {
            let view = JSObjectView.JSObjectView[list[i]];
            let node = view.toAudioObject();
            if (node) {
                obj.getAudioNode.disconnect(node);
            }
            else {
                // TODO: proper error handling
            }
        }
    }
}