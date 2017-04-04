
///<reference path="../lib/TInterval.ts"/>
///<reference path="../lib/TTypes.ts"/>

type TTimeSegment = TInterval<Fraction>;

//--------------------------------------------------------------------
// Graphic segments class
//--------------------------------------------------------------------
class TGraphicSegment	{ 
	protected fXInterval: 	NumberInterval;
	protected fYInterval: 	NumberInterval;

	constructor(xinterval?: NumberInterval, yinterval?: NumberInterval) {
		if (xinterval) {
			this.fXInterval = xinterval;
			this.fYInterval = yinterval ? yinterval : xinterval;
		}
		else {
			this.fXInterval = new NumberInterval(0,0);
			this.fYInterval = new NumberInterval(0,0);
		}
	}

	toString(): string  { return "[" + this.fXInterval + ", " + this.fYInterval + "]"; }

	first(): NumberInterval			{ return this.fXInterval; }
	second(): NumberInterval		{ return this.fYInterval; }
	size(): number 					{ return this.fXInterval.size() * this.fYInterval.size(); }
	empty() : boolean				{ return this.fXInterval.empty() || this.fYInterval.empty(); } 

	eq (s: TGraphicSegment) : boolean	{ return this.fXInterval.eq(s.fXInterval) && this.fYInterval.eq(s.fYInterval); }
	neq (s: TGraphicSegment) : boolean 	{ return !this.eq(s); };

	includeLocation (loc: TPosition) : boolean	{ return this.fXInterval.includeLocation(loc.x) && this.fYInterval.includeLocation(loc.y); }
	include (g: TGraphicSegment) : boolean		{ return this.fXInterval.include(g.first()) && this.fYInterval.include(g.second()); }
}

