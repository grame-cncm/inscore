
#include <QDebug> 

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gdrawarea.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->bar1->setRange (0, kBarScale);
	ui->bar2->setRange (0, kBarScale);
	ui->bar3->setRange (0, kBarScale);

	clearBars();

	ui->stopButton->setEnabled (false);
	ui->followButton->setEnabled (false);
	QObject::connect (ui->learn1Button, SIGNAL(clicked()), this, SLOT(learn1()));
	QObject::connect (ui->learn2Button, SIGNAL(clicked()), this, SLOT(learn2()));
	QObject::connect (ui->learn3Button, SIGNAL(clicked()), this, SLOT(learn3()));
	QObject::connect (ui->followButton, SIGNAL(clicked()), this, SLOT(follow()));
	QObject::connect (ui->stopButton,	SIGNAL(clicked()), this, SLOT(forcestop()));
	QObject::connect (ui->frame,		SIGNAL(stopDraw()),this, SLOT(stop()));
	QObject::connect (ui->frame,		SIGNAL(data(float,float)),this, SLOT(data(float,float)));

	fFollower.setBars(ui->bar1, ui->bar2, ui->bar3, kBarScale);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearBars()
{
	ui->bar1->setValue (0);
	ui->bar2->setValue (0);
	ui->bar3->setValue (0);
}

void MainWindow::adjustButtons	(bool state)
{
	ui->learn1Button->setEnabled (state);
	ui->learn2Button->setEnabled (state);
	ui->learn3Button->setEnabled (state);
	ui->followButton->setEnabled (state);
	ui->stopButton->setEnabled (!state);
}

void MainWindow::learn( int index)
{
	ui->status->setText ("Learning");
	ui->frame->clear();
	ui->frame->collect();
	adjustButtons (false);
	if (fFollower.getState() == GestureFollower::kIdle)
		fFollower.startLearn (index);
}

void MainWindow::learn1()		{ learn(0); }
void MainWindow::learn2()		{ learn(1); }
void MainWindow::learn3()		{ learn(2); }

void MainWindow::follow()
{
	ui->status->setText ("Following");
	ui->frame->clear();
	ui->frame->collect();
	clearBars();
	adjustButtons (false);
	if (fFollower.getState() == GestureFollower::kIdle)
		fFollower.startFollow ();
}

void MainWindow::data(float x, float y)
{
	fFollower.data(x, y);
}

void MainWindow::forcestop()
{
	ui->status->setText ("");
	adjustButtons (true);
	fFollower.stop();
}

void MainWindow::stop()
{
	if (fFollower.getState() != GestureFollower::kDecoding) forcestop();
	else ui->frame->collect();
}
