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

    //shared state
    SensorData sharedData;
    QMutex     mutex;



}

MainWindow::~MainWindow()
{
    delete ui;
}
