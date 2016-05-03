
///<reference path="../model/IObject.ts"/>

class ViewUpdater {
    
	static update ( obj: IObject) : void {
		if (obj.getState() & (objState.kNewObject + objState.kModified)) {
			obj.getView().updateView(obj);
//console.log("ViewUpdater update " + obj.getName());
		}
		if (obj.getState() & objState.kSubModified) {
			let subnodes = obj.getSubNodes();
			for (let i=0; i < subnodes.length; i++)
				this.update (subnodes[i]);
		}
	}	
}
