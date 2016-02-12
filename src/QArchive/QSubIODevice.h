#ifndef QSUBIODEVICE_H
#define QSUBIODEVICE_H

#include <QIODevice>

namespace qarchive{

class QSubIODevice: public QIODevice{
	QIODevice* fData;
	qint64 fStart;
	const qint64 fSize;
public:
	QSubIODevice(QIODevice *data, quint64 startPos, quint64 size);

	bool open(OpenMode mode);
	void close();
	bool isSequential() const {return false;}

	void setStartPos(quint64 startpos){fStart = startpos;}

	quint64 subSize() const {return fSize;}

	// QIODevice interface
protected:
	qint64 readData(char *data, qint64 maxlen);
	qint64 writeData(const char *, qint64);


};


} // End namespace

#endif // QSUBIODEVICE_H
