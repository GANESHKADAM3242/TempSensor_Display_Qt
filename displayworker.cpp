#include "displayworker.h"
#include "sensorworker.h"
#include <QThread>



DisplayWorker::DisplayWorker(SensorData *data, QMutex *mutex, QObject *parent)
: QObject(parent), m_data(data), m_mutex(mutex)
{

}

void DisplayWorker::startDisplay()
{
    m_running = true;
    while(m_running)
    {
        double temp,hum;
        int count;
        {
            QMutexLocker locker(m_mutex);
            temp = m_data->temperature;
            hum = m_data->humidity;
            count = m_data->readCount;
        }
        emit newReading(temp, hum, count);

    }

}

void DisplayWorker::stop()
{
    m_running = false;
}

