
#include <sstream>

#include "oscprinter.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
void oscprinter::print (ostream& os, const SINode& node, std::string prefix)
{
	print (os, node.get(), prefix);
}

//------------------------------------------------------------
void oscprinter::print (ostream& os, const INode* node, std::string prefix)
{
	switch ( node->getType() ) {
	 	case INode::kForest:
			print (os, node->childs(), prefix);
			break;
	 	case INode::kSlash:
			print (os, node->childs(), prefix);
			break;
	 	default:
			string p = prefix + "/" + node->getValue();
			for (auto n: node->childs()) print (os, n, p );
			if (node->empty()) os << p << ";" << endl;
	}
}

//------------------------------------------------------------
void oscprinter::print (ostream& os, const NList& nodes, std::string prefix)
{
	for (auto n: nodes) {
		print (os, n, prefix);
	}
}

} // end namespace

