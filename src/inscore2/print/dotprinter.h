
#ifndef __dotprinter__
#define __dotprinter__

#include <iostream>

#include "INode.h"

namespace inscore2
{

class dotprinter
{
	std::ostream*	fStream;
	bool 			fPrintEnv;
	
	void start(std::ostream& os) const		{ os << "digraph impl {\n margin=0.05\n" << std::endl;}
	void end(std::ostream& os) const		{ os <<  "}" << std::endl; }
	void printNames (const INode* node);
	void printLinks (const INode* node);

	std::string id (const INode *) const;
	std::string label (const INode *) const;

	public:
				 dotprinter(bool printenv=false) : fStream(0), fPrintEnv(printenv) {}
		virtual ~dotprinter() {}

		void print (std::ostream& os, const INode* node);
		void print (std::ostream& os, const NList& nodes);
};

} // end namespace

#endif

