class Tools {
    
    static regexp (str: string): boolean
    {
        let n = str.length;
        for (let i: number = 0; i < n; i++) {
            if ((str[i] == '*') || (str[i] == '?') || (str[i] == '['))
                return true;
        }
        return false;
    }
}