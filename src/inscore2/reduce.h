
#ifndef __reduce__
#define __reduce__


#include "INode.h"

namespace inscore2
{

//------------------------------------------------------------
class reduce
{
	static SINode applySubs (const SINode& n1, const SINode& n2);
	static SINode apply (const SINode& n1, const SINode& n2);

	public:
		static SINode apply (const SINode& node);
};

} // end namespace

#endif

