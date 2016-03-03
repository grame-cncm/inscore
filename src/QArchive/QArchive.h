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

class QArchiveData;
class QSubIODevice;


/*!
 * \brief The QArchive interface allows to create an archive, empty or from an existing one, to add files and directory to it, and finally to extract or compress it to the disk.
 */
class QArchive
{
	friend class QArchiveHeader;

	QList<QArchiveData> fFiles;
	Tree<int> fTree;

	QIODevice* fArchiveData=0;
	QArchiveHeader fHeader;


public:
	/*!
	 * \brief emptyArchive create an empty  archive
	 */
	static QArchive* emptyArchive();

	/*!
	 * \brief	Create an archive using an existing one stored on the disk.
	 *			During the process, the header of the existing archive is read but none of the data is uncompressed.
	 * \param path the path to the archive file (can be relative or absolute)
	 * \param error Contains the error that happened during reading of the archive (contain ARCH_OK=0 if no error)
	 */
	static QArchive* readArchiveFromFile(QString path, QArchiveError& error)		{ return readArchive(new QFile(path), error);}
	 //! \brief	Overide readArchiveFromFile(QString path, QArchiveError& error) without the error parameter
	static QArchive* readArchiveFromFile(QString path)								{ QArchiveError e; return readArchiveFromFile(path, e);}
	//! \brief	overide readArchiveFromFile(QString path, QArchiveError& error) with standard string
	static QArchive* readArchiveFromFileStd(std::string path, QArchiveError& error)	{ return readArchiveFromFile(QString::fromStdString(path), error);}
	//! \brief	Overide readArchiveFromFileStd(QString path, QArchiveError& error) with standard string
	static QArchive* readArchiveFromFileStd(std::string path)						{ QArchiveError e; return readArchiveFromFileStd(path, e);}

	/*!
	 * \brief	Create an archive using an existing one stored in the memory
	 *			During the process, the header of the existing archive is read but none of the data is uncompressed.
	 * \param data the archive data
	 * \param error Contains the error that happened during reading of the archive (contain ARCH_OK=0 if no error)1
	 */
	static QArchive* readArchiveFromData(const QByteArray& data, QArchiveError& error);
	//! \brief	Overide readArchiveFromData(const QByteArray& data, QArchiveError& error) with a pointer to a byte array
	static QArchive* readArchiveFromData(QByteArray* data, QArchiveError& error)	{ return readArchive(new QBuffer(data),error);}

	/*!
	 * \brief	Compress this archive into a single archive file on the disk.
	 *			The data of all the files added is read and compressed then a header is written
	 * \param outputArchive Path to the output archive file (can be absolute or relative)
	 * \param overwrite force the overwrite on the file
	 * \return The error that occurs during the process (or ARCH_OK=0 if none)
	 */
	QArchiveError compress(QString outputArchive, bool overwrite = true);
	//! \brief	Overwrite compress(QString outputArchive, bool overwrite) with std::string
	QArchiveError compressStd(std::string outputArchive, bool overwrite = true)		{ return compress(QString::fromStdString(outputArchive), overwrite);}
	/*!
	 * \brief	Extract this archive to a specific path
	 *			The data of all the archive is read and uncompressed
	 * \param outputArchive Path to the folder where the archive should be uncompressed (if the path does not exist it will be created).
	 * \param overwrite force the overwrite
	 * \return The error that occurs during the process (or ARCH_OK=0 if none)
	 */
	QArchiveError extract(QString path, bool overwrite = true);
	//! \brief	Overwrite extract(QString path, bool overwrite) with std::string
	QArchiveError extractStd(std::string path, bool overwrite = true)				{ return extract(QString::fromStdString(path), overwrite);}

	/*!
	 * \brief add a folder in the virtual archive tree
	 * \param folder the folder name (can be absolute or relative, in which case the folder is added in the current directory).
	 * \return true if succeed, false otherwise (folder already exists).
	 */
	bool addDir(QString name);
	//! \brief	Overwrite addDirStd(QString name) with std::string
	bool addDirStd(const std::string& name){return addDir(QString::fromStdString(name));}

	/*!
	 * \brief change the current directory in the virtual archive tree
	 * \param dir the directory name (can be absolute or relative, in which case the folder is added in the current directory).
	 * \return true if succeed, false otherwise (folder does not exist).
	 */
	bool		changeDir(QString dir);
	//! \brief	Overwrite changeDirStd(QString name) with std::string
	bool		changeDirStd(const std::string& dir){return changeDir(QString::fromStdString(dir));}
	/*!
	 * \brief Move the current directory to the parent folder of the current directory.
	 * \return true if succeed, false otherwise (the current folder is the root folder).
	 */
	bool		upDir();
	//! \brief Return the current directory absolute path
	QString		currentDir()	const;
	//! \brief Return the current directory absolute path (in a std::string).
	std::string	currentDirStd()	const {return currentDir().toStdString();}

	/*!
	 * \brief	Add a file into the virtual archive tree.
	 *			The data of the file is read from a file stored on the disk.
	 * \param name The name of the file as it shall be stored in the archive. (can be absolute or relative path to the current directory)
	 * \param path The path of the file stored on the disk that contains the data.
	 * \param currentDir If "name" is not a path (only the file name), this flag should be set to true for optimisation.
	 * \return true if succeed, false otherwise (a file already exist with this name in the archive, or the data could not be read).
	 */
	bool addFile(QString name, const QString &path, bool currentDir=false);
	//! \brief Overwrite addFile(QString name, const QString &path, bool currentDir) with std::string.
	bool addFileStd(const std::string& name, const std::string& path, bool currentDir=false)
				{ return addFile(QString::fromStdString(name),QString::fromStdString(path), currentDir);}

	/*!
	 * \brief	Add a file into the virtual archive tree.
	 *			The data of the file is read from a buffer in the memory.
	 * \param name The name of the file as it shall be stored in the archive. (can be absolute or relative path to the current directory)
	 * \param data The data of the file.
	 * \param currentDir If "name" is not a path (only the file name), this flag should be set to true for optimisation.
	 * \return true if succeed, false otherwise (a file already exist with this name)
	 */
	bool addBufferedFile(QString name, const QByteArray& data, bool currentDir=false);
	//! \brief Overwrite addBufferedFile(QString name, const QByteArray& data, bool currentDir)41 1445with std::string.
	bool addBufferedFileStd(const std::string& name, const QByteArray& data, bool currentDir=false)
				{ return addFile(QString::fromStdString(name), data, currentDir);}

	/*!
		 * \brief	Add a text file into the virtual archive tree.
		 *			The data of the file is read from a string stored in the memory.
		 * \param name The name of the file as it shall be stored in the archive. (can be absolute or relative path to the current directory)
		 * \param data The string stored in the file (as UTF-8).
		 * \param currentDir If "name" is not a path (only the file name), this flag should be set to true for optimisation.
		 * \return true if succeed, false otherwise (a file already exist with this name)
		 */
	bool addTextFile(QString name, const QString& data, bool currentDir=false);
	//! \brief Overwrite addTextFile(QString name, const QString &data, bool currentDir) with std::string.
	bool addTextFileStd(const std::string& name, const std::string& data, bool currentDir=false)
				{ return addTextFile(QString::fromStdString(name), QString::fromStdString(data), currentDir);}

	/*!
	 * \brief Extract a specific file from the archive
	 * \param name The name of the file in the archive (can be absolute or relative path).
	 * \param data Store the data contained in the file.
	 * \return true if succeed, false otherwise (the file does not exist)
	 */
	bool readFile(QString name, QByteArray &data);
	//! \brief Overwrite readFile(QString name, QByteArray &data) with std::string.
	bool readFileStd(const std::string& name, QByteArray &data)						{ return readFile(QString::fromStdString(name), data);}

	//! \brief Return the tree that store the archive hierarchy internally
	const Tree<int>& tree() const {return fTree;}
	//! \brief Return the header of the archive (for exemple to add or read custom property).
	QArchiveHeader& header() {return fHeader;}

	virtual ~QArchive();

protected:
			QArchive():fHeader(this){}

	static QArchive* readArchive(QIODevice* device, QArchiveError& error);

	bool addFileFromSubIODevice(QString name, QSubIODevice* device, bool currentDir = false);

	bool addFile(QString name, QIODevice* device, bool currentDir);
	bool readFile(int fileID, QByteArray &data);
};

class QArchiveData
{
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
