
///<reference path="JSObjectView.ts"/>
///<reference path="interfaces.ts"/>

class TMaster {
	private fMaster: JSObjectView;
	private fSlave: JSObjectView;

	constructor(m: JSObjectView, s: JSObjectView) {
		this.fMaster = m;
		this.fSlave = s;
		// m.getElement().appendChild (s.getElement());
	}

	master() : JSObjectView	{ return this.fMaster; }
	slave() : JSObjectView 	{ return this.fSlave; }

	// unsync () : void	{ this.master().removeChild(this.slave().getElement());}
	unsync () : void	{ }
}

class TSyncManager implements GraphicSyncManager {

	private fTarget: JSObjectView;
	private fSync = new Array<TMaster>();

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

		removed.forEach ( (element: TMaster, index: number): void => { this.remove(index); } );
		newmasters.forEach ( (element: JSObjectView, index: number): void => { this.add(element); } );

// let n = obj.getMasters().size();
// if (n || this.countMasters())
console.log(this + ".updateSync " + obj.getMasters().size() + " on input -  remove: " + removed.length  + " - add: " +  newmasters.length + " currents: " + this.countMasters());
// else return false;

// the sync list is now updated
		let updated = 0;
		this.fSync.forEach( (element: TMaster, index: number) : void => {
			if (element) {
//console.log(this + " call update id: " + element.slave().getId() + " " + element.slave()  + " master id: " +  element.master().getId() + " " + element.master());
				updated++;
			}
		});
		if (!updated) this.fSync = [];
		console.log(this + " id: " + this.fTarget.getId() + " updated masters : " + updated);
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
console.log(this + ".add " + obj.getId() + " " + obj);
		let m = new TMaster(obj, this.fTarget);
		this.fSync[obj.getId()] = m;
	}

	private remove (index: number) : void {
console.log(this + ".remove " + index);
// 		let master = this.fSync[index];
// console.log(this + ".remove " + index + " " + master.slave() + " id: " + master.slave().getId());
// 		master.unsync();
		this.fSync[index] = null;
	}

	// private find (tbl: Array<JSObjectView>, obj: JSObjectView) : JSObjectView {
	// 	let index =  tbl.indexOf (obj);
	// 	return (index < 0) ? null : obj; 
	// }

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

	// private filter (tbl: Array<TMaster>, f: Array<TMaster>) : Array<TMaster> {
	// 	let out = new Array<JSObjectView>();
	// 	tbl.forEach ( (element: TMaster, index: number) : void => {
	// 		if (!f[index]) out.push(tbl[index]);
	// 	} );
	// 	// for (let i=0; i < tbl.length; i++) {
	// 	// 	if (this.find (f, tbl[i]) != null) i++
	// 	// 	else out.push(tbl[i]);
	// 	// }
	// 	return out;
	// }

	// concat tables without duplicates
	// private union (t1: Array<TMaster>, t2: Array<TMaster>) : Array<TMaster> {
	// 	let t = this.filter (t2, t1);
	// 	return t1.concat (t)
	// }	
}
