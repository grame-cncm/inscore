#ifndef QARCHIVE_H
#define QARCHIVE_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QBuffer>
#include <QDataStream>
#include <string>
#include <istream>

#include <smartpointer.h>

#include "Tree.h"
#include "QArchiveHeader.h"

namespace qarchive{

class QArchive;
typedef libmapping::SMARTP<QArchive> SQArchive;

class QArchiveData;

class QArchive: public libmapping::smartable
{
	friend class QArchiveHeader;

	QList<QArchiveData> fFiles;
	Tree<int> fTree;

	QIODevice* fArchiveData;
	QArchiveHeader fHeader;


public:
	static SQArchive emptyArchive();

	static SQArchive readArchive(QString path, QArchiveError& error){return readArchive(new QFile(path), error);}
	static SQArchive readArchive(QString path){QArchiveError e; return readArchive(path, e);}
	static SQArchive readArchiveStd(std::string path, QArchiveError& error){return readArchive(QString::fromStdString(path), error);}
	static SQArchive readArchiveStd(std::string path){QArchiveError e; return readArchiveStd(path, e);}

	static SQArchive readArchive(QByteArray* data, QArchiveError& error){return readArchive(new QBuffer(data), error);}

	static SQArchive readArchive(QIODevice* device, QArchiveError& error);

	QArchiveError compress(QString outputArchive, bool overwrite = true);
	QArchiveError compressStd(std::string outputArchive, bool overwrite = true){return compress(QString::fromStdString(outputArchive), overwrite);}
	QArchiveError extract(QString path, bool overwrite = true);
	QArchiveError extractStd(std::string path, bool overwrite = true){return extract(QString::fromStdString(path), overwrite);}

	bool addDir(QString name);
	bool addDirStd(const std::string& name){return addDir(QString::fromStdString(name));}

	bool		changeDir(QString dir);
	bool		changeDirStd(const std::string& dir){return changeDir(QString::fromStdString(dir));}
	bool		upDir();
	QString		currentDir()	const;
	std::string	currentDirStd()	const {return currentDir().toStdString();}

	bool addFile(QString name, const QString &path);
	bool addFileStd(const std::string& name, const std::string& path){return addFile(QString::fromStdString(name),QString::fromStdString(path));}

	bool addBufferedFile(QString name, const QByteArray& data);
	bool addBufferedFileStd(const std::string& name, const QByteArray& data){return addFile(QString::fromStdString(name), data);}

	bool addTextFile(QString name, const QString& data);
	bool addTextFileStd(const std::string& name, const std::string& data){return addTextFile(QString::fromStdString(name), QString::fromStdString(data));}

	bool readFile(QString name, QByteArray &data);
	bool readFileStd(const std::string& name, QByteArray &data){return readFile(QString::fromStdString(name), data);}

	virtual ~QArchive();

protected:
	QArchive():fHeader(this){}

	bool addFile(QString name, QIODevice* device, quint32 compressedSize=0);

	bool readFile(int fileID, QByteArray &data);
};

class QArchiveData{
	quint32 fSize=0;
	QIODevice* fData;
	bool fCompressed = false;
public:
	QArchiveData(QIODevice* data):fData(data){}

	QIODevice* data() const {return fData;}

	void setCompressedSize(quint32 size){fSize = size;}
	quint32 compressedSize() const {return fSize;}
	void setCompressed(bool isCompressed){fCompressed = isCompressed;}
	bool isCompressed() const{return fCompressed;}

	bool compressedData(QByteArray& data);
	bool uncompressedData(QByteArray& data);
};



} // End namespace

#endif // QARCHIVE_H
