#include "sensorworker.h"
#include <QThread>
#include <QDebug>
#include <QRandomGenerator>

SensorWorker::SensorWorker(SensorData *data, QMutex *mutex, QObject *parent)
    : QObject{parent}
{
    writeData   = data;
    sensorMutex = mutex;
    qDebug() << "[SensorWorker] constructed. data:" << data << "mutex:" << mutex;
}

void SensorWorker::startReading()
{
    qDebug() << "[SensorWorker] startReading() on thread:" << QThread::currentThread();
    SensorRunning = true;

    while(SensorRunning)
    {
        {
            QMutexLocker locker(sensorMutex); // mutex lock here.
            writeData->temperature = 20.0 + QRandomGenerator::global()->bounded(15);
            writeData->humidity    = 40.0 + QRandomGenerator::global()->bounded(15);
            writeData->readCount = writeData->readCount + 1;
        }
        QThread::msleep(500);
    }

    emit finished();

}

void SensorWorker::stop()
{
    SensorRunning = false;
}
