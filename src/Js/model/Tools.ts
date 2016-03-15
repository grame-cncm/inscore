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

enum MsgHandler { 
    kBadAddress,
    kProcessed = 1,
    kProcessedNoChange = 2,
    kBadParameters = 4,
    kCreateFailure = 8,
}

enum state {
    kClean,
    kNewObject = 1,
    kModified = 2,
    kSubModified = 4,
    kMasterModified = 8, 
}