#include <QBuffer>

#include "QArchive.h"

namespace qarchive{

SQArchive QArchive::emptyArchive()
{
	return new QArchive();
}

SQArchive QArchive::readArchive(QString path)
{
	QArchive* a = new QArchive();
	a->fArchiveFile = new QFile(path);

	a->fHeader.readHeader(a->fArchiveFile);

	return a;
}


bool QArchive::compress(QString outputArchive)
{

	if(fArchiveFile)
		delete fArchiveFile;

	fArchiveFile = new QFile(outputArchive);

	if(!fArchiveFile->open(QIODevice::WriteOnly))
		return false;

	QByteArray b;

	qint64 bSize=0;
	for (int i = 0; i < fFiles.size(); ++i) {
		QIODevice* d = fFiles.at(i).data();
		if(d->isOpen())
			return false;
		d->open(QIODevice::ReadOnly);
		b.append(qCompress(fFiles.at(i).data()->readAll(), 9));
		//b.append(fFiles.at(i).data()->readAll());
		fFiles.at(i).data()->close();
		fFiles[i].setCompressedSize(b.size()-bSize);
		bSize=b.size();
	}

	fArchiveFile->write(fHeader.generateHeader());
	fArchiveFile->write(b);

	fArchiveFile->close();

	return true;
}

bool QArchive::extract(QString path)
{
	QDir dir;
	dir.mkpath(path);
	dir.cd(path);
	treeConstIterator<int> it = fTree.globalIterator();
	Movement m;
	while( (m=it.next()) ){
		switch(m){
		case TreeEnd:
			return true;
		case Branch:
			if(!dir.mkdir(it.name()))
					return false;
			dir.cd(it.name());
			break;
		case LeavingBranch:
			if(!dir.cdUp())
					return false;
			break;
		case Item:
			QFile f(dir.absolutePath()+QDir::separator()+it.name());
			if(!f.open(QIODevice::WriteOnly))
				return false;
			QByteArray data;
			if(!readFile(it.itemValue(), data))
				return false;
			f.write(data);
			f.close();
			break;

		}
	}

	return true;
}

//______________________________________________________
//------------------------------------------------------


bool QArchive::addDir(QString name)
{
	return fTree.addDir(name);
}

bool QArchive::changeDir(QString dir)
{
	bool r;
	fTree.changeDir(dir, r);
	return r;
}

bool QArchive::upDir()
{
	return fTree.upDir();
}

QString QArchive::currentDir()
{
	return fTree.currentDir();
}

bool QArchive::addFile(QString name, QIODevice *device, quint32 compressedSize)
{
	if(!fTree.addItem(name, fFiles.size()))
		return false;

	fFiles.append(device);
	if(compressedSize)
		fFiles.last().setCompressedSize(compressedSize);
	return true;
}

bool QArchive::addFile(QString name, const QString& path)
{
	return addFile(name, new QFile(path));
}

bool QArchive::addBufferedFile(QString name, const QByteArray &data)
{
	if(!fTree.addItem(name, fFiles.size()))
		return false;
	QBuffer *b = new QBuffer();
	b->open(QIODevice::WriteOnly);
	b->write(data);
	b->close();
	fFiles.append(QArchiveData( b));
	return true;
}

bool QArchive::addTextFile(QString name, const QString &data)
{
	if(!fTree.addItem(name, fFiles.size()))
		return false;
	QByteArray a = data.toUtf8();
	QBuffer *b = new QBuffer();
	b->open(QIODevice::WriteOnly);
	b->write(a);
	b->close();
	fFiles.append(QArchiveData(b));
	return true;
}

bool QArchive::readFile(QString name, QByteArray& data)
{
	int id;
	if(!fTree.searchItem(name,id))
		return false;

	return readFile(id, data);
}

bool QArchive::readFile(int fileID, QByteArray &data)
{

	QIODevice* file = fFiles.at(fileID).data();

	if(!file->open(QIODevice::ReadOnly))
		return false;

	if(!fFiles.at(fileID).isCompressed())
		data = file->readAll();
	else
		data = qUncompress(file->readAll());

	file->close();

	return true;
}

//______________________________________________________
//------------------------------------------------------
QArchive::~QArchive()
{
	delete fArchiveFile;
	for (int i = 0; i < fFiles.size(); ++i)
		delete fFiles.at(i).data();
}

} // End namespace
