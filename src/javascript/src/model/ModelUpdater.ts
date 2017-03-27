
///<reference path="../inscore.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="IObject.ts"/>

class ModelUpdater {
	private fRoot: IObject;

    constructor(root: IObject) { this.fRoot = root; }

	update (stack: Array<IMessage>) : void {
        let elt = stack.length;
        if (elt != 0) {
            for (let i = elt; i > 0; i--) {
				let msg = stack[i];
                INScore.checkStatus ( this.fRoot.process(msg), msg)
            }
        } 
	}	
}
