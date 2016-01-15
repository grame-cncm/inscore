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


bool QArchive::compress(QString outputArchive, bool overwrite)
{

	QFile output(outputArchive);

	if(output.exists()){
		if(overwrite)
			output.remove();
		else
			return false;
	}

	if(!output.open(QIODevice::WriteOnly))
		return false;

	QByteArray b;

	qint64 bSize=0;

	treeConstIterator<int> it = fTree.globalIterator();
	while(it.next()){
		int i;
		if(it.item(i)){
			if(!fFiles[i].compressedData(b))
				return false;
			fFiles[i].setCompressedSize(b.size()-bSize);
			bSize=b.size();
		}
	}

	output.write(fHeader.generateHeader());
	output.write(b);

	output.close();

	return true;
}

bool QArchive::extract(QString path, bool overwrite)
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
			if(!dir.mkpath(it.name()))
					return false;
			dir.cd(it.name());
			break;
		case LeavingBranch:
			if(!dir.cdUp())
					return false;
			break;
		case Item:
			QFile f(dir.absolutePath()+QDir::separator()+it.name());
			if(f.exists()){
				if(overwrite)
					f.remove();
				else
					continue;
			}
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

QString QArchive::currentDir() const
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

	data.clear();
	if(!fFiles[fileID].uncompressedData(data))
		return false;

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

bool QArchiveData::compressedData(QByteArray& data)
{
	if(!fData->open(QIODevice::ReadOnly))
		return false;
//*
	if(fCompressed)
		data.append(fData->readAll());
	else
		data.append(qCompress(fData->readAll(), 9));
/*/
	data.append(fData->readAll());
//*/

	fData->close();
	return true;
}

bool QArchiveData::uncompressedData(QByteArray &data)
{if(!fData->open(QIODevice::ReadOnly))
		return false;
//*
	if(fCompressed)
		data.append(qUncompress(fData->readAll()));
	else
		data.append(fData->readAll());

/*/
	data.append(fData->readAll());
//*/
	fData->close();
	return true;

}

} // End namespace
