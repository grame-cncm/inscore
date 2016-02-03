#include <QDataStream>
#include <QBuffer>

#include "QArchive.h"

#include "QArchiveHeader.h"
#include "QSubIODevice.h"


namespace qarchive{

QArchiveError QArchiveHeader::readHeader(QIODevice *input)
{
	if(!input->open(QIODevice::ReadOnly))
		return FILE_NOT_FOUND;
	QDataStream d(input);
	d.setVersion(QDataStream::Qt_5_5);

	quint8 fieldID;
	QList<QSubIODevice*> files;

	while(!d.atEnd()){
		d >> fieldID;
		if(fieldID==HEADER_END){
			break;
		}else if(fieldID==HEADER_HIERARCHY){

			//------  HIERARCHY ------
			while(fieldID!=H_HIER_END){
				d >> fieldID;
				if(fieldID == H_HIER_END){
					break;

				}else if(fieldID == H_NEW_DIR){
					char* name;
					d >> name;
					fArchive->fTree.addDir(QString::fromUtf8(name));
					fArchive->fTree.changeDir(QString::fromUtf8(name));

				}else if(fieldID == H_NEW_FILE){
					char* name;
					quint32 size;
					d >> size >> name;
					QSubIODevice *file = new QSubIODevice(input, 0, size);
					files.push_back(file);
					fArchive->addFileFromSubIODevice(QString::fromUtf8(name), file, true);
				}else if(fieldID == H_UPDIR){
					fArchive->fTree.upDir();
				}else{
					return FILE_CORRUPTED;
				}
			}

		}else if(HEADER_PROPERTIES){
			//------  PROPERTIES ------
			while(fieldID != H_PROP_END){
				d >> fieldID;
				if(fieldID == H_PROP_END)
					break;
				if(fieldID == H_BUNDLE_VERSION){
					d >> bundleVersion;
					if(bundleVersion > BUNDLE_VERSION)	//Bundle version is higher than the library version
						return HIGHER_BUNDLE_VERSION;
				}else if(fieldID == H_ITL_VERSION)
					d >> itlVersion;
				else if(fieldID == HEADER_END)		//H_PROP_END has not been detected -> invalid file
					return FILE_CORRUPTED;
				else
					continue;
			}
		}else{
			return FILE_CORRUPTED;
		}
	}

	qint64 headerSize = d.device()->pos();
	input->close();

	//Align all SubIODevices to their start position
	for (int i = 0; i < files.size(); ++i) {
		files.at(i)->setStartPos(headerSize);
		headerSize += files.at(i)->subSize();
	}

	return NO_ERROR;
}

QByteArray QArchiveHeader::generateHeader() const
{
	QBuffer buffer;
	buffer.open(QIODevice::ReadWrite);
	QDataStream out(&buffer);
	out.setVersion(QDataStream::Qt_5_5);

	//Writing PROPERTIES
	out << (quint8) HEADER_PROPERTIES;
	out << (quint8) H_BUNDLE_VERSION;
	out << BUNDLE_VERSION;
	out << (quint8) H_ITL_VERSION;
	out << itlVersion;
	out << (quint8) H_PROP_END;

	//Writing HIERARCHY
	out << (quint8) HEADER_HIERARCHY;
	treeConstIterator<int> it = fArchive->fTree.globalIterator();
	Movement m;
	while( (m=it.next()) ){
		switch(m){
		case TREE_END:
			break;
		case BRANCH:
			out << (quint8) H_NEW_DIR;
			out << it.name().toUtf8().data();
			break;
		case LEAVING_BRANCH:
			out << (quint8) H_UPDIR;
			break;
		case ITEM:
			out << (quint8) H_NEW_FILE;
			out << (quint32) fArchive->fFiles.at(it.itemValue()).compressedSize();
			out << it.name().toUtf8().data();
			break;
		}
	}
	out << (quint8) H_HIER_END;

	//Writing End of Header

	out << (quint8) HEADER_END;
	buffer.close();

	return buffer.data();
}



} // End namespace
