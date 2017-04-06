
///<reference path="TTime2GraphicRelation.ts"/>
///<reference path="TSegment.ts"/>
///<reference path="../lib/TTypes.ts"/>

interface TArrayFunction 			{ (elt: TTime2GraphicRelation): void; }

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

	forEach(f: TArrayFunction)						{ this.fRelations.forEach ( f ); }
	clear()	: void									{ this.fRelations = []; }
	getRelations(): Array<TTime2GraphicRelation> 	{ return this.fRelations; }

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

	mapPoint2Date (point: TPosition) : Fraction	{
		let relation = this.point2Relation (point);
		if (relation) {
			let xinterval = relation.fGraph.first();
			let offset = point.x - xinterval.first();
			if (offset >= 0) {
				let relativepos = offset / xinterval.size();
				let start = relation.fTime.first().toNum();		// computations on fractions are made on numeric values
				let end = relation.fTime.second().toNum();
				let timeoffset = (end - start) * relativepos;
				return Fraction.approximate (start + timeoffset, 1000000);
			}
			else console.log ("Unexpected offset " + offset + " in TTime2GraphicMap.mapPoint2Date");
		}
		return null; 
	}

	size() : number			{ return this.fRelations.length; }
}
