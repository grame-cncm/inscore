
var parser 	= require("./INScoreParser").parser;

var argv = process.argv;
var argc = argv.length;

for (var i=2; i < argc; i++) {
    var content = require('fs').readFileSync(require('path').normalize(argv[i]), "utf8");
	parser.parse (content);
	var msgs = parser.get();
	for (var n=0; n < msgs.length; n++) {
		console.log (msgs[n].toString());
	}
}

