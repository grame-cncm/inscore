
///<reference path="JSObjectView.ts"/>
///<reference path="interfaces.ts"/>

interface MasterInfo {view: JSObjectView, vstretch: boolean; }

class TMaster {
	private fMaster: JSObjectView;
	private fSlave: JSObjectView;
	private fClone: JSObjectView;
	private fVStretch: boolean;

	constructor(m: JSObjectView, s: JSObjectView, vstretch: boolean) {
		this.fMaster = m;
		this.fSlave = s;
		this.fClone = s.clone (m);
		this.fVStretch = vstretch;
		m.getElement().appendChild (this.fClone.getElement());
	}

	master() : JSObjectView		{ return this.fMaster; }
	slave()  : JSObjectView 	{ return this.fClone; }
	scale()  : boolean 	 		{ return !this.fVStretch; }

	unsync () : void	{ 
		this.master().getElement().removeChild(this.fClone.getElement()); 
		this.fClone.delete(); 
	}
}

class TSyncManager implements GraphicSyncManager {

	private fSync = new Array<TMaster>();
	private fTarget: JSObjectView;
	private fRemoveChild = true;

	constructor(obj: JSObjectView) {
		this.fTarget = obj;
	}

	toString() : string		    { return "TSyncManager"; }

	updateSync(obj: INScoreObject): boolean {
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
		newmasters.forEach ( (element: MasterInfo, index: number): void => { this.add(element); } );

		// the sync list is now updated
		let updated = 0;
		this.fSync.forEach( (m: TMaster, index: number) : void => {
			if (m) {
				m.slave().updateView (obj, m.master().getIObject(), false, m.scale());
				updated++;
			}
		});
		if (updated) return true;

		this.fSync = [];
		this.fTarget.getParent().getElement().appendChild (this.fTarget.getElement());
		this.fRemoveChild = true;
		return false;
	}

	clean() : void 		{ this.fSync.forEach ( (m: TMaster, index: number) : void => { this.remove (index); }); }

	//-----------------------------------------------------------------------
	// table utilities
	//-----------------------------------------------------------------------
	// convert a vector of identifiers into a table of JSObjectView (masters)
	private masters2Objects (vec: MastersVector) : Array<MasterInfo> {
		let m = new Array<MasterInfo>();
		for (let i=0; i < vec.size(); i++) {
			let master = vec.get(i);
			m[master.viewid] = { view: JSObjectView.getVObject(master.viewid), vstretch: master.vstretch };
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
		
	private add (obj: MasterInfo) : void {
		let m = new TMaster(obj.view, this.fTarget, obj.vstretch);
		this.fSync[obj.view.getId()] = m;
	}

	private remove (index: number) : void {
 		let master = this.fSync[index];
 		master.unsync();
		this.fSync[index] = null;
	}

	// give a table of the objects not sync list
	private newSync (objs: Array<MasterInfo>) : Array<MasterInfo> {
		let out = new Array<MasterInfo>();
		objs.forEach ( (element: MasterInfo, index: number) : void => {
			if (!this.fSync[index]) out.push(objs[index]);
		} );
		return out;
	}

	// give a table of obsolete masters in sync list
	private obsolete (f: Array<MasterInfo>) : Array<TMaster> {
		let out = new Array<TMaster>();
		this.fSync.forEach ( (element: TMaster, index: number) : void => {
			let current = this.fSync[index];
			if (!f[index] && current) out[index] = current;
		} );
		return out;
	}
}
