

class TPoint {
    protected fX: number;
    protected fY: number;
    
    constructor(x: number, y: number) {
        this.fX = x;
        this.fY = y;
    }
    
    toArray(): Array<number> { return [this.fX, this.fY]}
    
    // Methodes de calcul sur les points à faire...
}
