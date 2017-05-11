
///<reference path="../model/IObject.ts"/>

class ViewUpdater {
    
	static update ( obj: IObject) : void {
		if (!obj.getDeleted()) {
			let state = obj.getState();
			if (state & (eObjState.kNewObject + eObjState.kModified)) {
				let views = obj.getViews();
				views.forEach ( function(view: VObjectView) { view.updateView(obj); } );
			}
			if (state & eObjState.kSubModified) {
				let subnodes = obj.getSubNodes();
				for (let i=0; i < subnodes.length; i++) {
					this.update (subnodes[i]);
				}
			}
		}
	}	
}
