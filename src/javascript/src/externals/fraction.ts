class Fraction {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    protected numerator: number;
    protected denominator: number;

// CONSTRUCTOR
//-------------------------------------------------------------- 
    constructor(a: number|Fraction|string, b?:number) {
        if (a instanceof Fraction) {
            this.numerator = a.numerator;
            this.denominator = a.denominator;
        } 
        else if (typeof a === "number" && b === undefined) {
            this.rational2fraction(a);
        } 
        else if (typeof a === "number" && b !== undefined) {
            this.numerator = a;
            this.denominator = b;
        }
        else if (typeof a === "string" && b === undefined) {
            let myRegex = /^([0-9]+)\/([0-9]+)$/.test(a);
            if (myRegex) {
	            this.numerator = parseInt(RegExp.$1);
    	        this.denominator = parseInt(RegExp.$2);
    	    }
        }
    
        if (this.denominator == 0) { this.numerator = undefined; this.denominator = undefined}     // undefined if denominator = 0
    }

// CONVERTION RATIONAL TO A FRACTION
//-------------------------------------------------------------- 
    rational2fraction(value: number): void {
        let cpt:number = 1;
        let test:number = 0;
        while (value*cpt != test) {
            cpt++;
            test = Math.floor(value*cpt);
        }     
        this.numerator = value*cpt;
        this.denominator = cpt;
        this.reduce();
    }
    
// CONVERT NUMERIC FRACTION TO A STRING
//-------------------------------------------------------------- 
    toString() 					{ return `${this.numerator}/${this.denominator}`; }
    toNum() : number			{ return this.numerator / this.denominator; }
    toArray() : Array<number>	{ return [this.numerator, this.denominator]; }

// OPERATORS FONCTIONS
//-------------------------------------------------------------- 
    // fraction1 + fraction2 => var sum = fraction1.add(fraction2)
    add(value: Fraction|number) {
        let that:Fraction = new Fraction (value); 
        let denominator = this.denominator * that.denominator;
        that.numerator = this.numerator * that.denominator + that.numerator * this.denominator; 
        that.denominator = denominator;     
        return that.reduce(); 
    }

    // fraction1 * fraction2 => var result = fraction1.sum(fraction2)
    mul(value: Fraction|number) {
        let that:Fraction = new Fraction (value);    
        that.numerator = this.numerator * that.numerator;
        that.denominator = this.denominator * that.denominator;
        return that.reduce();
    }

    // fraction1 / fraction2 => var result = fraction1.div(fraction2)
    div(value: Fraction|number) {
        let that:Fraction = new Fraction (value);
        [that.numerator, that.denominator] = [that.denominator, that.numerator];
        return this.mul(that);
    }

    // fraction1 - fraction2 => var result = fraction1.sub(fraction2)
    sub(value: Fraction|number) {   
        let that:Fraction = new Fraction (value);
        that.numerator = -that.numerator;
        return this.add(that);
    }
    
     // inverse a fraction
    inverse(): Fraction {
        return new Fraction(this.denominator, this.numerator).reduce();
    }
    
     // comparisons
    eq(f: Fraction): boolean {
    	let f1 = new Fraction(this.denominator, this.numerator).reduce();
    	let f2 = new Fraction(f).reduce();
        return (f1.denominator == f2.denominator) && (f1.numerator == f2.numerator);
    }
    gt (f: Fraction): boolean { return this.toNum() > f.toNum(); }
    geq(f: Fraction): boolean { return this.toNum() >= f.toNum(); }
    lt (f: Fraction): boolean { return this.toNum() < f.toNum(); }
    leq(f: Fraction): boolean { return this.toNum() <= f.toNum(); }
    
    // reduce a fraction : Euclide algorithme
    reduce(): Fraction {
        let n = this.numerator;
        let d = this.denominator;
        let that: Fraction = new Fraction(n, d);
        
        let a = Math.max (n, d);
        let b = Math.min (n, d);
        if (b == 0) return that;
        
        let rest = a%b;        
        while (rest != 0) {
            a = b;
            b = rest;                               // var b is the PGCD if the rest is equal to 0
            rest = a%b;
        }
        
        that.numerator = this.numerator/b;
        that.denominator = this.denominator/b;
        return that;      
    }
    
// GETS AND SETS VALUES
//--------------------------------------------------------------
    getDenominator(): number { return this.denominator; }
    
    getNumerator(): number { return this.numerator; }
    
    setDenominator(value: number): void { this.denominator = value; }
        
    setNumerator(value: number): void { this.numerator = value; }
    
}

//export default Fraction;