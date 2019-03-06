
#ifndef __inscorev1converter__
#define __inscorev1converter__

#include "INode.h"
#include "IMessage.h"

namespace inscore2
{

class inscorev1converter
{
	void tov1 (inscore::SIMessageList msgs, const SINode& node) const;

	public:
				 inscorev1converter() {}
		virtual ~inscorev1converter() {}

	inscore::SIMessageList convert (const SINode& node) const;
};

} // end namespace

#endif

