
#include <vector>

#include "MainWindow.h"

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>


using namespace std;

#define DEFAULT_ADDRESS "192.168.1.21"
//#define DEFAULT_ADDRESS "192.168.43.88"
#define DEFAULT_PORT 8000


//------------------------------------------------------------------------
void SensorWidget::timerEvent(QTimerEvent * )
{
	for (TSensors::const_iterator i = fSensors.begin(); i != fSensors.end(); i++) {
		Sensor* sensor = i->sensor;
		QCheckBox * ctrl = i->controler;
         if (ctrl && ctrl->isChecked()) {
			if (!sensor->active() ) sensor->activate(true);
            int count = sensor->count();
            if (count) {
              OSCStream osc;
                osc.start( sensor->address());
                for (int i=0; i<count; i++)
                    osc << sensor->value(i);
                osc.end();
                fSocket->Send(osc.Data(), osc.Size());
            }
		}
		else if (sensor->active() ) sensor->activate(false);
	}
}

//------------------------------------------------------------------------
void SensorWidget::initSensors()
{
	int avail = 0;
	for (int t = Sensor::kSensorStart; t < Sensor::kSensorMax; t++) {
		TSensorUI ui;
		ui.sensor = new Sensor(t);
		if (ui.sensor->available()) {
			QCheckBox* ctrl = new QCheckBox(verticalLayoutWidget);
			ctrl->setObjectName(ui.sensor->name());
			QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
			sizePolicy.setHorizontalStretch(0);
			sizePolicy.setVerticalStretch(0);
			sizePolicy.setHeightForWidth(ctrl->sizePolicy().hasHeightForWidth());
			ctrl->setSizePolicy(sizePolicy);
			ctrl->setMinimumSize(QSize(100, 24));
			verticalLayout->addWidget(ctrl, 0, Qt::AlignVCenter);
			ctrl->setText(ui.sensor->name());
			ui.controler = ctrl;
			avail++;
		}
		else ui.controler = 0;
		fSensors.push_back(ui);
	}
	if (!avail) {
		QMessageBox alert(QMessageBox::Information, "Sensors", "No sensor available", QMessageBox::Ok, this);
		alert.exec();
	}
}

//------------------------------------------------------------------------
SensorWidget::SensorWidget(QWidget *parent) : QFrame(parent)
{
	setupUi(this);
	initSensors();
	
	connect( mAddressLineEdit,	SIGNAL(editingFinished()) , this , SLOT(addressChge()) );
    connect( mPortLineEdit,	SIGNAL(valueChanged(int)) , this , SLOT(portChge(int)) );
    connect( mSkip,	SIGNAL(stateChanged(int)) , this , SLOT(skipChge(int)) );

	fSocket = new UdpTransmitSocket( IpEndpointName( destination().toStdString().c_str() , port() ) );
	QSettings settings;
	mPortLineEdit->setValue(settings.value("port", DEFAULT_PORT).toInt());
	mAddressLineEdit->setText(settings.value("address", DEFAULT_ADDRESS).toString());
	sendAvailable();
	fTimerID = startTimer(10);
}

//------------------------------------------------------------------------
void SensorWidget::sendAvailable ()
{
	for (TSensors::const_iterator i = fSensors.begin(); i != fSensors.end(); i++) {
		if (i->sensor->available())
			send(i->sensor->address(), "available");
	}
}

//------------------------------------------------------------------------
SensorWidget::~SensorWidget()
{
	killTimer(fTimerID);
	for (size_t i = 0; i < fSensors.size(); i++)
		delete fSensors[i].sensor;
	QSettings settings;
    settings.setValue("port", mPortLineEdit->value());
    settings.setValue("address", destination());
}

//------------------------------------------------------------------------
QString SensorWidget::destination () const
{
	QString address = mAddressLineEdit->text();
	if( address.isEmpty())
		address = DEFAULT_ADDRESS;
	return address;
}

//------------------------------------------------------------------------
void SensorWidget::destchge()
{
	UdpTransmitSocket* socket = new UdpTransmitSocket( IpEndpointName( destination().toStdString().c_str() , port() ) );
	UdpTransmitSocket* tmp = fSocket;
	fSocket = socket;
	delete tmp;

    QSettings settings;
    settings.setValue("port", mPortLineEdit->value());
    settings.setValue("address", destination());
}

//------------------------------------------------------------------------
void SensorWidget::addressChge()	{ destchge(); }
void SensorWidget::portChge(int)	{ destchge(); }
void SensorWidget::skipChge(int state)
{
    for (TSensors::const_iterator i = fSensors.begin(); i != fSensors.end(); i++) {
        i->sensor->skipDuplicates (state);
    }
}

//------------------------------------------------------------------------
int SensorWidget::port () const
{
	return mPortLineEdit->value();
}

//------------------------------------------------------------------------
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags ) 
	:	QMainWindow ( parent , flags )
{
	QCoreApplication::setOrganizationName("GRAME");
    QCoreApplication::setOrganizationDomain("QtOSCSensor");
	
	QSettings settings;
	resize(settings.value("size", QSize(100, 100)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	
	SensorWidget* widget = new SensorWidget(this);
	setCentralWidget(widget);
}

//------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	QSettings settings;

    settings.setValue("size", size());
    settings.setValue("pos", pos());
}
