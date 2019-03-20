
#include <iostream>
#include <fstream>
#include <string>

#include "IParser2.h"
#include "reduce.h"
#include "dotprinter.h"
#include "oscprinter.h"
#include "inscorev1printer.h"
//#include "mathEval.h"
//#include "addressEval.h"
#include "parseEval.h"
//#include "expandEval.h"
#include "evaluator2.h"
//#include "varEval.h"
#include "pathsList.h"



using namespace std;
using namespace inscore2;

static void usage (const char * name) {
	cerr << "usage: " << name << " [options] file" << endl;
	cerr << "       options: -pout to generate the dot parser output" << endl;
	exit (1);
}

static bool checkOption (int argc, char * argv[], const char* option) {
	for (int i = 1; i < argc; i++) {
		const string s(argv[i]);
		if (s == option) return true;
	}
	return false;
}

static const char* input (int argc, char * argv[]) {
	for (int i = 1; i < argc; i++) {
		if (*argv[i] != '-') return argv[i];
	}
	return 0;
}

static int toINScoreV1 (SINode root)
{
	try {
		SINode e = evaluator::eval(parseEval::eval(root));
		inscorev1printer p;
		p.tov1(cout, e);
	}
	catch (parseEvalException e) {
		cerr << "error while evaluating parser output: " << e.what() << endl;
		return 1;
	}
	catch (evalException e) {
		cerr << "error while evaluating expression: " << e.what() << endl;
		return 1;
	}
	return 0;
}


int main (int argc, char * argv[]) {
	if (argc == 1) usage (argv[0]);
	
	bool tov1 	  = checkOption (argc, argv, "-v1");
	bool parse 	  = checkOption (argc, argv, "-parse");
	bool eval 	  = checkOption (argc, argv, "-eval");
	bool printenv = checkOption (argc, argv, "-env");
	bool pathsout = checkOption (argc, argv, "-paths");
	bool pathsonl = checkOption (argc, argv, "-pathsonly");
	bool applyout = checkOption (argc, argv, "-apply");
	const char* file = input (argc, argv);
	if (!file)  usage (argv[0]);

	ifstream f (file);
	IParser p (&f);
	if (p.parse()) {
		SINode root = p.tree();
		if (tov1) return toINScoreV1 (root);

		cerr << "--------------- " << file << " --------------" << endl;
		dotprinter dot (printenv);
		if (parse) {
			dot.print (cout, root->childs());
		}
		else {
		try {
			SINode e = parseEval::eval(root);
			SINode toprint = e;
			if (eval) 			toprint = evaluator::eval(e);
			else if (pathsout)	toprint = pathsList::eval( evaluator::eval( e ));
			else if (pathsonl)	toprint = pathsList::eval( evaluator::eval( e ), false);
			else if (applyout)	toprint = reduce::apply (evaluator::eval( e ));

			if (applyout)	dot.print (cout, toprint.get());
			else dot.print (cout, toprint->childs());
			oscprinter::print(cerr, toprint);
		}
		catch (parseEvalException e) {
			cerr << "error while evaluating parser output: " << e.what() << endl;
			return 1;
		}
		catch (evalException e) {
			cerr << "error while evaluating expression: " << e.what() << endl;
			return 1;
		}
		}
	}
	else return 1;
	return 0;
}


