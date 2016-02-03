#include <QBuffer>

#include "QArchive.h"
#include "QSubIODevice.h"

namespace qarchive{

SQArchive QArchive::emptyArchive()
{
	return new QArchive();
}

SQArchive QArchive::readArchive(QIODevice *d, QArchiveError &error)
{
	QArchive* a = new QArchive();
	a->fArchiveData = d;
	error = a->fHeader.readHeader(a->fArchiveData);
	return a;
}

SQArchive QArchive::readArchiveFromData(const QByteArray &data, QArchiveError &error)
{
	QBuffer *b = new QBuffer();
	b->setData(data);
	return readArchive(b,error);
}

//______________________________________________________
//------------------------------------------------------

QArchiveError QArchive::compress(QString outputArchive, bool overwrite)
{
	QFile output(outputArchive);

	if(output.exists()){
		if(overwrite)
			output.remove();
		else
			return FILE_EXIST;
	}

	if(!output.open(QIODevice::WriteOnly))
		return WRONG_PERMISSIONS;

	QByteArray b;

	qint64 bSize=0;

	treeConstIterator<int> it = fTree.globalIterator();
	while(it.next()){
		int i;
		if(it.item(i)){
			if(!fFiles[i].compressedData(b))
				return FILE_CORRUPTED;
			fFiles[i].setCompressedSize(b.size()-bSize);
			bSize=b.size();
		}
	}

	output.write(fHeader.generateHeader());
	output.write(b);

	output.close();

	return NO_ERROR;
}

QArchiveError QArchive::extract(QString path, bool overwrite)
{
	QDir dir;
	dir.mkpath(path);
	dir.cd(path);
	treeConstIterator<int> it = fTree.globalIterator();
	Movement m;
	while( (m=it.next()) ){
		switch(m){
		case TREE_END:
			return NO_ERROR;
		case BRANCH:
			if(!dir.mkpath(it.name()))
					return WRONG_PERMISSIONS;
			dir.cd(it.name());
			break;
		case LEAVING_BRANCH:
			if(!dir.cdUp())
					return FILE_CORRUPTED;
			break;
		case ITEM:
			QFile f(dir.absolutePath()+QDir::separator()+it.name());
			if(f.exists()){
				if(overwrite)
					f.remove();
				else
					continue;
			}
			if(!f.open(QIODevice::WriteOnly))
				return WRONG_PERMISSIONS;
			QByteArray data;
			if(!readFile(it.itemValue(), data))
				return FILE_CORRUPTED;
			f.write(data);
			f.close();
			break;

		}
	}

	return NO_ERROR;
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

bool QArchive::addFile(QString name, QIODevice *device, bool currentDir)
{
	if(!fTree.addItem(name, fFiles.size(), currentDir))
		return false;

	fFiles.append(device);
	return true;
}

bool QArchive::addFileFromSubIODevice(QString name, QSubIODevice *device, bool currentDir)
{
	if(!addFile(name, device, currentDir))
		return false;
	fFiles.last().setCompressed(true);
	fFiles.last().setCompressedSize(device->subSize());
	return true;
}

bool QArchive::addFile(QString name, const QString& path, bool currentDir)
{
	QFile* file = new QFile(path);
	if(!file->exists()){
		delete file;
		return false;
	}
	return addFile(name, new QFile(path), currentDir);
}


bool QArchive::addBufferedFile(QString name, const QByteArray &data, bool currentDir)
{
	if(!fTree.addItem(name, fFiles.size(), currentDir))
		return false;
	QBuffer *b = new QBuffer();
	b->open(QIODevice::WriteOnly);
	b->write(data);
	b->close();
	fFiles.append(QArchiveData( b));
	return true;
}

bool QArchive::addTextFile(QString name, const QString &data, bool currentDir)
{
	if(!fTree.addItem(name, fFiles.size(), currentDir))
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
	delete fArchiveData;
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
