
#ifndef __oscprinter__
#define __oscprinter__

#include <iostream>
#include <string>

#include "INode.h"

namespace inscore2
{

class oscprinter
{
	public:
		static void print (std::ostream& os, const INode* node, std::string prefix="" );
		static void print (std::ostream& os, const SINode& node, std::string prefix="" );
		static void print (std::ostream& os, const NList& nodes, std::string prefix="" );
};

} // end namespace

#endif

