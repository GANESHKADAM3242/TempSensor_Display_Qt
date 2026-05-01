#include "displayworker.h"
#include "sensorworker.h"
#include <QThread>
#include <qdebug.h>



DisplayWorker::DisplayWorker(SensorData *data, QMutex *mutex, QObject *parent)
: QObject(parent)
{
    readData     = data;
    displayMutex = mutex;
    qDebug() << "[DisplayWorker] constructed. data:" << data << "mutex:" << mutex;
}

void DisplayWorker::startDisplay()
{
    displayRunning = true;
    while(displayRunning)
    {
        double temp,hum;
        int count;
        {
            QMutexLocker locker(displayMutex);
            temp  = readData->temperature;
            hum   = readData->humidity;
            count = readData->readCount;
        }
        emit newReading(temp, hum, count);
        QThread::msleep(1000);
    }

}

void DisplayWorker::stop()
{
    displayRunning = false;
}

