
interface AMethod  { (n: number): void; }

class A {
	fN: number;

	constructor() { this.fN = 0; }
	static square(n: number) : number { return n*n; }

	call (f: AMethod, n: number): void 	{ f(n); }

	fA (): string 				{ return "Class A"; }
	fX = function(n: number) : void { this.fN = n; };
}
