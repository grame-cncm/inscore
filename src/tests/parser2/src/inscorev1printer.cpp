
#include <sstream>

#include "inscorev1printer.h"
#include "pathsList.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
class v1Msg {
	string			fAddress;
	vector<string>	fArgs;
	vector<v1Msg>	fMsgArgs;

	void 			parseNode (const SINode& node);
	const SINode	getAddress (const SINode& node);
	void 			getParams (const SINode& node);

	public :
				 v1Msg(SINode node) { parseNode(node); }
		virtual ~v1Msg() {}

		void print (ostream& os, string shift="") const;
};

ostream& operator << (ostream& os, const v1Msg& msg) { msg.print (os); return os; }

//------------------------------------------------------------
void v1Msg::print (ostream& os, string shift) const
{
	os << shift << fAddress;
	for (auto n: fArgs) os << " " << n;
	size_t n = fMsgArgs.size();
	if (n) {
		os << " (" << endl;
		const char* sep = "";
		for (auto n: fMsgArgs) {
			os << sep;
			n.print (os, shift + "  ");
			sep = ",\n";
		}
		os << endl << shift << ")";
	}
}

//------------------------------------------------------------
void v1Msg::parseNode (const SINode& node)
{
	getParams ( getAddress (node));
}

//------------------------------------------------------------
const SINode v1Msg::getAddress (const SINode& node)
{
	const SINode next = node->size() ? node->childs()[0] : 0;
	if (node->address()) {
		fAddress += "/";
		fAddress += node->getValue();
		return next ? getAddress (next) : 0;
	}
	else return node;
}

//------------------------------------------------------------
void v1Msg::getParams (const SINode& node)
{
	if (!node) return;
	if (node->address()) {
		v1Msg msg (node);
		fMsgArgs.push_back (msg);
	}
	else {
		string prefix;
		if (node->getType() == INode::kVariable) prefix = "$";
		fArgs.push_back (prefix + node->getValue());
		for (auto n: node->childs())
			getParams (n);
	}
}

//------------------------------------------------------------
ostream& inscorev1printer::print (ostream& os, const SINode& node)
{
	if( node->getType() == INode::kForest) {
		for (auto n: node->childs()) print(os, n);
	}
	else {
		v1Msg msg (node);
		os << msg << ";" << endl;
	}
	return os;
}


//------------------------------------------------------------
ostream& inscorev1printer::tov1 (ostream& os, const SINode& node)
{
	return print (os, pathsList::eval(node));
}


} // end namespace
