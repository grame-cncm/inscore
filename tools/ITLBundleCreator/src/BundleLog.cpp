#include <cmath>

#include "BundleLog.h"

namespace itlbundle{

BundleLog::BundleLog()
	: fActive(false)
{

}

void BundleLog::setActive(bool active)
{
	fActive = true;
}

void BundleLog::section(std::string sectionName)
{
	fTab = 0;
	printLog("⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼\n");
	size_t space = sectionName.length()>50? 0 : 50 - sectionName.length();
	sectionName.insert(0,0>floor(space/2.)?0:floor(space/2.), ' ');
	printLog(sectionName);
	printLog("\n⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼\n");
	fTab = 1;
}

void BundleLog::exitSection()
{
	fTab=0;
	printLog("\n                -- -- -- -- -- \n\n");
}

void BundleLog::subSection(std::__cxx11::string subSectionName)
{
	printLog("\n ⏤ "+subSectionName+" ⏤ \n");
	fTab++;
}

void BundleLog::exitSubSection()
{
	if(fTab>1)
		fTab--;
}

void BundleLog::printLog(std::string msg)
{
	if(fActive){
		size_t pos=0;
		while(pos < msg.length()-1){
			pos = msg.find('\n', pos);
			for (int i = 0; i < fTab; ++i)
				msg.insert(pos+1, "\t");
			pos += fTab;
		}

		if(fNewLine)
			for (int i = 0; i < fTab; ++i)
				msg.insert(0, "\t");
		fNewLine = *(msg.end()) == '\n';

		printLog<std::string>(msg);
	}
}

void BundleLog::error(std::string msg) const
{
	std::cerr<<"Error: "<<msg<<std::endl;
}

} // end namespace
