

#include "INode.h"
#include "TEnv2.h"


namespace inscore2
{

std::ostream& TEnv::print (std::ostream& os) const {
	for (auto n: *this) os << n.first << "=" << n.second->getName() << std::endl;
	return os;
}

} // end namespace
