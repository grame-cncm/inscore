#include "QArchive.h"
#include <QtCore>

using namespace qarchive;
int main(int argc, char* argv[]){

	qDebug()<<"QArchive test!";

	SQArchive a = QArchive::emptyArchive();
	a->addTextFile("Fichier 1","Le contenu de ce fichier peut sembler étrange.");
	a->addDir("Test");
	a->addDir("Test/Test");
	a->addDir("Images");
	a->changeDir("Test");
	a->addTextFile("Explication","Mais c'est déjà formidable que vous puissiez le lire !");
	a->addFile("/Images/Smiley.png", "TuxGaby.png");

	a->compress("zip.bundle");


	SQArchive b = QArchive::readArchive("zip.bundle");
	b->addFile("/Smiley.png", "TuxGaby.png");
	b->compress("zip2.bundle");

	SQArchive c = QArchive::readArchive("zip2.bundle");
	b->extract("bundle");

	return 0;
}
