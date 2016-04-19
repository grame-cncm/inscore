class OSCAddress {

// ATTRIBUTES
//--------------------------------------------------------------     
    static kAddressSep: string = "/";
    static npos: number = -1; 
    
// METHODS
//--------------------------------------------------------------  
    static addressFirst (a: string): string {
        if (a[0] == this.kAddressSep) {
            var n: number = a.indexOf(this.kAddressSep, 1);
            if (n == this.npos) n = a.length;
            return a.substr(1, n-1);
        }
        return "";
    }

    static addressTail (a: string) : string {
        if (a[0] == this.kAddressSep) {
            var n: number = a.indexOf(this.kAddressSep, 1);
            if (n != this.npos) {
                return a.substr(n, a.length - n);
            }
        }
        return "";
    }
}