
///<reference path="JSObjectView.ts"/>
///<reference path="interfaces.ts"/>

class TMaster {
	private fMaster: JSObjectView;
	private fSlave: JSObjectView;
	private fClone: JSObjectView;

	constructor(m: JSObjectView, s: JSObjectView) {
		this.fMaster = m;
		this.fSlave = s;
		this.fClone = s.clone (m);
		m.getElement().appendChild (this.fClone.getElement());
	}

	master() : JSObjectView	{ return this.fMaster; }
	slave()  : JSObjectView 	{ return this.fClone; }

	unsync () : void	{ this.master().getElement().removeChild(this.fClone.getElement()); }
	// unsync () : void	{ }
}

class TSyncManager implements GraphicSyncManager {

	private fSync = new Array<TMaster>();
	private fTarget: JSObjectView;
	private fRemoveChild = true;

	constructor(obj: JSObjectView) {
		this.fTarget = obj;
	}

	toString() : string		    { return "TSyncManager"; }

	updateSync(obj: INScoreObject, oid: number): boolean {
		let m = obj.getMasters();
		let n = m.size() + this.countMasters();
		if (!n) return false;

		let masters = this.masters2Objects (m);
		let removed = this.obsolete (masters);
		let newmasters = this.newSync (masters);

		if (this.fRemoveChild) {
			this.fTarget.getParent().getElement().removeChild(this.fTarget.getElement());
			this.fRemoveChild = false;
		}
		removed.forEach ( (element: TMaster, index: number): void => { this.remove(index); } );
		newmasters.forEach ( (element: JSObjectView, index: number): void => { this.add(element); } );

// let n = obj.getMasters().size();
// if (n || this.countMasters())
// console.log(this + ".updateSync " + obj.getMasters().size() + " on input -  remove: " + removed.length  + " - add: " +  newmasters.length + " currents: " + this.countMasters());
// else return false;

		// the sync list is now updated
		let updated = 0;
		this.fSync.forEach( (master: TMaster, index: number) : void => {
			if (master) {
				master.slave().updateView (obj, oid);
//console.log(this + " call update id: " + element.slave().getId() + " " + element.slave()  + " master id: " +  element.master().getId() + " " + element.master());
				updated++;
			}
		});
		if (updated) return true;

		this.fSync = [];
		this.fTarget.getParent().getElement().appendChild (this.fTarget.getElement()	);
		this.fRemoveChild = true;
// console.log(this + " id: " + this.fTarget.getId() + " updated masters : " + updated);
		return false;
	}

	//-----------------------------------------------------------------------
	// table utilities
	//-----------------------------------------------------------------------
	// convert a vector of identifiers into a table of JSObjectView (masters)
	private masters2Objects (vec: IntVector) : Array<JSObjectView> {
		let m = new Array<JSObjectView>();
		for (let i=0; i < vec.size(); i++) {
			let id = vec.get(i);
			m[id] = JSObjectView.getVObject(id);
		}
		return m;
	}

	private countMasters () : number {
		let count = 0;
		this.fSync.forEach ( (element: TMaster, index: number) : void => {
			if (element) count++;
		});
		return count;
	}
		
	private add (obj: JSObjectView) : void {
		let m = new TMaster(obj, this.fTarget);
		this.fSync[obj.getId()] = m;
	}

	private remove (index: number) : void {
 		let master = this.fSync[index];
 		master.unsync();
		this.fSync[index] = null;
	}

	// give a table of the objects not sync list
	private newSync (objs: Array<JSObjectView>) : Array<JSObjectView> {
		let out = new Array<JSObjectView>();
		objs.forEach ( (element: JSObjectView, index: number) : void => {
			if (!this.fSync[index]) out.push(objs[index]);
		} );
		return out;
	}

	// give a table of obsolete masters in sync list
	private obsolete (f: Array<JSObjectView>) : Array<TMaster> {
		let out = new Array<TMaster>();
		this.fSync.forEach ( (element: TMaster, index: number) : void => {
			let current = this.fSync[index];
			if (!f[index] && current) out[index] = current;
		} );
		return out;
	}
}
