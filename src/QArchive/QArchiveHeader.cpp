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

	while(true){
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
					delete[] name;
				}else if(fieldID == H_NEW_FILE){
					char* name;
					quint32 size;
					d >> size >> name;
					QSubIODevice *file = new QSubIODevice(input, 0, size);
					files.push_back(file);
					fArchive->addFileFromSubIODevice(QString::fromUtf8(name), file, true);
					delete[] name;
				}else if(fieldID == H_UPDIR){
					fArchive->fTree.upDir();
				}else{
					return FILE_CORRUPTED;
				}
			}

		}else if(fieldID==HEADER_PROPERTIES){
			//------  PROPERTIES ------
			while(fieldID != H_PROP_END){
				d >> fieldID;
				if(fieldID == H_PROP_END)
					break;
				if(fieldID == H_ARCHIVE_VERSION){
					d >> archiveVersion;
					if(archiveVersion > ARCHIVE_VERSION)	//Bundle version is higher than the library version
						return HIGHER_BUNDLE_VERSION;
				}else if(fieldID == H_ITL_VERSION){		//Compatibility
					qreal n;
					d >> n;
				}else if(fieldID == HEADER_END)		//H_PROP_END has not been detected -> invalid file
					return FILE_CORRUPTED;
				else
					continue;
			}
		}else if(fieldID==HEADER_CUSTOM_PROP){
			//------  CUSTOM PROPERTIES ------
			QArchiveError e = readCustomProp(d);
			if(e)
				return e;
			else
				continue;
		}else{
			return FILE_CORRUPTED;
		}

		if(d.atEnd())
			return FILE_CORRUPTED;
	}

	qint64 headerSize = d.device()->pos();
	input->close();

	//Align all SubIODevices to their start position
	for (int i = 0; i < files.size(); ++i) {
		files.at(i)->setStartPos(headerSize);
		headerSize += files.at(i)->subSize();
	}

	return ARCH_OK;
}

//______________________________________________
QByteArray QArchiveHeader::generateHeader() const
{
	QBuffer buffer;
	buffer.open(QIODevice::ReadWrite);
	QDataStream out(&buffer);
	out.setVersion(QDataStream::Qt_5_5);

	//Writing PROPERTIES
	out << (quint8) HEADER_PROPERTIES;
	out << (quint8) H_ARCHIVE_VERSION;
	out << ARCHIVE_VERSION;
	out << (quint8) H_PROP_END;

	//Writing CUSTOM PROPERTIES
	out << (quint8) HEADER_CUSTOM_PROP;
	out << generateCustomProp();
	out << (quint8) H_CUSTOM_END;

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

//______________________________________________
QByteArray QArchiveHeader::generateCustomProp() const
{
	QByteArray r;
	QDataStream d(&r, QIODevice::WriteOnly);
	d.setVersion(QDataStream::Qt_5_5);
	for(auto it = fNbrProperties.begin(); it != fNbrProperties.end(); it++){
		d << (quint8) (0x40 + it->first);
		d << (float) it->second;
	}
	for(auto it = fStringProperties.begin(); it != fStringProperties.end(); it++){
		d << (quint8) (0xC0 + it->first);
		d << it->second.c_str();
	}

	return r;
}

//______________________________________________
QArchiveError QArchiveHeader::readCustomProp(QDataStream &d)
{
	quint8 fieldID;
	while(!d.atEnd()){
		d >> fieldID;

		if(fieldID == H_CUSTOM_END)
					return ARCH_OK;
		else if((fieldID & (quint8)0xC0) == (quint8)0xC0){	// string
			quint8 t = fieldID & (quint8)0xC0 ;
			quint8 t1 = (quint8) 0xC0;
			char* c;
			d >> c;
			fStringProperties[fieldID & (quint8)0x3F] = std::string(c);
			delete[] c;
		}else if((fieldID & (quint8)0xC0) == (quint8)0x40){ // number
			float f;
			d >> f;
			fNbrProperties[fieldID & (quint8)0x3F] = f;
		}else
			FILE_CORRUPTED;
	}

	return FILE_CORRUPTED;
}

//_________________________________________________________________
//-----------------------------------------------------------------
bool QArchiveHeader::addNbrProperty(int id, float value)
{
	if(id>64 || id<0)
		return false;

	if(fNbrProperties.count(id))
		return false;

	fNbrProperties[id] = value;
	return true;
}

//______________________________________________
bool QArchiveHeader::readNbrProperty(int id, float &value)
{
	auto it = fNbrProperties.find(id);
	if(it==fNbrProperties.end())
		return false;

	value = it->second;
	return true;
}

//______________________________________________
bool QArchiveHeader::addStringProperty(int id, std::string value)
{
	if(id>64 || id<0)
		return false;

	if(fStringProperties.count(id))
		return false;

	fStringProperties[id] = value;
	return true;
}

//______________________________________________
bool QArchiveHeader::readStringProperty(int id, std::string &value)
{
	auto it = fStringProperties.find(id);
	if(it==fStringProperties.end())
		return false;

	value = it->second;
	return true;
}


} // End namespace
