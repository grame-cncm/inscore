#include <iostream>

#include "BundleExtractor.h"

using namespace qarchive;

namespace itlbundle {


bool BundleExtractor::extract(std::string bundleFile, std::string outputFolder)
{
	QArchiveError e;
	SQArchive a = qarchive::QArchive::readArchiveStd(bundleFile, e);

	switch (e) {
	case qarchive::NO_ERROR:
		return writeFiles(a, outputFolder, fForceOverwrite);

	case qarchive::FILE_NOT_FOUND:
		std::cerr<<bundleFile<<" not found."<<std::endl;
		break;
	case qarchive::FILE_CORRUPTED:
		std::cerr<<bundleFile<<" is corrupted."<<std::endl;
		break;
	default:
		std::cerr<<"An error occurs during the reading of the bundle..."<<std::endl;
		break;
	}

	return false;
}

bool BundleExtractor::writeFiles(SQArchive &a, std::string outputFolder, bool overwrite)
{
	QArchiveError e = a->extractStd(outputFolder, overwrite);

	std::string r;
	switch(e){
	case qarchive::NO_ERROR:
		return true;
	case qarchive::FILE_EXIST:
		std::cout<<"File already exist, do you want to overwrite? [O/n]   ";
		std::cin>>r;
		if(r!="n")
			return false;
		else
			return writeFiles(a, outputFolder, true);
		break;
	case qarchive::FILE_CORRUPTED:
		std::cerr<<"Error when uncompressing bundle: the file is corrupted!"<<std::endl;
		break;
	case qarchive::WRONG_PERMISSIONS:
		std::cerr<<"Impossible to write in "<<outputFolder<<std::endl;
		break;

	}
	return false;
}

} // End namespace
