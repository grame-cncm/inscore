
#ifndef __pathsList__
#define __pathsList__

#include <map>

#include "INode.h"

namespace inscore2
{

class pathsList
{
	public:
				 pathsList() {}
		virtual ~pathsList() {}

		static SINode 	eval (const SINode& node);
};

} // end namespace

#endif
