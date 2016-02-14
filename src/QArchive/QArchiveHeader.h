#ifndef QARCHIVEHEADER_H
#define QARCHIVEHEADER_H

#include <QIODevice>
#include <QByteArray>
#include <map>
#include <string>


#define ARCHIVE_VERSION 1.0

namespace qarchive {

enum HEADER_IDENTIFIERS{
	HEADER_END				= 0x00,		// 0000 0000
	HEADER_HIERARCHY		= 0x40,		// 0100 0000
		H_HIER_END			= 0xC0,		// 1100 0000
		H_NEW_DIR			= 0xC1,		// 1100 0001
		H_NEW_FILE			= 0xC2,		// 1100 0010
		H_UPDIR				= 0xC4,		// 1100 0100
	HEADER_PROPERTIES		= 0x20,		// 0010 0000
		H_PROP_END			= 0xA0,		// 1010 0000
		H_ARCHIVE_VERSION	= 0xA1,		// 1010 0001
		H_ITL_VERSION		= 0xA2,		// 1010 0010
	HEADER_CUSTOM_PROP		= 0xC8,		// 1100 1000
		H_CUSTOM_END		= 0x80,		// 1000 0000
};

enum QArchiveError{
	ARCH_OK	=	0,
	FILE_EXIST,
	FILE_NOT_FOUND,
	FILE_CORRUPTED,
	WRONG_PERMISSIONS,
	HIGHER_BUNDLE_VERSION
};

class QArchive;

class QArchiveHeader
{
	friend class QArchive;

	QArchive* fArchive;
	std::map<int, float> fNbrProperties;
	std::map<int, std::string> fStringProperties;

public:
	bool addNbrProperty (int id, float value);
	bool readNbrProperty(int id, float &value);

	bool addStringProperty (int id, std::string value);
	bool readStringProperty(int id, std::string &value);


protected:
	QArchiveHeader(QArchive* archive):fArchive(archive){}

	qreal archiveVersion=ARCHIVE_VERSION;

	QArchiveError	readHeader(QIODevice *input);
	QByteArray		generateHeader() const;

	QByteArray		generateCustomProp() const;
	QArchiveError	readCustomProp(QDataStream &dataStream);

};

} // End namespace
#endif // QARCHIVEHEADER_H
