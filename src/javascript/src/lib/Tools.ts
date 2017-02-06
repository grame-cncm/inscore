class Tools {
    
    static regexp (str: string): boolean
    {
        let n = str.length;
        for (let i = 0; i < n; i++) {
        	let c = str[i];
            if ((c == '*') || (c == '?') || (c == '[') || (c == '{'))
                return true;
        }
        return false;
    }
}