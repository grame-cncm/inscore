
abstract class M { abstract update() : void; }
abstract class V { abstract updateView (m: M) : void; }

class M1 implements M {
	fV: V;
	fName: string;
	constructor () { this.fV = new V1(); this.fName="M1"; }
	getName() : string { return this.fName; }
	update() : void { this.fV.updateView (this); }
}

class M2 implements M {
	fV: V;
	constructor () { this.fV = new V1(); }
	update() : void { this.fV.updateView (this); }
}

// ==> V1 implementation of V is incorrect but not detected by the compiler
class V1 implements V {
	updateView (m: M1) : void { console.log (m.getName() + ": update called"); }
}

var m1 = new M1();
m1.update();

// ==> incorrect use of V1 by M2 not detected at compile time, generates an error at run time
var m2 = new M2();
m2.update();



// the V2 declaration generates an error at compile time
/*
abstract class X { abstract amethods () : void; }
class V2 implements V {
	updateView (m: X) : void { console.log ("V2 update called"); }
}
*/