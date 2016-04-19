class Tools {
    
    static regexp (str: string): boolean
    {
        var n: number = str.length;
        for (var i: number = 0; i < n; i++) {
            if ((str[i] == '*') || (str[i] == '?') || (str[i] == '['))
                return true;
        }
        return false;
    }
}