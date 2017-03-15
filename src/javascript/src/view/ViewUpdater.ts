
///<reference path="../model/IObject.ts"/>

class ViewUpdater {
    
	static update ( obj: IObject) : void {
		if (obj.getDeleted()) {
//			if (obj.getView()) 
//			obj.getView().remove();
		}
		else {
			let state = obj.getState();
			if (state & (objState.kNewObject + objState.kModified)) {
				let view = obj.getView();
				if (view) view.updateView(obj);
			}
			if (state & objState.kSubModified) {
				let subnodes = obj.getSubNodes();
				for (let i=0; i < subnodes.length; i++) {
					this.update (subnodes[i]);
				}
			}
		}
	}	
}
