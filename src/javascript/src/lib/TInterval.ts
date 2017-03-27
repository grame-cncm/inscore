
///<reference path="../externals/fraction.ts"/>

//--------------------------------------------------------------------
// an abstract class to represent intervals
//--------------------------------------------------------------------
abstract class TInterval<T>	{ 
	protected fFirst: 	T;
	protected fSecond:	T;

	constructor(first: T, second: T) {
		this.fFirst = first;
		this.fSecond = second;
	}

	toString(): string  { return "[" + this.fFirst + ", " + this.fSecond + "]"; }

	set( i: TInterval<T>): void  { 
		this.fFirst = i.first();
		this.fSecond = i.second();
	}
	
	first(): T 		{ return this.fFirst; }
	second(): T 	{ return this.fSecond; }

	abstract	empty () : boolean;
	abstract	eq (i: TInterval<T>) : boolean;
				neq (i: TInterval<T>) : boolean 	{ return !this.eq(i); };
	abstract	includeLocation (loc: T) : boolean;
				include (i: TInterval<T>) : boolean	{ return this.includeLocation(i.first()) && this.includeLocation(i.second()); }
}

//--------------------------------------------------------------------
// numbers intervals
//--------------------------------------------------------------------
class NumberInterval extends TInterval<number> { 

	eq (i: NumberInterval) 			: boolean	{ return (this.fFirst == i.first()) && (this.fSecond == i.second()); }
	empty () 						: boolean	{ return this.fFirst == this.fSecond; }
	includeLocation (loc: number) 	: boolean	{ return (this.fFirst <= loc) && (this.fSecond > loc); }
	toArray () 					: Array<number>	{ return [ this.fFirst, this.fSecond ]; }
}

//--------------------------------------------------------------------
// time intervals
//--------------------------------------------------------------------
class TimeInterval extends TInterval<Fraction> { 

	constructor(first: Fraction, second: Fraction) { super (new Fraction(first), new Fraction(second)); }

	toNumInterval () 		: NumberInterval  	{ return new NumberInterval(this.fFirst.toNum(), this.fSecond.toNum()); }
	eq (i: TimeInterval) 			: boolean	{ return (this.fFirst.eq(i.first())) && (this.fSecond.eq(i.second())); }
	empty () 						: boolean	{ return this.fFirst.eq(this.fSecond) }
	includeLocation (loc: Fraction) : boolean	{ return this.fFirst.leq(loc) && this.fSecond.gt(loc); }
	toArray () 					: Array<number>	{ return this.fFirst.toArray().concat(this.fSecond.toArray()); }
}

