

class TPoint {
    protected fX: number;
    protected fY: number;
    
    constructor(x: number, y: number) {
        this.fX = x;
        this.fY = y;
    }
    
    toArray(): Array<number> 	{ return [this.fX, this.fY]; }
    toString(): string 			{ return this.toArray().toString(); }
    getX(): number 				{ return this.fX; }
    getY(): number 				{ return this.fY; }
    
    // Methodes de calcul sur les points à faire...
}
