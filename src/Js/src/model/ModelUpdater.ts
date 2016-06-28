
class ModelUpdater {

	static update (stack: Array<any>) : void {
        let elt = stack.length;
        for (let i = elt; i > 0; i--) {
            INScore.processData(INScore.stackPop());
            
        }
	}	
}
