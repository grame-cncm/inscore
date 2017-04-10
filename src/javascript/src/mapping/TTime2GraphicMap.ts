
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

	date2Relation (d: Fraction ) : TTime2GraphicRelation {
		for (var i=0; i < this.fRelations.length; i++)
			if ( this.fRelations[i].includeTime(d)) return this.fRelations[i];
		return null;
	}

	private pos2IObjectPos (n: number) :  number							{ return (n * 2) - 1 }
	private interval2IObjectInterval (i: NumberInterval) :  NumberInterval	{ 
					return new NumberInterval(this.pos2IObjectPos(i.first()), this.pos2IObjectPos(i.second())); }

	date2MapLocation (date: Fraction) :  { x: number, y: NumberInterval }	{
		let relation = this.date2Relation (date);
		if (relation) {
			let timeinterval = relation.fTime;
			let offset = date.toNum() - timeinterval.first().toNum();
			if (offset >= 0) {
				let relativepos = offset / (timeinterval.second().toNum() - timeinterval.first().toNum());
				let xpos = this.pos2IObjectPos ((relation.fGraph.first().second() - relation.fGraph.first().first()) * relativepos);
				return { x: xpos, y: this.interval2IObjectInterval(relation.fGraph.second()) };
			}
			else console.log ("Unexpected offset " + offset + " in TTime2GraphicMap.date2MapPoint");
		}
		return { x: kNoPosition, y: new NumberInterval(0,0) };
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
