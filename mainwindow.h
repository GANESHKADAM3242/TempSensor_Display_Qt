#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QMutex>
#include <QThread>
#include "sensorworker.h"
#include "displayworker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewReading(double temp, double hum, int count);

private:
    Ui::MainWindow *ui;

    SensorData     mainSharedData;
    QMutex         mainMutex;

    SensorWorker  *mainSensorWorker  = nullptr;
    DisplayWorker *mainDisplayWorker = nullptr;
    QThread       *mainSensorThread  = nullptr;
    QThread       *mainDisplayThread = nullptr;
};
#endif // MAINWINDOW_H
