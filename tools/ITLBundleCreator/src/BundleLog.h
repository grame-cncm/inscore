#ifndef BUNDLELOG_H
#define BUNDLELOG_H

#include <string>
#include <iostream>

namespace itlbundle {

class BundleLog
{
	bool fActive;

	int fTab;
	bool fNewLine;

public:
	BundleLog();

	void setActive(bool active = true);

	void section(std::string sectionName);
	void exitSection();

	void subSection(std::string subSectionName);
	void exitSubSection();

	template <typename T>
	void printLog(T msg){if(fActive) std::cout<<msg;}

	void printLog(std::string msg);
	void printLog(const char* msg){printLog(std::string(msg));}

	void error(std::string msg) const;
};

template <typename T>
BundleLog& operator << (BundleLog& out, T msg) {out.printLog(msg); return out;}

} // end namespace
#endif // BUNDLELOG_H
