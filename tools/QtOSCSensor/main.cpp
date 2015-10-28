#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QDebug>

#include "MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app( argc , argv );
    QPixmap pixmap(":/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
qDebug() << "splash show";
	MainWindow mainWindow;
	mainWindow.show();
	
    splash.finish(&mainWindow);

	return app.exec();
}
