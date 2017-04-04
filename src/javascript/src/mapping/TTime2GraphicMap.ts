
///<reference path="TTime2GraphicRelation.ts"/>
///<reference path="TSegment.ts"/>
///<reference path="../lib/TTypes.ts"/>

//--------------------------------------------------------------------
// Segmentation class
//--------------------------------------------------------------------
class TTime2GraphicMap {
	protected fRelations: Array<TTime2GraphicRelation>;

	constructor() { this.fRelations = []; }

	toString(): string  { 
		let out = "[\n";
		this.fRelations.forEach( function (elt: TTime2GraphicRelation) { out += " " + elt + ",\n" } );
		return out + "]";
	}
	
	addElt(elt: TTime2GraphicRelation)			{ this.fRelations.push(elt); }
	addElts(elts: Array<TTime2GraphicRelation>)	{ elts.forEach ( function (elt: TTime2GraphicRelation) { this.fRelations.push(elt); } ); }

	clear()	: void		{ this.fRelations = []; }

	time2Relation (loc: Fraction) : TTime2GraphicRelation {
		for (var i=0; i < this.fRelations.length; i++)
			if ( this.fRelations[i].includeTime(loc)) return this.fRelations[i];
		return null;
	}

	point2Relation (loc: TPosition ) : TTime2GraphicRelation {
		for (var i=0; i < this.fRelations.length; i++)
			if ( this.fRelations[i].includePoint(loc)) return this.fRelations[i];
		return null;
	}

	size() : number			{ return this.fRelations.length; }
}
