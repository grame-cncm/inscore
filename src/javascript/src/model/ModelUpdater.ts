
///<reference path="../inscore.ts"/>
///<reference path="../controller/IMessage.ts"/>

class ModelUpdater {

	static update (stack: Array<IMessage>) : void {
        let elt = stack.length;
        if (elt != 0) {
            for (let i = elt; i > 0; i--) {
				let msg = stack[i];
                INScore.checkStatus (INScore.getRoot().process(msg), msg)
            }
        } 
	}	
}
