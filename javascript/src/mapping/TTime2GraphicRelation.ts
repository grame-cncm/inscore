
///<reference path="TSegment.ts"/>
///<reference path="../lib/TTypes.ts"/>

//--------------------------------------------------------------------
// A relation between a graphic segment and a time segment
//--------------------------------------------------------------------
class TTime2GraphicRelation {
	fTime	: TTimeSegment;
	fGraph	: TGraphicSegment;

	constructor(time: TTimeSegment, graph: TGraphicSegment) { 
		this.fTime = time; 
		this.fGraph = graph; 
	}

	toString(): string  		{ return this.fTime.toString() + " -> " + this.fGraph.toString(); }

	includeTime (loc: Fraction) : boolean	{ return this.fTime.includeLocation (loc); }
	includePoint (loc: TPosition) : boolean { return this.fGraph.includeLocation (loc); }
}
