#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QDebug>
#include "sensorworker.h"
#include "displayworker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->currentTemp_lineEdit->setReadOnly(true);
    ui->currentHumidity_lineEdit->setReadOnly(true);


    mainSensorWorker   = new SensorWorker(&mainSharedData, &mainMutex);
    mainDisplayWorker  = new DisplayWorker(&mainSharedData, &mainMutex);

    // create thread for sensor and display
    mainSensorThread  = new QThread;
    mainDisplayThread = new QThread;

    //moving workers to thread
    mainSensorWorker->moveToThread(mainSensorThread);
    mainDisplayWorker->moveToThread(mainDisplayThread);

    //create signal and slots
    QObject::connect(mainSensorThread, &QThread::started, mainSensorWorker, &SensorWorker::startReading);
    QObject::connect(mainDisplayThread, &QThread::started, mainDisplayWorker, &DisplayWorker::startDisplay);

    connect(mainSensorWorker,  &SensorWorker::finished, mainSensorThread,  &QThread::quit);
    connect(mainDisplayWorker, &DisplayWorker::finished, mainDisplayThread, &QThread::quit);

    //print Temp. and Humidity in widget window Realtime
    connect(mainDisplayWorker, &DisplayWorker::newReading, this, &MainWindow::onNewReading);

    //start thread
    mainSensorThread->start();
    mainDisplayThread->start();


}

MainWindow::~MainWindow()
{
    // Tell workers to exit their while loops
    mainSensorWorker->stop();
    mainDisplayWorker->stop();

    // Wait for threads to finish cleanly before UI destroys
    mainSensorThread->quit();
    mainSensorThread->wait();
    delete mainSensorThread;

    mainDisplayThread->quit();
    mainDisplayThread->wait();
    delete mainDisplayThread;

    delete ui;
}

void MainWindow::onNewReading(double temp, double hum, int count)
{
    ui->currentTemp_lineEdit->setText(QString::number(temp) + "°C");
    ui->currentHumidity_lineEdit->setText(QString::number(hum) + "%");
    qDebug()<<"Count: "<<count;

}
