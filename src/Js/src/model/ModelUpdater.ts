
///<reference path="../inscore.ts"/>

class ModelUpdater {

	static update (stack: Array<IMessage>) : void {
        let elt = stack.length;
        if (elt != 0) {
            for (let i = elt; i > 0; i--) {
                let msg = INScore.getGlue().popStack();
                INScore.checkStatus (INScore.getRoot().process(msg), msg)
            }
        } 
	}	
}
