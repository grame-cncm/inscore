
///<reference path="TTypes.ts"/>

class OSCAddress {

// ATTRIBUTES
//--------------------------------------------------------------     
    static kAddressSep: string = "/";
    static npos: number = -1; 
    
// METHODS
//--------------------------------------------------------------  
    static shift (address: string): TPair<string> {
		let head = address.replace(/\/([^\/]+)(\/..*|$)/, "$1");
		let tail = address.replace(/\/[^\/]*(.*)/, "$1");
		return { first: head, second: tail };
    }

    static last (address: string): string {
		return address.replace(/.*\//, "");
    }

    static addressFirst (a: string): string {
        if (a[0] == this.kAddressSep) {
            let n: number = a.indexOf(this.kAddressSep, 1);
            if (n == this.npos) n = a.length;
            return a.substr(1, n-1);
        }
        return "";
    }

    static addressTail (a: string) : string {
        if (a[0] == this.kAddressSep) {
            let n: number = a.indexOf(this.kAddressSep, 1);
            if (n != this.npos) {
                return a.substr(n, a.length - n);
            }
        }
        return "";
    }
}