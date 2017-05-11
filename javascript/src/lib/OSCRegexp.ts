

class OSCRegexp {
    protected fRegExp: RegExp;    
    constructor(regexp: string) { this.fRegExp = new RegExp("^"+OSCRegexp.OSCRe2Re(regexp)+"$"); }    

	static OSCRe2Re (re: string) : string {
		let outstr = "";
		let inlist = false;
		for (let i=0; i<re.length; i++) {
			switch(re[i]) {
				case '{': outstr += '('; inlist = true; break;
				case ',':	outstr += (inlist ? '|' : ','); break;
				case '}':	outstr += ')'; inlist = false; break;
				case '*':	outstr += ".*"; break;
				case '?':	outstr += '.'; break;
				default:	outstr += re[i];
			}
		}
		return outstr;
	}

    match(str: string) : boolean {
    	return this.fRegExp.test( str ); 
    }
}
