
#ifndef __inscorev1printer__
#define __inscorev1printer__

#include <ostream>

#include "INode.h"

namespace inscore2
{

class inscorev1printer
{
	std::ostream& 	print (std::ostream& os, const SINode& node);

	public:
				 inscorev1printer() {}
		virtual ~inscorev1printer() {}
	
		std::ostream& tov1 (std::ostream& os, const SINode& node);
};

} // end namespace

#endif

