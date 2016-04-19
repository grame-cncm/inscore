
declare var INScoreParser;

function parse(msg:string) : Array<any> {
	INScoreParser.parse(msg);
    return INScoreParser.msgs;
}

