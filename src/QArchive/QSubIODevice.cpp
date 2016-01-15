#include "QSubIODevice.h"

namespace qarchive{

QSubIODevice::QSubIODevice(QIODevice *data, quint64 startPos, quint64 size)
	:QIODevice(data), fData(data), fStart(startPos), fSize(size)
{
}

bool QSubIODevice::open(QIODevice::OpenMode mode)
{
	if((! (mode & QIODevice::WriteOnly) ) && (mode & QIODevice::ReadOnly)){
		if(fData->open(mode))
			return QIODevice::open(mode);
	}
	return false;
}

void QSubIODevice::close()
{
	fData->close();
	QIODevice::close();
}

qint64 QSubIODevice::readData(char *data, qint64 maxlen)
{
	if(pos()>=fSize)
		return -1;

	if(!fData->seek(pos()+fStart))
		return -1;

	return fData->read(data, qMin(maxlen, (qint64)fSize-pos()));
}

qint64 QSubIODevice::writeData(const char *, qint64)
{
	return -1;
}

} // End namespace
