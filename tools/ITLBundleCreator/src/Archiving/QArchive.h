#ifndef QARCHIVE_H
#define QARCHIVE_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QDataStream>
#include <string>

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

	QFile* fArchiveFile;
	QArchiveHeader fHeader;


public:
	static SQArchive emptyArchive();
	static SQArchive readArchive(QString path);

	bool compress(QString outputArchive);
	bool extract(QString path);

	bool addDir(QString name);
	//bool addDir(std::string name){return addDir(QString::fromStdString(name));}

	bool	changeDir(QString dir);
	bool	upDir();
	QString currentDir();

	bool addFile(QString name, const QString &path);
	//bool addFile(std::string name, std::string path){return addFile(QString::fromStdString(name),QString::fromStdString(path));}

	bool addBufferedFile(QString name, const QByteArray& data);
	//bool addFile(std::string name, const QByteArray& data){return addFile(QString::fromStdString(name), data);}

	bool addTextFile(QString name, const QString& data);

	bool readFile(QString name, QByteArray &data);

	virtual ~QArchive();

protected:
	QArchive():fHeader(this){}

	bool addFile(QString name, QIODevice* device, quint32 compressedSize=0);

	bool readFile(int fileID, QByteArray &data);
};

class QArchiveData{
	quint32 fSize=0;
	QIODevice* fData;
public:
	QArchiveData(QIODevice* data):fData(data){}

	QIODevice* data() const {return fData;}

	void setCompressedSize(quint32 size){fSize = size;}
	quint32 compressedSize() const {return fSize;}
};



} // End namespace

#endif // QARCHIVE_H
