#include "sensorworker.h"
#include <QThread>
#include <QDebug>
#include <QRandomGenerator>

SensorWorker::SensorWorker(SensorData *data, QMutex *mutex, QObject *parent)
    : QObject{parent}
{}

void SensorWorker::startReading()
{
    m_running = true;

    while(m_running)
    {
        QMutexLocker locker(m_mutex); // mutex lock here.
        m_data->temperature = 20.0 + QRandomGenerator::global()->bounded(15);
        m_data->humidity    = 40.0 + QRandomGenerator::global()->bounded(15);
        m_data->readCount = m_data->readCount + 1;
    }
    QThread::msleep(500);
    emit finished();

}

void SensorWorker::stop()
{
    m_running = false;
}
