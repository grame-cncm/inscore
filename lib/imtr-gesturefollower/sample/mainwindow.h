#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gfollower.h"

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

	gfollower fFollower;

	enum {kBarScale = 100 };
	void clearBars();	
	
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void learn			(int index);
    void adjustButtons	(bool state);

public slots:
    void learn1();
    void learn2();
    void learn3();
    void follow();
    void stop();
    void forcestop();
    void data(float, float);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
